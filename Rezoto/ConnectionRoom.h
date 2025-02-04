#pragma once
#include "GameScreen.h"
#include "pong.h"
class ConnectionRoom :
    public GameScreen
{
public:
    Rectangle textBox = { 800 / 2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;
    char name[12 + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    int framesCounter = 0;
    void ComputeLogic(Pong* pong) override;
    void Draw(Pong* pong) override;
    void StartScreen(Pong* pong) override;
};

