#pragma once

#include <WinSock2.h>

class ReseauxClass
{
private:
	SOCKET serverSocket;
	WSADATA wsaData;

public:

	void init();

	void disconect();

	~ReseauxClass();
};

