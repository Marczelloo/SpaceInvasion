#pragma once

#include <raylib.h>

class Enemy {
	Texture2D enemy = LoadTexture("assets/sprite_enemy.png");
	static const int enemyBulletNum = 5;
	float x, y;
	float speedX, speedY;
	float width = enemy.width / 2, height = enemy.height;
	int frame = 0;
	float health;
	float timeToShoot = 0;
	float hitTime = 0;
	float randTime = 0;
	Rectangle recEnemy;
	bool active;
	bool shooting;
	bool hit;
	Rectangle recEnemyCollision{ x - enemy.width / 4, y - enemy.width / 2, width, height };
public:
	Enemy();
	Enemy(float , float , float , float, float);
	void setX(float);
	void setY(float);
	void setSpeedX(float);
	void setSpeedY(float);
	void setHealth(float);
	void setActive(bool);
	void setFrame(int);
	float getX();
	float getY();
	float getSpeedX();
	float getSpeedY();
	float getHealth();
	float getWidth();
	float getHeight();
	bool getActive();
	void setShooting(bool);
	bool getShooting();
	void setHit(bool);
	bool getHit();
	Rectangle getRecEnemyCollision();
	void Update();
	void Draw();
	void UnloadTxt();
};
