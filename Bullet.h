#pragma once

#include <raylib.h>

class Bullet {
private:
	Texture2D bullet = LoadTexture("assets/bullet.png");
	float x, y;
	float width = bullet.width, height = bullet.height;
	float speed;
	bool active;
	Rectangle recBullet{ x, y, width, height };
public:
	Bullet();
	Bullet(float, float, float, bool);
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
};