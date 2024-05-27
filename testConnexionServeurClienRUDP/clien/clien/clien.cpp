/*
	Simple udp client
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <thread>         // std::thread
#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <string>
#include "ReseauxConnection.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library


//
//struct dataMessage
//{
//	SOCKET s;
//	std::string message;
//	size_t size;
//	struct sockaddr_in si_other;
//	int slen;
//	unsigned char nbMessage;
//};

//void ThreadReiceived(dataMessage* dm)
//{
//	char buf[BUFLEN];
//	////receive a reply and print it
//////clear the buffer by filling null, it might have previously received data
//	////try to receive some data, this is a blocking call
//	while (true)
//	{
//		fflush(stdout);
//		memset(buf, '\0', BUFLEN);
//
//		if (recvfrom(dm->s, buf, BUFLEN, 0, (struct sockaddr*)&dm->si_other, &dm->slen) == SOCKET_ERROR)
//		{
//			printf("recvfrom() failed with error code : %d", WSAGetLastError());
//			exit(EXIT_FAILURE);
//		}
//		if (buf[0] == 'R')
//		{
//			dm->nbMessage = buf[1];
//			std::cout << "ressu !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
//		}
//		else
//		{
//			std::cout << "voila " << buf << std::endl;
//		}
//		std::cout << "tu as ressu " << buf << std::endl;
//	}
//}
//
//void ThreadSendMSG(dataMessage* dm, size_t size, unsigned char nbM)
//{
//	std::string msg = dm->message;
//	int32_t count = 0;
//	std::thread(ThreadReiceived, dm).detach();
//	while (count <= 100 && dm->nbMessage != nbM)
//	{
//		std::cout << count << " send message " << msg << " with " << (int)dm->nbMessage << " and " << (int)nbM << std::endl;
//
//		if (sendto(dm->s, dm->message.c_str(), size, 0, (struct sockaddr*)&dm->si_other, dm->slen) == SOCKET_ERROR)
//		{
//			printf("sendto() failed with error code : %d", WSAGetLastError());
//			exit(EXIT_FAILURE);
//		}
//
//		Sleep(500);
//
//		count++;
//
//	}
//
//}

int main(void)
{
	ReseauxConnection serveur;

	//keep listening for data
	serveur.ThreadReiceived();
	serveur.SetBuffer('C', "");
	serveur.ThreadSendMSG();
	while (1)
	{
		std::string message;
		std::cin >> message;

		serveur.SetBuffer('S', message.c_str());
		serveur.ThreadSendMSG();

		//now reply the client with the same data
	}

	serveur.SetBuffer('D', "");
	serveur.ThreadSendMSG();

	return 0;
}