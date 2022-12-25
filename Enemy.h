#pragma once

#include <raylib.h>

class Enemy {
	Texture2D enemy = LoadTexture("assets/sprite_enemy.png");
	float x, y;
	float speedX, speedY;
	float width = enemy.width / 2, height = enemy.height;
	int frame = 0;
	float health;
	Rectangle recEnemy;
	bool active;
	Rectangle recEnemyCollision{ x - enemy.width / 4, y - enemy.width / 2, width, height };
public:
	Enemy();
	Enemy(float x, float y, float speedX, float speedY, float health);
	void setX(float x);
	void setY(float y);
	void setSpeedX(float speedX);
	void setSpeedY(float speedY);
	void setHealth(float health);
	void setActive(bool active);
	void setFrame(int frame);
	float getX();
	float getY();
	float getSpeedX();
	float getSpeedY();
	float getHealth();
	float getWidth();
	float getHeight();
	bool getActive();
	Rectangle getRecEnemyCollision();
	void Update();
	void Draw();
	void UnloadTxt();
};
