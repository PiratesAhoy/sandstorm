#include "storm-engine\controls.h"
#include "storm-engine\layers.h"
#include "storm-engine\interface\messages.h"

object GameInterface;

extern void LoadDemo();
extern void UnloadDemo();

void Module_Main() {
	CreateEntity(&GameInterface, "xinterface");
	LayerAddObject(INTERFACE_EXECUTE, &GameInterface, -100);
	LayerAddObject(INTERFACE_REALIZE, &GameInterface, -100);

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, "resource/ini/interfaces/main.ini");

	CreateAndMapControl("ITurnH", 256, 0);
	CreateAndMapControl("ITurnV", 257, INVERSE_CONTROL);

	if(LoadSegment("modules/interface/info_handler.c"))
	{
		LoadDemo();
		UnloadDemo();
		UnloadSegment("modules/interface/info_handler.c");
	}
}

void CreateAndMapControl(string control_name, int key_code, int state)
{
	int control_code = CreateControl(control_name);
	MapControl(control_code, key_code);
	SetControlFlags(control_code, state);
}