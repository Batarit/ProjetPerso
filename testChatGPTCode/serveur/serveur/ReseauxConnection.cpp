#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <thread>         // std::thread
#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <string>
#include "ReseauxConnection.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library


ReseauxConnection::ReseauxConnection()
{
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
}

ReseauxConnection::~ReseauxConnection()
{
	delete buf;
	closesocket(socketS);
	WSACleanup();
}

void ReseauxConnection::SendMSGR(int who, const char* msg)
{
	if (who < addrOutClients.addrOuts.size())
	{
		std::cout << "tu envoie quoi " << msg << std::endl;
		if (sendto(socketS, msg, sizeof(msg[0]) * (BUFLEN-1), 0, (struct sockaddr*)&addrOutClients.addrOuts[who], slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
}

void ReseauxConnection::ThreadSendMSGR(int who, const char* msg)
{
	std::thread(&ReseauxConnection::SendMSGR, this, who, msg).detach();
}

void ReseauxConnection::SendMSG(int who)
{
	const char* buffer = buf->c_str();
	int32_t count = 0;
	if (who < addrOutClients.addrOuts.size())
	{
		ThreadReiceived();
		while (count <= INT32_MAX && addrOutClients.nbMessage[who] != buffer[1])
		{

			if (sendto(socketS, buffer, BUFLEN, 0, (struct sockaddr*)&addrOutClients.addrOuts[who], slen) == SOCKET_ERROR)
			{
				printf("sendto() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}

			Sleep(500);
		}
	}
}

void ReseauxConnection::ThreadSendMSG(int who)
{
	std::thread(&ReseauxConnection::SendMSG, this, who).detach();
}

void ReseauxConnection::Reiceived()
{
	struct sockaddr_in temp;
	char buf[BUFLEN];
	////receive a reply and print it
////clear the buffer by filling null, it might have previously received data
	////try to receive some data, this is a blocking call


		printf("Waiting for data...");
		fflush(stdout);
		memset(buf, '\0', BUFLEN);
		if (recvfrom(socketS, buf, BUFLEN, 0, (struct sockaddr*)&temp, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		ThreadReiceived();
		int i = 0;
		while (i < addrOutClients.addrOuts.size())
		{
			if (addrOutClients.addrOuts[i].sin_addr.S_un.S_addr == temp.sin_addr.S_un.S_addr)
			{
				break;
			}
			i++;
		}

		if (buf[0] == 'R' && i < addrOutClients.addrOuts.size())
		{
			addrOutClients.nbMessage[i] = buf[1];
		}
		else if (buf[0] == 'S' && i < addrOutClients.addrOuts.size())
		{
			std::cout << "SEND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

			std::string message = "R";
			message += buf[1];


			ThreadSendMSGR(i, message.c_str());
		}
		else if (buf[0] == 'D' && i < addrOutClients.addrOuts.size())
		{
			addrOutClients.DisConnection(inet_ntoa(temp.sin_addr));
		}
		else if (buf[0] == 'C')
		{
			std::cout << "\nconnection " << i << " size befor conection " << addrOutClients.addrOuts.size() << std::endl;
			addrOutClients.Connection(inet_ntoa(temp.sin_addr));
			std::cout << "size after conection " << addrOutClients.addrOuts.size() << std::endl;
			std::string message = "R";
			message += buf[1];
			SendMSGR(addrOutClients.addrOuts.size() - 1, message.c_str());
		}
		printf("Received packet from %s:%d\n", inet_ntoa(temp.sin_addr), ntohs(temp.sin_port));
		printf("Data: %s\n", buf);
}

void ReseauxConnection::ThreadReiceived()
{
	std::thread(&ReseauxConnection::Reiceived, this).detach();
}

void ReseauxConnection::SetBuffer(char msgT, const char* msg)
{
	*buf = &msgT;
	*buf += nbOfMessage;
	*buf += msg;
	nbOfMessage++;

}

void addresseClients::Connection(char* _addrOut)
{
	struct sockaddr_in temp;
	memset((char*)&temp, 0, sizeof(temp));
	temp.sin_family = AF_INET;
	temp.sin_port = htons(PORT_S);
	temp.sin_addr.S_un.S_addr = inet_addr(_addrOut);
	addrOuts.push_back(temp);
	nbMessage.push_back(-1);

}

void addresseClients::DisConnection(char* _addrOut)
{
	struct sockaddr_in temp;
	memset((char*)&temp, 0, sizeof(temp));
	temp.sin_family = AF_INET;
	temp.sin_port = htons(PORT_S);
	temp.sin_addr.S_un.S_addr = inet_addr(_addrOut);
	for (size_t i = 0; i < addrOuts.size(); i++)
	{
		if (temp.sin_addr.S_un.S_addr == addrOuts[i].sin_addr.S_un.S_addr)
		{
			addrOuts.erase(addrOuts.begin() + i);
			nbMessage.erase(nbMessage.begin() + i);
			break;

		}
	}

}
