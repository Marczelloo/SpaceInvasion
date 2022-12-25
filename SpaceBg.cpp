#include "SpaceBg.h"

void SpaceBg::Draw() {
	DrawTextureEx(space, Vector2{ 0, scrolling }, 0.0f, 1.0f, WHITE);
	DrawTextureEx(space, Vector2{ 0, -space.height + scrolling }, 0.0f, 1.0f, WHITE);
}

void SpaceBg::Update() {
	scrolling += 0.5;
	if (scrolling >= space.height) scrolling = 0;
}

void SpaceBg::UnloadTxt() {
	UnloadTexture(space);
}