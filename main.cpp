//TO DO
//Make waves with enemy spawn + 
//Make enemies move 
//Make enemies idle +
//Rebuild enemt spawning + 
//Add sounds to the game
//Rebiuld most of the code for OOP +
//Make game over screen
//Make main menu
//Make pause menu
//Make falling comets that can hit you
//Make collision working with setters and getters

#include "raylib.h"
#include <iostream>
#include "Includes.cpp"
#include "Consts.cpp"

using namespace std;

//class Game {
//	int shootRate = 0;
//	int score = 0;
//	float gameTime = 0;
//	int wave = 0;
//	float tempTime = 0;
//	bool waveText = false;
//	int dead = 0;
//	bool gamePause = false;
//
//	Player p;
//	SpaceBg s;
//	Enemy e[enemyNum];
//	Bullet b[bulletNum];
//public:
//	Game() {};
//	void PausedWindow();
//	void GameInit();
//	void GameUpdate();
//	void GameDraw();
//	void unloadingTextures();
//};

int shootRate = 0;
int score = 0;
float gameTime = 0;
int wave = 1;
float tempTime = 0;
bool waveText = false;
int dead = 0;
bool gamePause = false;


void PausedWindow() {
	DrawText("GAME PASUED", screenWidth / 2, screenHeight / 2, 40, WHITE);
	cout << "paused" << endl;
}

void GameInit() {
	
}

void GameUpdate() {
	
}

void DrawScore() {
	DrawText(TextFormat("SCORE %i", score), 5, 5, 20, WHITE);
}

void GameDraw() {
	
}

void unloadingTextures() {
	
}

