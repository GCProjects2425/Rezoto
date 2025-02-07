#pragma once
#include <list>
#include "Singleton.h"
#include "Party.h"
#include "GameStatus.h"

class GameManager final : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	typedef std::list<Party> PartyList;
	typedef std::list<Player> PlayerList;
	
	GameManager();
	int CreateParty();
	int RegisterPlayer(const std::string& ip, const std::string& username, int port);

	Party* FindPartyByID(int searchID);
	int RemovePartyByID(int searchID);
	void ManageMessages();
	const PartyList& GetPartyList() const { return m_lParties; }

	Player* FindPlayerByIP(const std::string& searchIP);
	int RemovePlayerByIP(const std::string& searchIP);
	const PlayerList& GetPlayerList() const { return m_lPlayers; }

	const bool IsPlayerListUpdated();

	void Run();
private:
	void Update();
	
	PartyList m_lParties;
	PlayerList m_lPlayers;

	bool m_isPlayerListUpdated = false;
};

