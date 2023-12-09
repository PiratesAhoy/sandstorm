#include "storm-engine\controls.h"
#include "storm-engine\layers.h"
#include "storm-engine\messages.h"
#include "storm-engine\interface\messages.h"
#include "storm-engine\sea_ai\script_defines.h"

#event_handler("Control Activation", "ProcessControls")

object GameInterface;
object Location;
object Lighter;

object Scene;
object FreeCamera;

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

	CreateAndMapControl("RunTest", 32, 0); // Space
	CreateAndMapControl("LighterToggle", 76, 0); // L

	LoadLocation();
}

void RunTest()
{
	if (!IsEntity(&Lighter) ) {
		if (!FindEntity(&Lighter, "Lighter") ) {
			Trace("Failed to find location lighter");
		}
		else {
			Trace("Found location lighter");
		}
	}

	// New Ligher messages:
	// sl "LoadPreset" <preset id>
	// sl "SavePreset" <preset id>
	// sll "Process" <trace shadows?> <smooth shadows?>
	// s "SaveLight"

	SendMessage(&Lighter, "sl", "LoadPreset", 1);
	SendMessage(&Lighter, "sll", "Process", 1, 1);
	SendMessage(&Lighter, "s", "SaveLight");
}

void ProcessControls()
{
	string control_name = GetEventData();
	if (control_name == "RunTest") {
		RunTest();
	}
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
	}

	CreateEntity(&Scene, "Scene");

	FreeCamera.Perspective = 1.285;
	CreateEntity(&FreeCamera, "FREE_CAMERA");

	SendMessage(&Scene, "si", "SetActiveCamera", &FreeCamera);

	LayerAddObject(EXECUTE, &Scene, 0);
	LayerAddObject(SEA_EXECUTE, &Scene, 0);

	SendMessage(&Location, "ls", MSG_LOCATION_LIGHTPATH, "day");
	SendMessage(&Location, "lsfff", MSG_LOCATION_ADD_LIGHT, "outside_day", 0, 0, 0);
	SendMessage(&Location, "lssl", MSG_LOCATION_ADD_MODEL, "barrel_1", "", 0);
}
