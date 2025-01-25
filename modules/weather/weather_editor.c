
void ShowWeatherEditor()
{
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, "resource/ini/interfaces/weather_editor.ini");

	SetEventHandler("eSlideChange","SliderChange",0);
}

void SliderChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if(sNodeName == "WAVE_HEIGHT")
	{
        Sea.Sea2.MaxSeaHeight = fVal * 10;
		return;
    }
	if(sNodeName == "WAVE_SCALE_1")
	{
        Sea.Sea2.Scale1 = fVal;
		return;
    }
	if(sNodeName == "WAVE_REFLECTION")
	{
        Sea.Sea2.Reflection = fVal;
		return;
    }
	if(sNodeName == "WAVE_TRANSPARENCY")
	{
        Sea.Sea2.Transparency = fVal;
		return;
    }
	if(sNodeName == "WAVE_ATTENUATION")
	{
        Sea.Sea2.Attenuation = fVal;
		return;
    }
	if(sNodeName == "WAVE_FRESNEL")
	{
        Sea.Sea2.Fresnel = fVal;
		return;
    }
}
