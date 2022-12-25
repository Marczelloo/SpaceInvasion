#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() {};

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
	cout << "Game initialization done" << endl;
}

void Game::GameUpdate() {

	if (!gamePause) {
		if (IsKeyReleased(KEY_P)) {
			gamePause = true;
			cout << "Zatrzymano gre" << endl;
		}
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
	} else if(gamePause) {
		if (IsKeyReleased(KEY_P)) {
			gamePause = false;
			cout << "Wznowiono gre" << endl;
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

	for (int i = 0; i < wave * 10; i++) {
		if (e[i].getActive()) e[i].Draw();
	}
	DrawScore();
	if (waveText) {
		DrawText(TextFormat("Wave cleared %i", wave), screenWidth / 2 - MeasureText(TextFormat("Wave cleared %i", wave), 24) / 2, screenHeight / 2 - 10, 24, WHITE);
		DrawText(TextFormat("Next wave in %i", 3 - (int)tempTime), screenWidth / 2 - MeasureText(TextFormat("Next wave in %i", 3 - (int)tempTime), 24) / 2, screenHeight / 2 + 10, 24, WHITE);
	}
	if (gamePause) {
		PausedWindow();
	}
}

void Game::DrawScore() {
	DrawRectangle(0, screenHeight - 50, screenHeight, 50, BLACK);
	DrawRectangleLinesEx(Rectangle{ 0, screenHeight - 50, screenWidth, 50 }, 3, WHITE);
	DrawText(TextFormat("SCORE:%i", score), 10, screenHeight - 35, 20, WHITE);
	DrawText(TextFormat("HIGHSCORE:%i", HighScore), screenWidth - 10 - MeasureText(TextFormat("HIGHSCORE:%i", HighScore), 20), screenHeight - 35, 20, WHITE);
}

void Game::UnloadGameTxt() {
	for (int i = 0; i < bulletNum; i++) {
		b[i].UnloadTxt();
	}

	for (int i = 0; i < wave * 10; i++) {
		e[i].UnloadTxt();
	}
	s.UnloadTxt();
	p.UnloadTxt();
}

void Game::GameTimer() {
	gameTime += 1.0f * GetFrameTime(); //counting time
}

void Game::PausedWindow() {
	DrawRectangleRec(RectPausedWindow, BLACK);
	DrawRectangleLinesEx(RectPausedWindow, PausedWindowFrameThick, WHITE);
	DrawText("GAME PASUED", centerX - MeasureText("GAME PAUSED", 30) / 2, centerY - PausedWindowHeight / 2 + PausedWindowFrameThick * 4, 30, WHITE);
	DrawText("Press [P] to unpause", centerX - MeasureText("Press [P] to unpause", 25) / 2, centerY + PausedWindowHeight / 2 - PausedWindowFrameThick * 8, 25, WHITE);
}

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