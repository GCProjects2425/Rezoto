#pragma once
#include <list>
#include "Singleton.h"
#include "Party.h"
class GameManager final : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	typedef std::list<Party> PartyList;
	
	GameManager();
	int CreateParty();

	const PartyList& GetPartyList() const { return m_lParties; }
private:
	PartyList m_lParties;
};

