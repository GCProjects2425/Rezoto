#pragma once
#include <string>
#include <iostream>
#include <sstream>

struct Message
{
	enum MesageType {
		Ping = 0,
		Connect,
		Disconnect,
		GameStatus,
		Ready,
		Unready,
		Play,
		Stop,
		Win,
		Lose
	};

	MesageType type;
	char message[0xFFFF-0xFF];

	std::string toString() const {
		return std::to_string(type) + "|" + message;
	}

	static Message fromString(const std::string& str) {
		Message msg;
		std::stringstream ss(str);
		std::string v1, v2;

		std::getline(ss, v1, '|');
		std::getline(ss, v2, '|');

		msg.type = static_cast<MesageType>(std::stoi(v1));

		switch (msg.type)
		{
		case Ping:
			// ping behaviour
			break;
		default:
			break;
		}

		return msg;
	}
};

