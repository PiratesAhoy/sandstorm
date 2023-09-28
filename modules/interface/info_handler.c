object InfoHandler;

void LoadDemo() {
	InfoHandler.picbackfilename = "checker_texture.png";
	CreateEntity(InfoHandler,"InfoHandler");
}

void UnloadDemo() {
	DeleteClass(&InfoHandler);
}
