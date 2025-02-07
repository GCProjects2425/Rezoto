#pragma once
#include <string>
#include <iostream>
#include <sstream>

struct Message
{
	enum MessageType {
		None = 0,
		Ping,
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

	MessageType type;
	std::string message;

	Message() : type(None) {};
	explicit Message(MessageType msgType, std::string msg) : type(msgType), message(std::move(msg)) {}

	std::string toString() const {
		return std::to_string(type) + "|" + message;
	}

	static Message fromString(const std::string& str) {
		Message msg;
		std::stringstream ss(str);
		std::string v1, v2;

		std::getline(ss, v1, '|');
		std::getline(ss, v2, '|');

		msg.type = static_cast<MessageType>(std::stoi(v1));
		msg.message = v2;

		return msg;
	}
};

