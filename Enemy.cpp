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

void Enemy::setShooting(bool shooting) {
	this->shooting = shooting;
};

bool Enemy::getShooting() {
	return shooting;
}
	
Rectangle Enemy::getRecEnemyCollision() {
	return recEnemyCollision;
}

void Enemy::setHit(bool hit) {
	this->hit = hit;
}

bool Enemy::getHit() {
	return hit;
}

void Enemy::Update() {
	if (active) {
		shooting = false;
		recEnemy = { frame * (float)enemy.width / 2, 0, (float)enemy.width / 2, (float)enemy.height };
		timeToShoot += 1 * GetFrameTime();
		if (timeToShoot >= 2) {
			timeToShoot = 0;
			if (GetRandomValue(1, 100) <= 20)
				shooting = true;
		}
		if (hit) {
			hitTime += 1 * GetFrameTime();
			if (hitTime >= 0.200f) {
				hit = false;
			}
		}
	}
}

void Enemy::Draw() {
	if (!hit) {
		DrawTextureRec(enemy, recEnemy, Vector2{ x - enemy.width / 4, y - enemy.height / 2 }, WHITE);
	}
	else {
		DrawTextureRec(enemy, recEnemy, Vector2{ x - enemy.width / 4, y - enemy.height / 2 }, Color{239, 88, 88, 255});
	}
}

void Enemy::UnloadTxt() {
	UnloadTexture(enemy);
}
