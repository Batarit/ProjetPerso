#pragma once
#include <vector>

#define SERVEUR "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT_R 5232	//The port on which to listen for incoming data
#define PORT_S 8888	


typedef void (*fonctionCalled)(std::string*);

class string;

using namespace std;

struct addresseServeur
{
	int size = 10;
	int actualPose = 0;
	struct sockaddr_in addrOuts;
	void Connection(const char* _addrOut);
	char nbMessage;
	class mutex* mLock;
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

	class mutex* mLock;

	std::vector<fonctionCalled> ftab;

public:

	void SendMSGR(std::string* msg);
	void ThreadSendMSGR(std::string* msg);

	void SendMSG();
	void ThreadSendMSG();

	void Reiceived();
	void ThreadReiceived();

	void SetBuffer(char msgT, const char* msg);
	std::string* GetBuffer();

	void AddFunction(fonctionCalled FC);
};
