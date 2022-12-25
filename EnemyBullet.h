#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <raylib.h>
#include <iostream>

class EnemyBullet {
private:
	Texture2D enemyBullet = LoadTexture("assets/bullet_enemy.png");
	float x, y;
	float width = enemyBullet.width, height = enemyBullet.height;
	float speed;
	bool active;
	Rectangle recEnemyBullet{ x, y, width, height};
public:
	EnemyBullet();
	EnemyBullet(float, float, float, bool);
	void setX(float);
	float getX();
	void setY(float);
	float getY();
	void setSpeed(float);
	float getSpeed();
	void setActive(bool);
	bool getActive();
	float getWidth();
	float getHeight();
	Rectangle getRect();
	void Draw();
	void UnloadTxt();
	void Update();
};