/*
	Simple udp client
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <thread>         // std::thread
#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <string>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT_SEND 8888	
#define PORT_RECEPT 5232	//The port on which to listen for incoming data


struct dataMessage
{
	SOCKET s;
	std::string message;
	size_t size;
	struct sockaddr_in si_other;
	int slen;
	unsigned char nbMessage;
};

void ThreadReiceived(dataMessage* dm)
{
	char buf[BUFLEN];
	////receive a reply and print it
////clear the buffer by filling null, it might have previously received data
	////try to receive some data, this is a blocking call
	while (true)
	{
		fflush(stdout);
		memset(buf, '\0', BUFLEN);

		if (recvfrom(dm->s, buf, BUFLEN, 0, (struct sockaddr*)&dm->si_other, &dm->slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		if (buf[0] == 'R')
		{
			dm->nbMessage = buf[1];
			std::cout << "ressu !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		}
		else
		{
			std::cout << "voila " << buf << std::endl;
		}
		std::cout << "tu as ressu " << std::endl;
	}
}

void ThreadSendMSG(dataMessage* dm, size_t size, unsigned char nbM)
{
	int32_t count = 0;
	while (count <= 100 && dm->nbMessage != nbM)
	{
		std::cout << count << " send message " << (int)dm->nbMessage << " and " << (int)nbM << std::endl;

		if (sendto(dm->s, dm->message.c_str(), size, 0, (struct sockaddr*)&dm->si_other, dm->slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		Sleep(500);

		count++;

	}

}


int main(void)
{
	dataMessage dm;
	struct sockaddr_in server;
	dm.s, dm.slen = sizeof(dm.si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	unsigned char nbMessage = 0;
	dm.nbMessage = 255;

	char ip = 0;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((dm.s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)&dm.si_other, 0, sizeof(dm.si_other));
	dm.si_other.sin_family = AF_INET;
	dm.si_other.sin_port = htons(PORT_SEND);
	dm.si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);



	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT_RECEPT);

	//Bind
	if (bind(dm.s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	std::thread reiceiv(ThreadReiceived, &dm);
	reiceiv.detach();
	//start communication
	while (1)
	{
		printf("Enter message ");

		std::cin >> message;

		std::string CompleteMSG = "S" + std::to_string((int)nbMessage);
		CompleteMSG += message;
		dm.message = CompleteMSG;
		//send the message
		std::thread send(ThreadSendMSG, &dm, CompleteMSG.size(), nbMessage);
		send.detach();




		nbMessage++;
	}

	closesocket(dm.s);
	WSACleanup();

	return 0;
}