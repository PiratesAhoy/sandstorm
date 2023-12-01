#include "storm-engine\controls.h"
#include "storm-engine\layers.h"
#include "storm-engine\messages.h"
#include "storm-engine\interface\messages.h"
#include "storm-engine\sea_ai\script_defines.h"

object GameInterface;
object Location;

object SeaCameras;
object FreeCamera;
object SeaShipCharacterForCamera;

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

	LoadLocation();
}

void CreateAndMapControl(string control_name, int key_code, int state)
{
	int control_code = CreateControl(control_name);
	MapControl(control_code, key_code);
	SetControlFlags(control_code, state);
}

void LoadLocation()
{
	if (!CreateEntity(&Location, "location")) {
		Trace("LoadLocation: failed to create loc entity.");
		return false;
	}

	CreateEntity(&SeaCameras, "SEA_CAMERAS");

	FreeCamera.Perspective = 1.285;
	CreateEntity(&FreeCamera, "FREE_CAMERA");

	LayerAddObject(INFO_REALIZE, &SeaCameras, 1);
	LayerAddObject(SEA_EXECUTE, &FreeCamera, 1);
	SeaCameras.Camera = "FreeCamera";
	SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &FreeCamera, &SeaShipCharacterForCamera);

	SendMessage(&Location, "lssl", MSG_LOCATION_ADD_MODEL, "barrel_1", "", 0);
}
