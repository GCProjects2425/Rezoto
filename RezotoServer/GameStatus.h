#pragma once
#include "CustomStruct.h"
#include <string>
struct GameStatus
{
    LeVector2 m_LeftRacketPos;
    LeVector2 m_RightRacketPos;
    LeVector2 m_BallPos;

    std::string toString() const {
        return m_LeftRacketPos.toString() + ";" + m_RightRacketPos.toString() + ";" + m_BallPos.toString();
    }

    static GameStatus fromString(const std::string& str) {
        GameStatus gs;
        std::stringstream ss(str);
        std::string v1, v2, v3;

        std::getline(ss, v1, ';');
        std::getline(ss, v2, ';');
        std::getline(ss, v3, ';');

        gs.m_LeftRacketPos = LeVector2::fromString(v1);
        gs.m_RightRacketPos = LeVector2::fromString(v2);
        gs.m_BallPos = LeVector2::fromString(v3);

        return gs;
    }
};