int main() {
	//Initializing game window and setting v-sync
	InitWindow(screenWidth, screenHeight, "Space Invasion");
	SetWindowState(FLAG_VSYNC_HINT);

	Player p(screenWidth / 2.0f, screenHeight / 1.3f, 200, 200);;
	SpaceBg s;
	Bullet b[bulletNum];
	Enemy e[enemyNum];
	 
	//Game game;
	//Initializing game elements
	//game.GameInit();
	//Initializing player
	//Initializing bullets
	for (int i = 0; i < bulletNum; i++) {
		b[i].setX(p.getX());
		b[i].setY(p.getY());
		b[i].setActive(false);
		b[i].setSpeed(400);
	};

	//setting wave
	wave = 1;

	//spawning enemy
	for (int j = 0; j < wave; j++) {
		for (int i = 0; i < 10; i++) {
			e[i + 10 * j].setX(e[i + 10 * j].getWidth() * i + e[i + 10 * j].getWidth() / 2);
			if (j == 0) {
				e[i + 10 * j].setY(60);
			}
			else {
				e[i + 10 * j].setY(60 + 60 * j);
			}
			e[i + 10 * j].setActive(true);
			e[i + 10 * j].setHealth(3 + wave / 2);
			cout << i + 10 * j << endl;
			cout << e[i + 10 * j].getX() << " : " << e[i + 10 * j].getY() << " : " << e[i + 10 * j].getActive() << endl;
		}
		cout << j << endl;
	}
	cout << "Game initialization done" << endl;

	while (!WindowShouldClose()) {
		//Updatnig
		// --------------------------------------------------------------------
		//game.GameUpdate();
		gameTime += 1.0f * GetFrameTime(); //counting time
		//Manageing game state 
	//if (!gamePause) {
	//	//Pasuing game
	//	if (IsKeyReleased(KEY_P)) {
	//		gamePause = false;
	//	}
		//rendering infinte background
		s.Update();

		//updating player
		p.UpdateControlling();
		p.UpdateFrames();

		//Shooting
		if (IsKeyDown(KEY_SPACE)) {
			shootRate += 5;
			for (int i = 0; i < bulletNum; i++) {
				if (!b[i].getActive() && shootRate % 40 == 0) {
					b[i].setX(p.getX() - b[i].getWidth() / 2);
					b[i].setY(p.getY() - p.getHeight() / 1.5);
					b[i].setActive(true);
					break;
				}
			}
		}
		for (int i = 0; i < wave * 10; i++) {
			e[i].setFrame((int)gameTime % 2);
			e[i].Update();
		}
		//enemy update
		for (int i = 0; i < bulletNum; i++) {
			if (b[i].getActive()) {
				b[i].setY(b[i].getY() - b[i].getSpeed() * GetFrameTime());
				for (int j = 0; j < wave * 10; j++) {
					if (e[j].getActive()) {
						e[j].Update();
						if (CheckCollisionRecs(Rectangle{ b[i].getX(), b[i].getY(), b[i].getWidth(), b[i].getHeight() }, Rectangle{ e[j].getX() - e[j].getWidth() / 2, e[j].getY() - e[j].getWidth(), e[j].getWidth(), e[j].getHeight() })) {
							e[j].setHealth(e[j].getHealth() - 1);
							cout << e[j].getHealth() << endl;
							b[i].setActive(false);
							if (e[j].getHealth() <= 0) {
								e[j].setActive(false);
								score += 100;
							}
						}
					}
				}
				if (b[i].getY() < 0) {
					b[i].setActive(false);
				}
			}
		}
		dead = 0;
		//Counting dead enemies
		for (int i = 0; i < wave * 10; i++) {
			if (!e[i].getActive()) {
				dead++;
			}
		}

		//Spawning waves of enemies
		if (dead == wave * 10) {
			//countging time till next wave
			tempTime += GetFrameTime() * 1;
			if (tempTime >= 3) {
				dead = 0;
				wave++;
				//spawning wave
				for (int j = 0; j < wave; j++) {
					for (int i = 0; i < 10; i++) {
						e[i + 10 * j].setX(e[i + 10 * j].getWidth() * i + e[i + 10 * j].getWidth() / 2);
						if (j == 0) {
							e[i + 10 * j].setY(60);
						}
						else {
							e[i + 10 * j].setY(60 + 60 * j);
						}
						e[i + 10 * j].setActive(true);
						e[i + 10 * j].setHealth(3 + wave / 2);
						cout << i + 10 * j << endl;
						cout << e[i + 10 * j].getX() << " : " << e[i + 10 * j].getY() << " : " << e[i + 10 * j].getActive() << endl;
					}
					cout << j << endl;
				}
				tempTime = 0;
				waveText = false;
			}
			else {
				waveText = true;
			}

		}
		/*} else {
			PausedWindow();
			if (IsKeyReleased(KEY_P)) {
				gamePause = false;
			}
		}*/
		//Drawing
		// --------------------------------------------------------------------
		BeginDrawing();
		
		//Drawing game elements
		//game.GameDraw();
		ClearBackground(Color{ 0, 0, 10, 1 });

		s.Draw();
		p.Draw();

		for (int i = 0; i < bulletNum; i++) {
			if (b[i].getActive()) b[i].Draw();
		}

		for (int i = 0; i < wave * 10; i++) {
			if (e[i].getActive()) e[i].Draw();
		}
		DrawScore();
		if (waveText) {
			DrawText(TextFormat("Wave cleared %i", wave), screenWidth / 2 - MeasureText(TextFormat("Wave cleared %i", wave), 20) / 2, screenHeight / 2 - 10, 20, WHITE);
			DrawText(TextFormat("Next wave in %i", 3 - (int)tempTime), screenWidth / 2 - MeasureText(TextFormat("Next wave in %i", 3 - (int)tempTime), 20) / 2, screenHeight / 2 + 10, 20, WHITE);
		}


		EndDrawing();
	}

	//unloading all textures
	//game.unloadingTextures();
	for (int i = 0; i < bulletNum; i++) {
		b[i].UnloadTxt();
	}

	for (int i = 0; i < wave * 10; i++) {
		e[i].UnloadTxt();
	}
	s.UnloadTxt();
	p.UnloadTxt();
	//unloading all sounds

	CloseWindow();

	return 0;
}