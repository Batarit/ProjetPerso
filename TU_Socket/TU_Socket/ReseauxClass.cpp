#include "ReseauxClass.h"
#include <thread>

void ReseauxClass::init()
{
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		exit(1);
	}

	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888); // Port number
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		closesocket(serverSocket);
		WSACleanup();
		exit(1);
	}

}

void ReseauxClass::disconect()
{
	closesocket(serverSocket);
	WSACleanup();
}

ReseauxClass::~ReseauxClass()
{
	disconect();
}
