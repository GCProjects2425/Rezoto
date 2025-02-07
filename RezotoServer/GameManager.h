#pragma once
#include <list>
#include "Singleton.h"
#include "Party.h"
#include "UDPServer.h"

class GameManager final : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	typedef std::list<Party> PartyList;
	
	GameManager();
	int CreateParty();

	Party* FindPartyByID(int searchID);
	int RemovePartyByID(int searchID);
	void Update();
	const PartyList& GetPartyList() const { return m_lParties; }
private:
	PartyList m_lParties;
	UDPServer* m_server;
};

