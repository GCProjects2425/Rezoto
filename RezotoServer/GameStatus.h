#pragma once
#include "CustomStruct.h"
#include <string>
struct GameStatus
{
    LeVector2 player1PaddlePos;
    LeVector2 player2PaddlePos;
    LeVector2 ballPos;

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

        gs.player1PaddlePos = LeVector2::fromString(v1);
        gs.player2PaddlePos = LeVector2::fromString(v2);
        gs.ballPos = LeVector2::fromString(v3);

        return gs;
    }
};
