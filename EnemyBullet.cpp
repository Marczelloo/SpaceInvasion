#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {};

EnemyBullet::EnemyBullet(float x, float y, float speed, bool active) {
	this->speed = speed;
	this->x = x;
	this->y = y;
	this->active = active;
};

void EnemyBullet::setX(float x) {
	this->x = x;
};

float EnemyBullet::getX() {
	return x;
}

void EnemyBullet::setY(float y) {
	this->y = y;
}

float EnemyBullet::getY() {
	return y;
}

void EnemyBullet::setSpeed(float speed) {
	this->speed = speed;
}

float EnemyBullet::getSpeed() {
	return speed;
}

void EnemyBullet::setActive(bool active) {
	this->active = active;
}

bool EnemyBullet::getActive() {
	return active;
}

float EnemyBullet::getWidth() {
	return width;
}

float EnemyBullet::getHeight() {
	return height;
}

Rectangle EnemyBullet::getRect() {
	return recEnemyBullet;
}

void EnemyBullet::Draw() {
	DrawTextureEx(enemyBullet, Vector2{ x + width / 2, y + height / 2}, 180.0f, 1.0f, WHITE);
}

void EnemyBullet::UnloadTxt() {
	UnloadTexture(enemyBullet);
}

void EnemyBullet::Update() {
		y = y + speed * GetFrameTime();
		if (y > 800) {
			active = false;
		}
}