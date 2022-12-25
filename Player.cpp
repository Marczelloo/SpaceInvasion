#include "Player.h"
#include "Consts.cpp"

Player::Player() {}

Player::Player(float x, float y, float speedX, float speedY) {
    this->x = x;
    this->y = y;
    this->speedX = speedX;
    this->speedX = speedX;
    this->speedY = speedY;
}

float Player::getWidth() {
    return width;
}

float Player::getHeight() {
    return height;
}

float Player::getX() {
    return x;
}

void Player::setX(float x) {
    this->x = x;
}

float Player::getY() {
    return y;
}

void Player::setY(float y) {
    this->y = y;
}

void Player::setSpeedX(float speedX) {
    this->speedX = speedX;
}

void Player::setSpeedY(float speedY) {
    this->speedY = speedY;
}

void Player::setHealth(float health) {
    this->health = health;
}

float Player::getHealth() {
    return health;
}

void Player::UpdateControlling() {
    if (IsKeyDown(KEY_W)) {
        if (y >= 0 + height / 2) {
            y -= speedX * GetFrameTime();
        }
    }
    if (IsKeyDown(KEY_S)) {
        if (y <= screenHeight - height / 2) {
            y += speedX * GetFrameTime();
        }
    }
    if (IsKeyDown(KEY_A)) {
        if (x >= 0 + width / 2) {
            x -= speedX * GetFrameTime();
        }
    }
    if (IsKeyDown(KEY_D)) {
        if (x <= screenWidth - width / 2) {
            x += speedX * GetFrameTime();
        }
    }
}

void Player::UpdateFrames() {
    if (IsKeyDown(KEY_W)) {
        frame = spaceShipFrameWidth * 1;
    }
    if (IsKeyDown(KEY_S)) {
        frame = 0;
    }
    if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_S)) {
        frame = 0;
    }
    if (IsKeyDown(KEY_D)) {
        frame = spaceShipFrameWidth * 2;
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
            frame = spaceShipFrameWidth * 3;
        }
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) {
            frame = 0;
        };
    }
    if (IsKeyDown(KEY_A)) {
        frame = spaceShipFrameWidth * 4;
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
            frame = spaceShipFrameWidth * 5;
        };
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) {
            frame = 0;
        };
    };
}

void Player::Draw() {
    DrawTextureRec(Spaceship, Rectangle{ frame, 0, (float)spaceShipFrameWidth, (float)spaceShipFrameHeight }, Vector2{ x - width / 2, y - height / 2 }, WHITE);
}

void Player::UnloadTxt() {
    UnloadTexture(Spaceship);
}