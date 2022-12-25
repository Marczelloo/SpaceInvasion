#pragma once

#include <raylib.h>

class Bullet {
	Texture2D bullet = LoadTexture("assets/bullet.png");
	float x, y;
	float width = bullet.width, height = bullet.height;
	float speed;
	bool active;
	Rectangle recBullet{ x, y, width, height };
public:
	Bullet();
	Bullet(float x, float y, float speed, bool active);
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setSpeed(float speed);
	float getSpeed();
	void setActive(bool active);
	bool getActive();
	float getWidth();
	float getHeight();
	Rectangle getRect();
	void Draw();
	void UnloadTxt();
};