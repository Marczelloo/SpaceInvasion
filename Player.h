#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
    Texture2D Spaceship = LoadTexture("assets/sprite_spaceship.png");
    float spaceShipFrameWidth = Spaceship.width / 6.0f;
    float spaceShipFrameHeight = (float)Spaceship.height;
    float x, y;
    float speedX, speedY;
    float width = spaceShipFrameWidth, height = spaceShipFrameHeight;
    float frame = 0;
    float health = 100;
    Rectangle recPlayer{ x, y, width, height };
public:
    Player();
    Player(float x, float y, float speedX, float speedY);
    float getWidth();
    float getHeight();
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    void setSpeedX(float speedX);
    void setSpeedY(float speedY);
    void setHealth(float health);
    float getHealth();
    void UpdateControlling();
    void UpdateFrames();
    void Draw();
    void UnloadTxt();

};

#endif
