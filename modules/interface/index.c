#include "storm-engine\controls.h"
#include "storm-engine\layers.h"
#include "storm-engine\interface\messages.h"

object GameInterface;

extern void LoadDemo();
extern void UnloadDemo();

#define FONT_DEFAULT "arial"

#define COLOR_NORMAL 4294967295

void Module_Main() {
	CreateEntity(&GameInterface, "xinterface");
	LayerAddObject(INTERFACE_EXECUTE, &GameInterface, -100);
	LayerAddObject(INTERFACE_REALIZE, &GameInterface, -100);

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, "resource/ini/interfaces/main.ini");

	CreateAndMapControl("ITurnH", 256, 0);
	CreateAndMapControl("ITurnV", 257, INVERSE_CONTROL);

	CreateString(true, "testString", "Sample text", FONT_DEFAULT, COLOR_NORMAL, 20, 50, SCRIPT_ALIGN_LEFT, 2.0);

//	if(LoadSegment("modules/interface/info_handler.c"))
//	{
//		LoadDemo();
//		UnloadDemo();
//		UnloadSegment("modules/interface/info_handler.c");
//	}
}

void CreateAndMapControl(string control_name, int key_code, int state)
{
	int control_code = CreateControl(control_name);
	MapControl(control_code, key_code);
	SetControlFlags(control_code, state);
}

void CreateString(int enable,string strName, string strData, string fontName, int color, int x, int y, int alignment, float scale)
{
    GameInterface.strings.(strName) = strData;
    SendMessage(&GameInterface,"lssllllf",MSG_INTERFACE_CREATE_STRING, strName, fontName, color, x,y,alignment,scale);
    if(enable==FALSE)
    {
        SendMessage(&GameInterface,"ls", MSG_INTERFACE_DISABLE_STRING, strName);
    }
}