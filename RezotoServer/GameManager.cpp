#include "GameManager.h"

GameManager::GameManager()
{
	srand((unsigned int)time(NULL));
}

int GameManager::CreateParty()
{
	if (m_lParties.size() >= 20) return -1;

	Party& it = m_lParties.emplace_back();

	return it.GetID();
}

Party* GameManager::FindPartyByID(int searchID)
{
    for (Party& party : m_lParties) {
        if (party.GetID() == searchID) {
            return &party;
        }
    }
    return nullptr;
}

int GameManager::RemovePartyByID(int searchID)
{
    for (PartyList::iterator it = m_lParties.begin(); it != m_lParties.end(); ++it) {
        if (it->GetID() == searchID) {
            m_lParties.erase(it);
            return 1;
        }
    }
    return -1;
}
