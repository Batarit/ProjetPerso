#include "definition.h"
#include "CommandFunction.h"
#include "CommandServeur.h"

void NewCharacter(CommandServeur* serv, PlayerStruct* player)
{
	system("cls");
	std::string request;

	int idRace;

	std::cout << "What race do you want to play ?" << std::endl;

	request = "SELECT * FROM `race` WHERE 1";
	serv->Request(request.c_str());
	for (int i = 1; serv->GetRow(); i++)
	{
		std::cout << i << "- " << serv->Getvalue(1) << std::endl;
	}

	std::cin >> idRace;
	while (idRace < 1 || idRace > serv->GetNbRow())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		AnswerNotValid();
		std::cin >> idRace;
	}
	serv->FreeResult();

	request = "SELECT `pv`,`mana`,`armor` FROM `race` WHERE `id`= " + std::to_string(idRace) + " ";
	serv->Request(request.c_str());
	serv->GetRow();
	std::string hpBonus = serv->Getvalue(0);
	std::string manaBonus = serv->Getvalue(1);
	std::string armorBonus = serv->Getvalue(2);

	serv->FreeResult();

	player->character.idRace = idRace;

	std::cout << "What is your name ?" << std::endl;

	std::string name;
	std::cin >> name;
	request = "INSERT INTO `perso` (`id`, `name`, `lv`, `exp`, `hp`, `mana`, `Armor`, `logued`, `id_player`, `id_race`, `id_passif`, `id_guild`, `id_map`)";
	request += " VALUES (NULL, '" + name + "', '1', '0', '" + hpBonus + " ', '" + manaBonus + "', '" + armorBonus + "', 0, '" + player->idPlayer + "', '" + std::to_string(idRace) + "', NULL, NULL, '0');";
	serv->Request(request.c_str());
	serv->FreeResult();
}

void CharacterSelection(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode)
{
	system("cls");
	int answer = -1;
	std::string request;
	std::cout << "Hello " + player->playerName + " ! chose your character ?" << std::endl;

	request = "SELECT `id`, `name` FROM `perso` WHERE id_player = " + player->idPlayer;
	serv->Request(request.c_str());

	std::vector<std::string> idCharac;
	int i = 1;
	if (serv->GetNbRow() < 8)
	{
		std::cout << i << "- create a new character" << std::endl;
		i++;
	}
	while (serv->GetRow())
	{
		idCharac.push_back(serv->Getvalue(0));
		std::cout << i << "- " << serv->Getvalue(1) << std::endl;
		i++;
	}
	std::cout << i<<"- quit game \n" << std::endl;

	std::cin >> answer;
	while (answer > serv->GetNbRow() + 1 || answer < 1)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		AnswerNotValid();
		std::cin >> answer;

	}
	serv->FreeResult();
	if (answer == 1 && idCharac.size() < 8)
	{
		NewCharacter(serv, player);
	}
	else if (answer == i)
	{
		*gameMode = QUIT;
	}
	else
	{
		request.clear();
		std::string id;
		if (idCharac.size() < 8)
		{
			id = idCharac[answer - 2];
		}
		else
		{
			id = idCharac[answer - 1];
		}
		request = "SELECT * FROM `perso` WHERE `id` = '" + id + "'";
		serv->Request(request.c_str());

		while (serv->GetRow())
		{
			//std::cout << serv->Getvalue(10) << std::endl;
			system("pause");
			player->character.id = std::stoi(serv->Getvalue(0));
			player->character.name = serv->Getvalue(1);
			player->character.lv = std::stoi(serv->Getvalue(2));
			player->character.exp = std::stoi(serv->Getvalue(3));
			player->character.hp = std::stoi(serv->Getvalue(4));
			player->character.ActualHp = player->character.hp;
			player->character.manaMax = std::stoi(serv->Getvalue(5));
			player->character.mana = player->character.manaMax;
			player->character.Armor = std::stoi(serv->Getvalue(6));
			player->character.logued = serv->Getvalue(7);
			player->character.idRace = std::stoi(serv->Getvalue(9));
			if (serv->Getvalue(10) != NULL)
				player->character.idPassif = std::stoi(serv->Getvalue(10));
			else
				player->character.idPassif = -1;
			if (serv->Getvalue(11) != NULL)
				player->character.idGuild = std::stoi(serv->Getvalue(11));
			else
				player->character.idGuild = -1;

			player->character.idMap = std::stoi(serv->Getvalue(12));
		}
		serv->FreeResult();
		*gameMode = IN_GAME;
	}

}
