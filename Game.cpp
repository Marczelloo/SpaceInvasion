#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() {};

//Initializing game elements
void Game::GameInit() {
	//Initializing game elements

	//Initializing player
	p = Player(screenWidth / 2.0f, screenHeight / 1.3f, 200, 200);

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

	//Initializing enemy bullets
	for (int i = 0; i < bulletNum; i++) {
		eb[i].setActive(false);
		eb[i].setX(e[i].getX());
		eb[i].setY(e[i].getY());
		eb[i].setSpeed(200);
	}

	cout << "Game initialization done" << endl;
}

//updating game elements
void Game::GameUpdate() {
	//Stops game if window not focused
	if (IsWindowFocused()) {
		//if statement for game over
		if (!gameOver) {
			//if statement for game pause
			if (!gamePause) {
				//pausing game
				if (IsKeyReleased(KEY_P)) {
					gamePause = true;
					cout << "Zatrzymano gre" << endl;
				}
				//rendering infinte background
				s.Update();

				//updating player
				p.UpdateControlling();
				p.UpdateFrames();

				//checking if player is dead
				if (p.getHealth() <= 0) {
					gameOver = true;
				}

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

				//idle animation for enemies
				for (int i = 0; i < wave * 10; i++) {
					e[i].setFrame((int)gameTime % 2);
					e[i].Update();
				}


				//detecting bullet and enemy collision and handling events
				for (int i = 0; i < bulletNum; i++) {
					if (b[i].getActive()) {
						b[i].setY(b[i].getY() - b[i].getSpeed() * GetFrameTime());
						for (int j = 0; j < wave * 10; j++) {
							if (e[j].getActive()) {
								if (CheckCollisionRecs(Rectangle{ b[i].getX(), b[i].getY(), b[i].getWidth(), b[i].getHeight() }, Rectangle{ e[j].getX() - e[j].getWidth() / 2, e[j].getY() - e[j].getWidth(), e[j].getWidth(), e[j].getHeight() })) {
									e[j].setHit(true);
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
						//reseting bullet when colliding with top game window
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


						//Hiding wave text and reseting wave timer
						tempTime = 0;
						waveText = false;
					}
					else {
						//displaying wave text and timer
						waveText = true;
					}

				}

				//spawning bullets and detecting collision with player
				for (int i = 0; i < wave * 10; i++) {
					if (!eb[i].getActive()) {
						if (e[i].getShooting()) {
							cout << "Shooting" << endl;
							eb[i].setActive(true);
							eb[i].setX(e[i].getX());
							eb[i].setY(e[i].getY());
						}
					}
					if (eb[i].getActive()) {
						if (CheckCollisionRecs(Rectangle{ eb[i].getX(), eb[i].getY(), eb[i].getWidth(), eb[i].getHeight() }, Rectangle{ p.getX() - p.getWidth() / 2, p.getY() - p.getHeight() / 2, p.getWidth(), p.getHeight() })) {
							eb[i].setActive(false);
							p.setHealth(p.getHealth() - 5);
							cout << p.getHealth() << endl;
						}
						eb[i].Update();
					}
				}
			}
			else if (gamePause) {
				//unpausing game 
				if (IsKeyReleased(KEY_P)) {
					gamePause = false;
					cout << "Wznowiono gre" << endl;
				}
			}
		}
		else if (gameOver) {
			if (IsKeyDown(KEY_R)) {
				GameInit();
				gameOver = false;
			}
		}
	}
}

void Game::GameDraw() {
	//Drawing game elements
	//game.GameDraw();
	ClearBackground(Color{ 0, 0, 10, 1 });

	s.Draw();
	p.Draw();

		for (int i = 0; i < bulletNum; i++) {
			if (b[i].getActive()) b[i].Draw();
		}

	//drawing enemies
	for (int i = 0; i < wave * 10; i++) {
		if (e[i].getActive()) e[i].Draw();
	}

	//drawing enemy bullets
	for (int i = 0; i < enemyNum; i++) {
		if (eb[i].getActive()) eb[i].Draw();
	}

	//drawing score
	DrawScore();
	if (waveText) {
		DrawText(TextFormat("Wave cleared %i", wave), screenWidth / 2 - MeasureText(TextFormat("Wave cleared %i", wave), 24) / 2, screenHeight / 2 - 10, 24, WHITE);
		DrawText(TextFormat("Next wave in %i", 3 - (int)tempTime), screenWidth / 2 - MeasureText(TextFormat("Next wave in %i", 3 - (int)tempTime), 24) / 2, screenHeight / 2 + 10, 24, WHITE);
	}
	if (gamePause) PausedWindow();
	if (gameOver) GameOverWindow();
}


//drawing game UI (scores, player health, wave etc.)
void Game::DrawScore() {
	DrawRectangle(0, screenHeight - 50, screenHeight, 50, BLACK);
	DrawRectangleLinesEx(Rectangle{ 0, screenHeight - 50, screenWidth, 50 }, 3, WHITE);
	DrawText(TextFormat("SCORE:%i", score), 10, screenHeight - 35, 20, WHITE);
	DrawText(TextFormat("HIGHSCORE:%i", HighScore), screenWidth - 10 - MeasureText(TextFormat("HIGHSCORE:%i", HighScore), 20), screenHeight - 35, 20, WHITE);
	DrawText("HEALTH", screenWidth / 2 - MeasureText("HEALTH", 20) / 2, screenHeight - 40, 20, WHITE);
	DrawRectangle(screenWidth / 2 - 100, screenHeight - 20, 200 * p.getHealth() / 100, 14, RED);
	DrawRectangleLinesEx(Rectangle{ screenWidth / 2 - 100, screenHeight - 20, 200, 14 }, 2, WHITE);
}

//unloading all game textures
void Game::UnloadGameTxt() {
	//unloading bullet textures
	for (int i = 0; i < bulletNum; i++) {
		b[i].UnloadTxt();
	}

	//unloading enemies textures
	for (int i = 0; i < wave * 10; i++) {
		e[i].UnloadTxt();
	}

	//unloading enemy bullets texture
	for (int i = 0; i < wave * 10; i++) {
		eb[i].UnloadTxt();
	}

	//unloading space background texture
	s.UnloadTxt();

	//unloading player texture
	p.UnloadTxt();
}

//unloading all game sounds
void Game::UnloadGameSounds() {

}

//couting game time
void Game::GameTimer() {
	gameTime += 1.0f * GetFrameTime(); //counting time
}


//drawing paused window and its elements
void Game::PausedWindow() {
	DrawRectangleRec(RectPausedWindow, BLACK);
	DrawRectangleLinesEx(RectPausedWindow, PausedWindowFrameThick, WHITE);
	DrawText("GAME PAUSED", centerX - MeasureText("GAME PAUSED", 30) / 2, centerY - PausedWindowHeight / 2 + PausedWindowFrameThick * 4, 30, WHITE);
	DrawText("Press [P] to unpause", centerX - MeasureText("Press [P] to unpause", 25) / 2, centerY + 120, 25, WHITE);
	DrawText("Press [ESC] to exit", centerX - MeasureText("Press [ESC] to exit", 26) / 2, centerY + 160, 26, WHITE);
}

//drawging game over window and its elements
void Game::GameOverWindow() {
	DrawRectangleRec(RectGameOverWindow, BLACK);
	DrawRectangleLinesEx(RectGameOverWindow, GameOverWindowFrameThick, WHITE);
	DrawText("GAME OVER", centerX - MeasureText("GAME OVER", 30) / 2, centerY - 100, 30, WHITE);
	DrawText(TextFormat("SCORE:%i", score), centerX - MeasureText(TextFormat("SCORE:%i", score), 26) / 2, centerY - 40, 26, WHITE);
	DrawText(TextFormat("HIGHSCORE:%i", HighScore), centerX - MeasureText(TextFormat("HIGHSCORE:%i", HighScore), 26) / 2, centerY + 20, 26, WHITE);
	DrawText("Press [R] to play again", centerX - MeasureText("Press [R] to play again", 26) / 2, centerY + 120, 26, WHITE);
	DrawText("Press [ESC] to exit", centerX - MeasureText("Press [ESC] to exit", 26) / 2, centerY + 160, 26, WHITE);
}
//saving score as highscore if larger than earlier
void Game::SaveHighScore() {
	cout << "Zapisywanie wyniku" << endl;
	ifstream write_file("score.txt");
	int tempHS;

	if (!write_file) {
		cout << "Theres error eith opening file for writing" << endl;
	}

	write_file >> tempHS;

	write_file.close();
	if (tempHS < score) {
		file = fopen("score.txt", "w");

		if (file == NULL) {
			cout << "Theres error with opening filr for writing" << endl;
		}

		fprintf(file, "%d", score);

		fclose(file);
		cout << "Ukonczono zapisywanie" << endl;
	}
}

//reading highscore
void Game::ReadHighScore() {
	cout << "Odczytywanie z pliku" << endl;
	ifstream input_file("score.txt");

	if (!input_file) {
		cout << "Theres error with opening filr for reading" << endl;
	}

	input_file >> HighScore;

	input_file.close();
	cout << "Odczytywanie ukonczone" << endl;
}

//unloading game elements
void Game::UnloadGame() {
	UnloadGameTxt();
	UnloadGameSounds();
}