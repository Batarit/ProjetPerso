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

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), wsa) != 0)
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

	//setup address structure
	for (int i = 0; i < 100; i++)
	{

	}
	//Prepare the sockaddr_in structure
	addrIn->sin_family = AF_INET;
	addrIn->sin_addr.s_addr = INADDR_ANY;
	addrIn->sin_port = htons(PORT_R);
}

ReseauxConnection::~ReseauxConnection()
{
}

void ReseauxConnection::SendMSGR(int who, const char* msg)
{
	if (who < addrOutClients.addrOuts.size())
	{
		std::cout << "tu envoie quoi " << buf << std::endl;
		if (sendto(socketS, msg, 2, 0, (struct sockaddr*)&addrOutClients.addrOuts[who], slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
}

void ReseauxConnection::SendMSG(int who)
{
	char* buffer = buf;
	int32_t count = 0;
	if (who < addrOutClients.addrOuts.size())
	{
		while (count <= INT32_MAX || addrOutClients.nbMessage[who] != buffer[1])
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

void ReseauxConnection::Reiceived()
{
	struct sockaddr_in temp = *addrOutClients.addrOuts[0];
	char buf[BUFLEN];
	////receive a reply and print it
////clear the buffer by filling null, it might have previously received data
	////try to receive some data, this is a blocking call
	while (true)
	{

		printf("Waiting for data...");
		fflush(stdout);
		memset(buf, '\0', BUFLEN);
		if (recvfrom(socketS, buf, BUFLEN, 0, (struct sockaddr*)&temp, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		int i = 0;
		while (i < addrOutClients.addrOuts.size())
		{
			if ((struct sockaddr*)&addrOutClients.addrOuts[i] == (struct sockaddr*)&temp)
			{
				break;
			}
			i++;
		}
		if (i < addrOutClients.addrOuts.size())
		{

			if (buf[0] == 'R')
			{
				addrOutClients.nbMessage[i] = buf[1];
			}
			else if (buf[0] == 'S')
			{
				std::cout << "SEND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
				//print details of the client/peer and the data received
				//printf("Received packet from %s:%d\n", inet_ntoa(dm->si_other.sin_addr), ntohs(dm->si_other.sin_port));
				//printf("Data: %s\n", buf);
				std::string message = "R";
				message += buf[1];


				SendMSGR(i, message.c_str());
			}
			printf("Received packet from %s:%d\n", inet_ntoa(temp.sin_addr), ntohs(temp.sin_port));
			printf("Data: %s\n", buf);
		}
		else if (buf[0] == 'C')
		{
			addrOutClients.Connection(inet_ntoa(temp.sin_addr));
		}
		else if (buf[0] == 'D')
		{
			addrOutClients.DisConnection(inet_ntoa(temp.sin_addr));
		}
	}
}

void addresseClients::Connection(char* _addrOut)
{
	struct sockaddr_in* temp;
	memset((char*)&temp, 0, sizeof(temp));
	temp->sin_family = AF_INET;
	temp->sin_port = htons(PORT_S);
	temp->sin_addr.S_un.S_addr = inet_addr(_addrOut);
	addrOuts.push_back(temp);
	nbMessage.push_back(-1);

}

void addresseClients::DisConnection(char* _addrOut)
{
	struct sockaddr_in* temp;
	memset((char*)&temp, 0, sizeof(temp));
	temp->sin_family = AF_INET;
	temp->sin_port = htons(PORT_S);
	temp->sin_addr.S_un.S_addr = inet_addr(_addrOut);
	for (size_t i = 0; i < addrOuts.size(); i++)
	{
		if (temp == addrOuts[i])
		{
			addrOuts.erase(addrOuts.begin() + i);
			nbMessage.erase(nbMessage.begin() + i);
			break;

		}
	}

}
