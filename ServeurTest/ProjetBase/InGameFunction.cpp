#include "definition.h"
#include "CommandFunction.h"

#include "CommandServeur.h"

void map(CommandServeur* serv, PlayerStruct* player)
{
	system("cls");
	std::string request;
	std::string choix;

	std::cout << "you can go to.\n" << std::endl;

	request = "SELECT map.id, map.name FROM `map` ,`mapliaison` ";
	request += "WHERE (mapliaison.idMap1 = '" + std::to_string(player->character.idMap) + "' AND map.id = mapliaison.idMap2) OR";
	request += " (mapliaison.idMap2 = '" + std::to_string(player->character.idMap) + "' AND map.id = mapliaison.idMap1)";
	serv->Request(request.c_str());

	int i = 0;

	std::vector<std::string> idMap;

	while (serv->GetRow())
	{
		idMap.push_back(serv->Getvalue(0));
		std::cout << i << "- " << serv->Getvalue(1) << std::endl;
		i++;
	}
	std::cout << i << "- " << "quit" << std::endl;

	std::cin >> choix;

	if (std::stoi(choix) == i)
	{
		return;
	}
	while (std::stoi(choix) >= idMap.size() && std::stoi(choix) < 0)
	{
		AnswerNotValid();
		std::cin >> choix;
	}
	serv->FreeResult();
	request = "UPDATE `perso` SET `id_map` = '" + idMap[std::stoi(choix)] + "' WHERE `perso`.`id` = " + std::to_string(player->character.id) + " ";
	serv->Request(request.c_str());
	serv->FreeResult();
	player->character.idMap = std::stoi(idMap[std::stoi(choix)]);

}

void guild(CommandServeur* serv, PlayerStruct* player)
{
	system("cls");
	std::string request;
	std::string name;
	std::string description;

	std::cout << "What is the name of your guild ?\n" << std::endl;

	std::cin >> name;

	std::cout << "\nmake a short description of your guild\n" << std::endl;

	std::cin.ignore();

	std::getline(std::cin, description);

	request = "SELECT id FROM guildes WHERE nom = '" + name + "'";
	serv->Request(request.c_str());
	if (serv->GetRow())
	{
		serv->FreeResult();
		do
		{
			std::cout << "this name is already used use another one\n" << std::endl;

			std::cin >> name;
			request = "SELECT id FROM guildes WHERE nom = '" + name + "'";
			serv->Request(request.c_str());

		} while (serv->GetRow());
	}
	serv->FreeResult();
	request = "INSERT INTO `guildes` (`id`,`nom`,`description`) VALUES (NULL, '" + name + "','" + description + "')";
	serv->Request(request.c_str());
	serv->FreeResult();
	request = "SELECT id FROM guildes WHERE nom = '" + name + "'";
	std::string idGuild = "NULL";
	serv->Request(request.c_str());
	if (serv->GetRow())
	{
		idGuild = serv->Getvalue(0);
		player->character.idGuild = std::stoi(idGuild);
	}

	serv->FreeResult();

	request = "UPDATE `perso` SET perso.id_guild = " + idGuild + " WHERE perso.id = " + std::to_string(player->character.id);
	serv->Request(request.c_str());
	serv->FreeResult();
}

void Game(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode)
{
	system("cls");
	std::string request;
	char choice;

	request = "SELECT * FROM `map` WHERE id = " + std::to_string(player->character.idMap);
	serv->Request(request.c_str());

	std::string name;
	std::string description;

	if (serv->GetRow())
	{
		name = serv->Getvalue(1);
		description = serv->Getvalue(2);
	}
	else
	{
		serv->FreeResult();
		std::cout << "map don't exist";
		request = "UPDATE `perso` SET `id_map` = '0' WHERE `perso`.`id` = " + std::to_string(player->character.id) + " ";
		serv->Request(request.c_str());
		serv->FreeResult();

		request = "SELECT * FROM `map` WHERE id = " + std::to_string(player->character.idMap);
		serv->Request(request.c_str());

		std::string name;
		std::string description;

		if (serv->GetRow())
		{
			name = serv->Getvalue(1);
			description = serv->Getvalue(2);
		}
	}

	serv->FreeResult();


	std::cout << "you are at " << name << std::endl;
	std::cout << description << std::endl << std::endl;

	std::cout << "What do you want to do ?" << std::endl;

	std::cout << "0- change zone \n"
		<< "1- message menu \n";
	if (player->character.idGuild == -1)
		std::cout << "2- create a guild \n" << std::endl; 
	else
		std::cout << "2- quit guild \n" << std::endl;

	std::cout << "3- quit game \n" << std::endl;

	std::cin >> choice;
	if (choice == '0')
	{
		map(serv, player);
		return;
	}
	else if (choice == '1')
	{
		*gameMode = MESSAGE;
	}
	else if (choice == '2')
	{
		if (player->character.idGuild == -1)
		{
			guild(serv, player);
		}
		else
		{
			request = "UPDATE `perso` SET `id_guild` = NULL WHERE id = " + std::to_string(player->character.id);
			serv->Request(request.c_str());
			serv->FreeResult();
			request = "SELECT `id_guild` FROM `perso` WHERE id_guild = " + std::to_string(player->character.idGuild);
			serv->Request(request.c_str());
			if (!serv->GetRow())
			{
				serv->FreeResult();
				request = "DELETE FROM `guildes` WHERE guildes.id = " + std::to_string(player->character.idGuild);
				serv->Request(request.c_str());
			}
			serv->FreeResult();
			player->character.idGuild = -1;
		}
	}
	else if (choice == '3')
	{
		*gameMode = QUIT;
	}
}

