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
    Rectangle recPlayer  { x, y, width, height };
public:
    Player();
    Player(float, float, float, float);
    float getWidth();
    float getHeight();
    float getX();
    void setX(float);
    float getY();
    void setY(float);
    void setSpeedX(float);
    void setSpeedY(float);
    void setHealth(float);
    float getHealth();
    void UpdateControlling();
    void UpdateFrames();
    void Draw();
    void UnloadTxt();
    Rectangle getRect();
};

#endif
