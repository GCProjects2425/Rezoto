#include "GameManager.h"
#include "UDPServer.h"

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

void GameManager::Update()
{
	for (Party& party : m_lParties)
	{
		//UPDATE GAME
		party.ComputeGame();

		//SEND GAMESTATUS INFOS TO ALL CLIENTS
		std::vector<Player*> playerList = party.GetPlayerList();
		for (int i = 0; i < playerList.size(); i++)
		{
			GameStatus* gameStatus = new GameStatus();

			gameStatus->m_BallPos = party.GetBallPos();
			gameStatus->m_LeftRacketPos = party.GetLeftRacketPos();
			gameStatus->m_RightRacketPos = party.GetRightRacketPos();

			UDPServer::GetInstance()->PushMessage(Message::GameStatus, gameStatus->toString(), playerList[i]->ip, 8888);
			
			////BALL POS
			//m_server->PushMessage(Message::GameStatus, party.GetBallPos().toString(), playerList[i]->ip, 8888);

			////RACKETS POS
			//m_server->PushMessage(Message::GameStatus, party.GetLeftRacketPos().toString(), playerList[i]->ip, 8888);
			//m_server->PushMessage(Message::GameStatus, party.GetRightRacketPos().toString(), playerList[i]->ip, 8888);

			////SCORES & WINNER
			//m_server->PushMessage(Message::GameStatus, std::to_string(party.GetLeftScore()), playerList[i]->ip, 8888);
			//m_server->PushMessage(Message::GameStatus, std::to_string(party.GetRightScore()), playerList[i]->ip, 8888);
			//m_server->PushMessage(Message::GameStatus, std::to_string(party.GetWinner()), playerList[i]->ip, 8888);
		}
	}
}
