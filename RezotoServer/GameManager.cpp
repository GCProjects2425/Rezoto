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

	m_isPartyListUpdated = true;
	return it.GetID();
}

int GameManager::RegisterPlayer(const std::string& ip, const std::string& username, int port)
{
	Player& it = m_lPlayers.emplace_back(ip, username, port);

	m_isPlayerListUpdated = true;
    return 0;
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

const bool GameManager::IsPlayerListUpdated()
{
	if (m_isPlayerListUpdated)
	{
		m_isPlayerListUpdated = false;
		return true;
	}
	return false;
}

const bool GameManager::IsPartyListUpdated()
{
	if (m_isPartyListUpdated)
	{
		m_isPartyListUpdated = false;
		return true;
	}
	return false;
}

void GameManager::Run()
{
	while (true)
	{
		Update();
	}
}

void GameManager::Update()
{
	ManageMessages();

	for (Player& player : m_lPlayers)
	{
		if (time(0) - player.lastPing > 3)
		{
			if (RemovePlayerByIP(player.ip) > 0)
				break;
		}
	}

	if (m_lPlayers.size() > 1 && m_lParties.size() == 0)
	{
		CreateParty();
		m_lParties.back().AddPlayer(&m_lPlayers.front());
		m_lParties.back().AddPlayer(&m_lPlayers.back());
	}

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
			
			//TODO SEND SCORE & WINNER ON MODIFIED CONDITION

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

void GameManager::PingPlayer(const std::string& ip)
{
	if (Player* player = FindPlayerByIP(ip))
	{
		player->lastPing = time(0);
	}
}

void GameManager::ManageMessages()
{
	while (!UDPServer::GetInstance()->IsEmpty())
	{
		std::shared_ptr<Message> message = UDPServer::GetInstance()->PopReceivedMessage();
		if (message == nullptr) continue;
		switch (message->type)
		{
		case Message::Ping:
			PingPlayer(message->ip);
			break;
		case Message::Connect:
			RegisterPlayer(message->ip, message->message, message->port);
			break;
		case Message::Disconnect:
			RemovePlayerByIP(message->ip);
			break;
		case Message::Ready:
			break;
		case Message::Unready:
			break;
		case Message::Play:
			break;
		case Message::Stop:
			break;
		case Message::Win:
			break;
		case Message::Lose:
			break;
		default:
			break;
		}
	}
}

Player* GameManager::FindPlayerByIP(const std::string& searchIP)
{
    for (Player& player : m_lPlayers) {
        if (player.ip == searchIP) {
            return &player;
        }
    }
    return nullptr;
}

int GameManager::RemovePlayerByIP(const std::string& searchIP)
{
    for (PlayerList::iterator it = m_lPlayers.begin(); it != m_lPlayers.end(); ++it) {
        if (it->ip == searchIP) {
            m_lPlayers.erase(it);
			m_isPlayerListUpdated = true;
            return 1;
        }
    }
    return -1;
}
