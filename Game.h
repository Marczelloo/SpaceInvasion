#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <raylib.h>
#include "Includes.cpp"
#include "Consts.cpp"
#include <fstream>

class Game {
	int shootRate = 0;
	int score = 0;
	int HighScore = 0;
	float gameTime = 0;
	int wave = 0;
	float tempTime = 0;
	bool waveText = false;
	int dead = 0;
	bool gamePause = false;
	float centerX = screenWidth / 2, centerY = screenHeight / 2;
	FILE* file;
	Player p;
	SpaceBg s;
	Enemy e[enemyNum];
	Bullet b[bulletNum];
	float PausedWindowWidth = 500, PausedWindowHeight = 400;
	float PausedWindowX = centerX - PausedWindowWidth / 2;
	float PausedWindowY = centerY - PausedWindowHeight / 2;
	int PausedWindowFrameThick = 5;
	Rectangle RectPausedWindow{PausedWindowX,PausedWindowY, PausedWindowWidth, PausedWindowHeight };
public:
	Game();
	void PausedWindow();
	void GameInit();
	void GameUpdate();
	void GameDraw();
	void UnloadGameTxt();
	void DrawScore();
	void GameTimer();
	void SaveHighScore();
	void ReadHighScore();
};