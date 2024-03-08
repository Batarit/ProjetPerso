/*
	Simple UDP Server
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <thread>         // std::thread
#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <string>
#include "ReseauxConnection.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library



//struct dataMessage
//{
//	SOCKET s;
//	std::string message;
//	size_t size;
//	struct sockaddr_in si_other;
//	int slen;
//	char nbMessage;
//};
//
//void ThreadSendMSGR(dataMessage* dm, std::string message, size_t size)
//{
//	std::cout << "tu envoie quoi " << message << std::endl;
//	if (sendto(dm->s, message.c_str(), size, 0, (struct sockaddr*)&dm->si_other, dm->slen) == SOCKET_ERROR)
//	{
//		printf("sendto() failed with error code : %d", WSAGetLastError());
//		exit(EXIT_FAILURE);
//	}
//}
//
//void ThreadReiceived(dataMessage* dm)
//{
//	char buf[BUFLEN];
//	////receive a reply and print it
//////clear the buffer by filling null, it might have previously received data
//	////try to receive some data, this is a blocking call
//	while (true)
//	{
//
//		printf("Waiting for data...");
//		fflush(stdout);
//		memset(buf, '\0', BUFLEN);
//		if (recvfrom(dm->s, buf, BUFLEN, 0, (struct sockaddr*)&dm->si_other, &dm->slen) == SOCKET_ERROR)
//		{
//			printf("recvfrom() failed with error code : %d", WSAGetLastError());
//			exit(EXIT_FAILURE);
//		}
//		if (buf[0] == 'R')
//		{
//			dm->nbMessage = buf[1];
//		}
//		else if (buf[0] == 'S')
//		{
//			std::cout << "SEND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
//			//print details of the client/peer and the data received
//			//printf("Received packet from %s:%d\n", inet_ntoa(dm->si_other.sin_addr), ntohs(dm->si_other.sin_port));
//			//printf("Data: %s\n", buf);
//			std::string message = "R";
//			message += buf[1];
//
//			std::thread send(ThreadSendMSGR, dm, message, message.size());
//			send.detach();
//		}
//		printf("Received packet from %s:%d\n", inet_ntoa(dm->si_other.sin_addr), ntohs(dm->si_other.sin_port));
//		printf("Data: %s\n", buf);
//	}
//}
//
//void ThreadSendMSG(dataMessage* dm, size_t size)
//{
//	int32_t count = 0;
//	while (count <= INT32_MAX || dm->nbMessage != dm->message[1])
//	{
//
//		if (sendto(dm->s, dm->message.c_str(), size, 0, (struct sockaddr*)&dm->si_other, dm->slen) == SOCKET_ERROR)
//		{
//			printf("sendto() failed with error code : %d", WSAGetLastError());
//			exit(EXIT_FAILURE);
//		}
//
//		Sleep(500);
//	}
//
//}

int main()
{


	ReseauxConnection serveur;

	//keep listening for data
	serveur.ThreadReiceived();

	while (1)
	{
		//now reply the client with the same data
	}


	return 0;
}