#pragma once
#include <string>
#include <iostream>
#include <sstream>

struct Message
{
	static uint32_t globalSequenceNumber;

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
	uint32_t sequenceNumber; // Numéro de séquence en 3e ligne

	Message() : type(None), message(""), sequenceNumber(0) {};
	explicit Message(MessageType msgType, std::string msg, uint32_t seqNum)

		: type(msgType), message(std::move(msg)), sequenceNumber(globalSequenceNumber++) {
	}

	std::string toString() const {
		return std::to_string(type) + "|" + message + "|" + std::to_string(sequenceNumber);
	}

	static Message fromString(const std::string& str) {
		Message msg;
		std::stringstream ss(str);
		std::string v1, v2, v3;

		std::getline(ss, v1, '|'); // Type de message
		std::getline(ss, v2, '|'); // Contenu du message
		std::getline(ss, v3, '|'); // Numéro de séquence

		msg.type = static_cast<MessageType>(std::stoi(v1));
		msg.message = v2;
		msg.sequenceNumber = static_cast<uint32_t>(std::stoul(v3));

		return msg;
	}
};
