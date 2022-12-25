//TO DO
//Make waves with enemy spawn + 
//Make enemies move 
//Make enemies idle +
//Rebuild enemt spawning + 
//Add sounds to the game
//Rebiuld most of the code for OOP +
//Make game over screen
//Make pause menu +/-
//Make falling comets that can hit you
//Make collision working with setters and getters
//Remade structore of whole project +

#include "raylib.h"
#include <iostream>
#include "Game.h"

using namespace std;

int main() {
	//Initializing game window and setting v-sync
	InitWindow(screenWidth, screenHeight, "Space Invasion");
	SetWindowState(FLAG_VSYNC_HINT);
 
	Game game;
	game.GameInit();
	game.ReadHighScore();
	

	while (!WindowShouldClose()) {
		//Updatnig
		// --------------------------------------------------------------------
		game.GameUpdate();
		game.GameTimer();

		//Drawing
		// --------------------------------------------------------------------
		BeginDrawing();
		
		game.GameDraw();

		EndDrawing();
	}
	game.SaveHighScore();

	//unloading all textures
	game.UnloadGameTxt();
	
	//unloading all sounds


	CloseWindow();

	return 0;
}