#pragma once
#include <vector>

#define SERVEUR "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT_R 5232	//The port on which to listen for incoming data
#define PORT_S 8888	



class string;

struct addresseServeur
{
	int size = 10;
	int actualPose = 0;
	struct sockaddr_in addrOuts;
	void Connection(const char* _addrOut);
	char nbMessage;
};

class ReseauxConnection
{
public:
	ReseauxConnection();
	~ReseauxConnection();

private:
	SOCKET socketS;
	struct sockaddr_in addrIn;
	addresseServeur addrOutServeur;
	std::string* buf;
	struct WSAData wsa;
	int slen = sizeof(addrOutServeur);
	char nbOfMessage = 0;
public:

	void SendMSGR(const char* msg);
	void ThreadSendMSGR(const char* msg);

	void SendMSG();
	void ThreadSendMSG();

	void Reiceived();
	void ThreadReiceived();

	void SetBuffer(char msgT, const char* msg);
};
