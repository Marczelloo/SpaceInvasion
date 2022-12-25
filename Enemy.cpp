#include "Enemy.h"

Enemy::Enemy() {};

Enemy::Enemy(float x, float y, float speedX, float speedY, float health) {
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->health = health;
};

void Enemy::setX(float x) {
	this->x = x;
}

void Enemy::setY(float y) {
	this->y = y;
}

void Enemy::setSpeedX(float speedX) {
	this->speedX = speedX;
}

void Enemy::setSpeedY(float speedY) {
	this->speedY = speedY;
}

void Enemy::setHealth(float health) {
	this->health = health;
}

void Enemy::setActive(bool active) {
	this->active = active;
}

void Enemy::setFrame(int frame) {
	this->frame = frame;
}

float Enemy::getX() {
	return x;
}

float Enemy::getY() {
	return y;
}

float Enemy::getSpeedX() {
	return speedX;
}

float Enemy::getSpeedY() {
	return speedY;
}

float Enemy::getHealth() {
	return health;
}

float Enemy::getWidth() {
	return width;
}

float Enemy::getHeight() {
	return height;
}

bool Enemy::getActive() {
	return active;
}

Rectangle Enemy::getRecEnemyCollision() {
	return recEnemyCollision;
}

void Enemy::Update() {
	recEnemy = { frame * (float)enemy.width / 2, 0, (float)enemy.width / 2, (float)enemy.height };
}

void Enemy::Draw() {
	DrawTextureRec(enemy, recEnemy, Vector2{ x - enemy.width / 4, y - enemy.height / 2 }, WHITE);
}

void Enemy::UnloadTxt() {
	UnloadTexture(enemy);
}
