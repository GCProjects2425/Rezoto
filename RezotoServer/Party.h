#pragma once
#include <string>
#include <vector>

struct Player
{
	std::string ip;
	std::string username;
	int connectionStart;
};

struct Vector2f
{
	float x;
	float y;
};

enum GameState
{
	IDLE,
	PAUSE,
	PLAY
};

class Party
{
	//Room variables
	std::vector<Player> m_vPlayerList;
	int m_score;
	int id;

	//Game variables
	Vector2f m_vBallPos;
	Vector2f m_vPlayerPos1;
	Vector2f m_vPlayerPos2;
};

