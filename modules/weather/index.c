#include "storm-engine\controls.h"
#include "storm-engine\layers.h"
#include "storm-engine\interface\messages.h"
#include "storm-engine\sea_ai\script_defines.h"

#define SKY_PRIORITY 0
#define SEA_PRIORITY 10
#define CAMERA_PRIORITY 20

object GameInterface;

object Sea;
object AISea;
object SeaCameras;
object SeaFreeCamera;

// Empty object used for camera creation
object SeaShipCharacterForCamera;

object Sky;

void Module_Main() {
	CreateEntity(&GameInterface, "xinterface");
	LayerAddObject(INTERFACE_EXECUTE, &GameInterface, -100);
	LayerAddObject(INTERFACE_REALIZE, &GameInterface, -100);

	CreateAndMapControl("ITurnH", CE_MOUSE_X_AXIS, 0);
	CreateAndMapControl("ITurnV", CE_MOUSE_Y_AXIS, INVERSE_CONTROL);
	CreateAndMapControl("FreeCamera_Turn_H", CE_MOUSE_X_AXIS, 0);
	CreateAndMapControl("FreeCamera_Turn_V", CE_MOUSE_Y_AXIS, 0);
	CreateAndMapControl("FreeCamera_Forward", 87, 0);
	CreateAndMapControl("FreeCamera_Backward", 83, 0);

	CreateSea();
	CreateSky();
}

void CreateAndMapControl(string control_name, int key_code, int state)
{
	int control_code = CreateControl(control_name);
	MapControl(control_code, key_code);
	SetControlFlags(control_code, state);
}

void CreateSea()
{
	CreateEntity(&Sea, "sea");
	LayerAddObject(SEA_EXECUTE, &Sea, SEA_PRIORITY);
	LayerAddObject(SEA_REALIZE, &Sea, SEA_PRIORITY);

	CreateEntity(&SeaCameras, "SEA_CAMERAS");

	SeaFreeCamera.Perspective = 1.285;
	SeaFreeCamera.Position.y = 5;
	CreateEntity(&SeaFreeCamera, "FREE_CAMERA");

	LayerAddObject(INFO_REALIZE, &SeaCameras, CAMERA_PRIORITY);
	LayerAddObject(SEA_EXECUTE, &SeaFreeCamera, CAMERA_PRIORITY);

	SeaCameras.Camera = "SeaFreeCamera";

	CreateEntity(&AISea, "sea_ai");
	LayerAddObject(SEA_EXECUTE, &AISea, SEA_PRIORITY);
	LayerAddObject(SEA_REALIZE, &AISea, SEA_PRIORITY);
	SendMessage(&AISea, "la", AI_MESSAGE_SET_CAMERAS_ATTRIBUTE, &SeaCameras);

	SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaFreeCamera, &SeaShipCharacterForCamera);

	SetEventHandler(WEATHER_CALC_FOG_COLOR, "Whr_OnCalcFogColor", 0);
}

void CreateSky()
{
	// Sky
	CreateEntity(&Sky,"Sky");
	LayerAddObject(SEA_REFLECTION, &Sky, SKY_PRIORITY);
	LayerAddObject(SEA_REALIZE, &Sky, SKY_PRIORITY);
	Sky.RotateSpeed = 0.01;
	Sky.Dir.s1 = "worldmap/skies/generated/";
	Sky.Dir = "";
	Sky.Size = 1000;
	Sky.IsDone = "";
}

int Whr_OnCalcFogColor()
{
	return argb(0,255,255,255);
}
