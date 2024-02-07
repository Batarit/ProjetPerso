#pragma once
#include <vector>

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT_R 8888	//The port on which to listen for incoming data
#define PORT_S 5232



struct addresseClients
{
	int size = 10;
	int actualPose = 0;
	std::vector<struct sockaddr_in*> addrOuts;
	void Connection(char* _addrOut);
	void DisConnection(char* _addrOut);
	std::vector<char> nbMessage;
};

class ReseauxConnection
{
public:
	ReseauxConnection();
	~ReseauxConnection();

private:
	int socketS;
	struct sockaddr_in* addrIn;
	addresseClients addrOutClients;
	char buf[BUFLEN];
	struct WSAData* wsa;
	int slen = sizeof(addrOutClients);;

public:

	void SendMSGR(int who, const char* msg);

	void SendMSG(int who);

	void Reiceived();
};
