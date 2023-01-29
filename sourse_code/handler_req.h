#pragma once
#include <iostream>

class HTTP
{
public:

	void sendHTTP(std::string target);

};

class Socket {
private:
	char* generateData(int dataSize);

public:

	void sendUDPPacket(char* destIP, int destPort);

	void sendTCPPacket(char* destIP, int destPort);

};