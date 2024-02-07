// TestDB.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdlib.h"
#include "time.h"
#include "conio.h"
#include "CommandServeur.h"

#include "CommandFunction.h"

#include "definition.h"


void AnswerNotValid()
{
	std::cout << "answer not valid please retrie" << std::endl;
}

int main()
{

	PlayerStruct player;
	GameMode gameMode = CHARACTER;
	CommandServeur serv;
	std::string error = serv.ConnectBDD("127.0.0.1");

	std::cout << error << std::endl;
	system("PAUSE");

	while (gameMode != QUIT)
	{
		switch (gameMode)
		{
		case CONNECTION:
			Connection(&serv, &player, &gameMode);
			break;
		case CHARACTER:
			CharacterSelection(&serv, &player, &gameMode);
			break;
		case IN_GAME:
			Game(&serv, &player, &gameMode);
			break;
		case MESSAGE:
			Message(&serv, &player, &gameMode);
			break;
		default:
			break;
		}
	}
}