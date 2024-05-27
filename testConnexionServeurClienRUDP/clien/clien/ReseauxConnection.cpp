#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <thread>         // std::thread
#include<stdio.h>
#include<winsock2.h>
#include <Mstcpip.h>
#include <iostream>
#include <string>
#include <mutex>
#include "ReseauxConnection.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)


ReseauxConnection::ReseauxConnection()
{
	mLock = new	std::mutex;
	buf = new std::string;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");


	//Prepare the sockaddr_in structure
	addrIn.sin_family = AF_INET;
	addrIn.sin_addr.s_addr = INADDR_ANY;
	addrIn.sin_port = htons(PORT_R);
	//Bind
	if (bind(socketS, (struct sockaddr*)&addrIn, sizeof(addrIn)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	addrOutServeur.mLock = new std::mutex;
	addrOutServeur.Connection(SERVEUR);

	BOOL bNewBehavior = FALSE;
	DWORD dwBytesReturned = 0;
	WSAIoctl(socketS, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);
}

ReseauxConnection::~ReseauxConnection()
{
	delete buf;
	delete mLock;
	delete addrOutServeur.mLock;
	closesocket(socketS);
	WSACleanup();
}

void ReseauxConnection::SendMSGR(std::string* msg)
{
	const char* buffer = msg->c_str();
	mLock->lock();

	std::cout << "tu envoie quoi " << msg << std::endl;
	if (sendto(socketS, buffer, BUFLEN, 0, (struct sockaddr*)&addrOutServeur.addrOuts, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	mLock->unlock();
}

void ReseauxConnection::ThreadSendMSGR(std::string* msg)
{
	std::thread(&ReseauxConnection::ThreadSendMSGR, this, msg).detach();
}

void ReseauxConnection::SendMSG()
{
	const char* buffer = buf->c_str();
	int32_t count = 0;

	ThreadReiceived();
	while (count <= 200 && addrOutServeur.nbMessage != buffer[1])
	{

		mLock->lock();
		if (sendto(socketS, buffer, BUFLEN, 0, (struct sockaddr*)&addrOutServeur.addrOuts, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		std::cout << buffer << " with nbM = " << addrOutServeur.nbMessage << " attendu = " << buffer[1] << std::endl;
		mLock->unlock();


		Sleep(500);
	}
	if (count > 200)
	{
		std::cout << "lost info" << std::endl;
	}
	buf->clear();
}

void ReseauxConnection::ThreadSendMSG()
{
	std::thread(&ReseauxConnection::SendMSG, this).detach();
}

void ReseauxConnection::Reiceived()
{
	struct sockaddr_in temp;
	char buf[BUFLEN];
	////receive a reply and print it
////clear the buffer by filling null, it might have previously received data
	////try to receive some data, this is a blocking call


	printf("Waiting for data...\n");
	fflush(stdout);
	memset(buf, '\0', BUFLEN);
	if (recvfrom(socketS, buf, BUFLEN, 0, (struct sockaddr*)&temp, &slen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	ThreadReiceived();

	if (addrOutServeur.addrOuts.sin_addr.S_un.S_addr == temp.sin_addr.S_un.S_addr)
	{


		if (buf[0] == 'R')
		{
			mLock->lock();
			addrOutServeur.nbMessage = buf[1];
			mLock->unlock();
		}
		else if (buf[0] == 'S')
		{
			std::cout << "SEND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

			std::string message = "R";
			message += buf[1];


			ThreadSendMSGR(&message);
		}
		printf("Received packet from %s:%d\n", inet_ntoa(temp.sin_addr), ntohs(temp.sin_port));
		printf("Data: %s\n", buf);
	}
}

void ReseauxConnection::ThreadReiceived()
{
	std::thread(&ReseauxConnection::Reiceived, this).detach();
}

void ReseauxConnection::SetBuffer(char msgT, const char* msg)
{
	mLock->lock();
	buf->clear();
	buf->push_back(msgT);
	if (nbOfMessage > CHAR_MAX)
	{
		nbOfMessage = 0;
	}
	buf->push_back((char)nbOfMessage);
	int i = 0;
	while (msg[i] != '\0')
	{
		buf->push_back(msg[i]);
		i++;
	}
	nbOfMessage++;
	mLock->unlock();

}

std::string* ReseauxConnection::GetBuffer()
{
	return buf;
}

void addresseServeur::Connection(const char* _addrOut)
{
	struct sockaddr_in temp;
	memset((char*)&temp, 0, sizeof(temp));
	temp.sin_family = AF_INET;
	temp.sin_port = htons(PORT_S);
	temp.sin_addr.S_un.S_addr = inet_addr(_addrOut);
	mLock->lock();
	addrOuts = temp;
	nbMessage = -1;
	mLock->unlock();

}
