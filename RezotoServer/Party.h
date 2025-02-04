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
public:
	Party();

	int GetID() const { return m_ID; }
private:
	//Room variables
	std::vector<Player*> m_vPlayerList;
	int m_score;
	int m_ID;

	//Game variables
	Vector2f m_vBallPos{ 0 };
	Vector2f m_vPlayerPos1{ 0 };
	Vector2f m_vPlayerPos2{ 0 };

	Vector2f m_vWindowSize{ 0 };
};

