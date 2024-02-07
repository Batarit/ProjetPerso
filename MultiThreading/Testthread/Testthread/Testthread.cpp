// Testthread.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include<stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include<windows.h>

void ThreadReiceived(char* nbMessageReiceived, char* editMSG)
{
	while (true)
	{
		Sleep(100);

		std::cout << "die" << std::endl;
		*editMSG += 1;
	}
}

int ThreadSendMSG(char* nbMessage, char* editMSG, bool* testON)
{
	//int32_t count = 0;
	//while (count <= INT32_MAX)
	//{

	//	if (sendto(*s, message, size, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	//	{
	//		printf("sendto() failed with error code : %d", WSAGetLastError());
	//		exit(EXIT_FAILURE);
	//	}
	std::thread reception(ThreadReiceived, nbMessage, editMSG);
	reception.detach();

	Sleep(1000);
	*testON = false;

	//}

	return 0;
}


int main()
{
	char nbMessage = 0;
	char editMSG = 0;
	bool testON = true;
	std::thread test(ThreadSendMSG, &nbMessage, &editMSG, &testON);

	while (testON)
	{
		Sleep(100);
		std::cout << std::to_string((int)editMSG) << std::endl;

	}

	test.join();
	nbMessage = 1;

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
