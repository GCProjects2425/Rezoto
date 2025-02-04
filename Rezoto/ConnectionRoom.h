#pragma once
#include "GameScreen.h"
#include "pong.h"
#include "vector"
#include "UiElement.h"
#include "InputField.h"

class ConnectionRoom :
    public GameScreen
{
public:
    ConnectionRoom();

    std::vector<UiElement*> UiElements;
    void ComputeLogic(Pong* pong) override;
    void Draw(Pong* pong) override;
    void StartScreen(Pong* pong) override;
};

