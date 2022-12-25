#include "Bullet.h";

Bullet::Bullet(){};

Bullet::Bullet(float x, float y, float speed, bool active){
	this->speed = speed;
	this->x = x;
	this->y = y;
	this->active = active;
}

void Bullet::setX(float x) {
	this->x = x;
}

float Bullet::getX() {
	return x;
}

void Bullet::setY(float y) {
	this->y = y;
}

float Bullet::getY() {
	return y;
}

void Bullet::setSpeed(float speed) {
	this->speed = speed;
}

float Bullet::getSpeed() {
	return speed;
}

void Bullet::setActive(bool active) {
	this->active = active;
}

bool Bullet::getActive() {
	return active;
}

float Bullet::getWidth() {
	return width;
}

float Bullet::getHeight() {
	return height;
}

Rectangle Bullet::getRect() {
	return recBullet;
}

void Bullet::Draw() {
	DrawTexture(bullet, x, y, WHITE);
}

void Bullet::UnloadTxt() {
	UnloadTexture(bullet);
}