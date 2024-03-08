#pragma once
#include <vector>

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT_R 8888	//The port on which to listen for incoming data
#define PORT_S 5232


class string;

struct addresseClients
{
	int size = 10;
	int actualPose = 0;
	std::vector<struct sockaddr_in> addrOuts;
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
	SOCKET socketS;
	struct sockaddr_in addrIn;
	addresseClients addrOutClients;
	std::string* buf;
	struct WSAData wsa;
	int slen = sizeof(addrOutClients);;
	char nbOfMessage = 0;

public:

	void SendMSGR(int who, const char* msg);
	void ThreadSendMSGR(int who, const char* msg);

	void SendMSG(int who);
	void ThreadSendMSG(int who);

	void Reiceived();
	void ThreadReiceived();

	void SetBuffer(char msgT, const char* msg);

};
