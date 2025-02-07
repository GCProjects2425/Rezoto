#pragma once
#include <string>
#include <iostream>
#include <sstream>

// MESSAGE SERVER
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
	std::string ip;
	int port;
	uint32_t sequenceNumber; 

	Message() : type(None), port(0) {};
	Message(MessageType msgType, std::string msg) : type(msgType), message(std::move(msg)), port(0) {}
	explicit Message(MessageType msgType, std::string msg, std::string ipSender, int portSender) : type(msgType), message(std::move(msg)), ip(std::move(ipSender)), port(portSender) {}

	std::string toString() const {
		return std::to_string(type) + "|" + message + "|" + std::to_string(sequenceNumber);
	}

	static Message fromString(const std::string& str) {
		Message msg;
		std::stringstream ss(str);
		std::string v1, v2, v3;

		std::getline(ss, v1, '|');
		std::getline(ss, v2, '|');
		std::getline(ss, v3, '|');

		msg.type = static_cast<MessageType>(std::stoi(v1));
		msg.message = v2;
		msg.sequenceNumber = static_cast<uint32_t>(std::stoul(v3)); // Conversion;

		return msg;
	}
};

