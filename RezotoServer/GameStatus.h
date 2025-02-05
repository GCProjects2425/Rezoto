#pragma once
#include "CustomStruct.h"
#include <string>
struct GameStatus
{
	Vector2f player1PaddlePos;
	Vector2f player2PaddlePos;
	Vector2f ballPos;

    std::string toString() const {
        return player1PaddlePos.toString() + ";" + player2PaddlePos.toString() + ";" + ballPos.toString();
    }

    static GameStatus fromString(const std::string& str) {
        GameStatus gs;
        std::stringstream ss(str);
        std::string v1, v2, v3;

        std::getline(ss, v1, ';');
        std::getline(ss, v2, ';');
        std::getline(ss, v3, ';');

        gs.player1PaddlePos = Vector2f::fromString(v1);
        gs.player2PaddlePos = Vector2f::fromString(v2);
        gs.ballPos = Vector2f::fromString(v3);

        return gs;
    }
};

