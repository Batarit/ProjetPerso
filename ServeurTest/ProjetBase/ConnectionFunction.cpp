#include "definition.h"
#include "CommandFunction.h"

#include "CommandServeur.h"



void NewPlayer(CommandServeur* serv, PlayerStruct* player)
{
	std::string pseudo;
	std::string password;
	std::string mail;
	std::string request;
	std::cout << "Ok please enter your pseudo" << std::endl;
	std::cin >> pseudo;

	std::cout << "next your password" << std::endl;
	std::cin >> password;

	std::cout << "and finaly your mail" << std::endl;
	std::cin >> mail;

	request = "SELECT `id` FROM `joueurs` WHERE `name` = '" + pseudo + "' OR `adresse mail` = '" + mail + "'";
	serv->Request(request.c_str());
	if (serv->GetRow())
	{
		bool isGood = false;
		do
		{
			isGood = false;
			serv->FreeResult();
			request = "SELECT `id` FROM `joueurs` WHERE `adresse mail` = " + mail;
			serv->Request(request.c_str());
			if (serv->GetRow())
			{
				isGood = true;
				std::cout << "your mail is already please use another one " << std::endl;
				std::cin >> mail;
			}

		} while (isGood);
		do
		{
			isGood = false;
			serv->FreeResult();
			request = "SELECT `id` FROM `joueurs` WHERE `name` = " + pseudo;
			serv->Request(request.c_str());
			if (serv->GetRow())
			{
				isGood = true;
				std::cout << "your pseudo is already used please use another one" << std::endl;
				std::cin >> pseudo;
			}

		} while (isGood);

	}

	serv->FreeResult();
	request = "INSERT INTO `joueurs` (`name`, `password`, `adresse mail`, `id`) VALUES ('" + pseudo + "', '" + password + "', '" + mail + "', NULL); ";
	serv->Request(request.c_str());
	serv->FreeResult();
	player->playerName = pseudo;
	player->password = password;
	player->mail = mail;
	request = "SELECT `id` FROM `joueurs` WHERE `name` = '" + pseudo + "' AND `adresse mail` = '" + mail + "'";
	serv->Request(request.c_str());
	while (serv->GetRow())
	{
		player->idPlayer = serv->Getvalue(0);
	}
}

void PlayerConnect(CommandServeur* serv, PlayerStruct* player)
{
	std::string pseudo;
	std::string password;
	std::string request;
	std::cout << "Ok please enter your pseudo" << std::endl;
	std::cin >> pseudo;

	std::cout << "next your password" << std::endl;
	std::cin >> password;

	request = "SELECT `id`, `Connected` FROM `joueurs` WHERE `name` = '" + pseudo + "' AND `password` = '" + password + "'";
	serv->Request(request.c_str());
	if (!serv->GetRow())
	{
		bool isNotGood = false;

		do
		{
			isNotGood = false;
			serv->FreeResult();
			request = "SELECT `id`, `Connected` FROM `joueurs` WHERE `name` = '" + pseudo + "'";
			serv->Request(request.c_str());
			if (!serv->GetRow())
			{
				isNotGood = true;
				std::cout << "this pseudo don't exit try another one" << std::endl;
				std::cin >> pseudo;
			}

		} while (isNotGood);

		do
		{
			isNotGood = false;
			serv->FreeResult();
			request = "SELECT `id`, `Connected` FROM `joueurs` WHERE `password` = '" + password + "'";
			serv->Request(request.c_str());
			if (!serv->GetRow())
			{
				isNotGood = true;
				std::cout << "wrong password retry" << std::endl;
				std::cin >> password;
			}

		} while (isNotGood);
	}
	if (serv->Getvalue(1) != nullptr)
	{
		std::string temp = serv->Getvalue(1);
		if (temp.compare("0") != 0)
		{
			std::cout << "this count is already connected" << std::endl;
			exit(1);
		}
	}

	serv->FreeResult();
	request = "SELECT * FROM `joueurs` WHERE `name` = '" + pseudo + "' AND `password` = '" + password + "'";
	serv->Request(request.c_str());
	while (serv->GetRow())
	{
		player->playerName = serv->Getvalue(0);
		player->password = serv->Getvalue(1);
		player->mail = serv->Getvalue(2);
		player->idPlayer = serv->Getvalue(4);
	}
	serv->FreeResult();
}

void Connection(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode)
{
	system("cls");
	char answer;
	std::cout << "Welcome ! do you already have an account ?" << std::endl;
	std::cout << "0- yes\n1- no" << std::endl;

	std::cout << "2- quit game \n" << std::endl;
	std::cin >> answer;
	while (answer < '0' || answer > '2')
	{
		AnswerNotValid();
		std::cin >> answer;
	}
	if (answer == '1')
	{
		NewPlayer(serv, player);
		*gameMode = CHARACTER;
	}
	else if (answer == '0')
	{
		PlayerConnect(serv, player);
		*gameMode = CHARACTER;
	}
	else if (answer == '2')
	{
		*gameMode = QUIT;
	}

}
