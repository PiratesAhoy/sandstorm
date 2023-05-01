#include "storm-engine\controls.h"
#include "storm-engine\layers.h"
#include "storm-engine\interface\messages.h"
#include "storm-engine\sea_ai\script_defines.h"

object GameInterface;
object WorldMap;

object Sea;
object AISea;
object SeaCameras;
object SeaFreeCamera;

object SeaShipCharacterForCamera;

void Module_Main() {
	CreateEntity(&GameInterface, "xinterface");
	LayerAddObject(INTERFACE_EXECUTE, &GameInterface, -100);
	LayerAddObject(INTERFACE_REALIZE, &GameInterface, -100);

	CreateAndMapControl("ITurnH", CE_MOUSE_X_AXIS, 0);
	CreateAndMapControl("ITurnV", CE_MOUSE_Y_AXIS, INVERSE_CONTROL);
	CreateAndMapControl("FreeCamera_Turn_H", CE_MOUSE_X_AXIS, 0);
	CreateAndMapControl("FreeCamera_Turn_V", CE_MOUSE_Y_AXIS, INVERSE_CONTROL);
	CreateAndMapControl("FreeCamera_Forward", 87, 0);
	CreateAndMapControl("FreeCamera_Backward", 83, 0);

	CreateSea();

	CreateEntity(&WorldMap, "AdvancedMap");
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
	LayerAddObject(SEA_EXECUTE, &Sea, 0);
	LayerAddObject(SEA_REALIZE, &Sea, 0);

	CreateEntity(&SeaCameras, "SEA_CAMERAS");

	SeaFreeCamera.Perspective = 1.285;
	CreateEntity(&SeaFreeCamera, "FREE_CAMERA");

	LayerAddObject(INFO_REALIZE, &SeaCameras, 1);
	LayerAddObject(SEA_EXECUTE, &SeaFreeCamera, 1);

	SeaCameras.Camera = "SeaFreeCamera";

	CreateEntity(&AISea, "sea_ai");
	LayerAddObject(SEA_EXECUTE, &AISea, 1);
	LayerAddObject(SEA_REALIZE, &AISea, -1);
	SendMessage(&AISea, "la", AI_MESSAGE_SET_CAMERAS_ATTRIBUTE, &SeaCameras);

	SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaFreeCamera, &SeaShipCharacterForCamera);
}
