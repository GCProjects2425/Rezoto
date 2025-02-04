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
