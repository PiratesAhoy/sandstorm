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
object Scene;
object FreeCamera;

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

	CreateEntity(&Scene, "Scene");

	FreeCamera.Perspective = 1.285;
	FreeCamera.Position.y = 10;
	CreateEntity(&FreeCamera, "FREE_CAMERA");

	SendMessage(&Scene, "si", "SetActiveCamera", &FreeCamera);

	LayerAddObject(EXECUTE, &Scene, 0);
	LayerAddObject(SEA_EXECUTE, &Scene, 0);

	SetEventHandler(WEATHER_CALC_FOG_COLOR, "Whr_OnCalcFogColor", 0);

	Sea.Sea2.Reflection = 0.9;
	Sea.Sea2.Transparency = 0.9;
	Sea.Sea2.Attenuation = 0.3;
	Sea.Sea2.Fresnel = 0.45;
	Sea.Sea2.WaterColor = argb(0, 25, 55, 80);
	Sea.Sea2.SkyColor = argb(0, 205, 255, 255);
	Sea.Sea2.BumpScale = 0.05;
	Sea.Sea2.Amp1 = 7.0;
	Sea.Sea2.AnimSpeed1 = 2.0;
	Sea.Sea2.Scale1 = 0.3;
	Sea.Sea2.MoveSpeed1 = "2.0, 0.0, 0.0";

	Sea.Sea2.MaxSeaHeight = 100;
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
