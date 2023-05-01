object Render;

int iScriptVersion = 54128;

extern void Module_Main();

void Main() {
	LoadModule("worldmap");
}

void LoadModule(string module)
{
	string module_index = "modules/" + module + "/index.c";
	if(LoadSegment(module_index))
	{
		Module_Main();
		UnloadSegment(module_index);
	}
}
