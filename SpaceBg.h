#pragma once

#include <raylib.h>

class SpaceBg {
	float x = 0;
	float scrolling = 0.0f;
	Texture2D space = LoadTexture("assets/space_background.png");
public:
	void Draw();
	void Update();
	void UnloadTxt();
};