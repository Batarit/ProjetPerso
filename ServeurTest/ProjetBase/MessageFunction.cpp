#include "definition.h"
#include "CommandFunction.h"

#include "CommandServeur.h"
#include <string>


enum To
{
	ZONE,
	GUILD,
	FRIENDS
};

std::string ContentMSG()
{
	std::string msg;


	std::cout << "what is your message\n" << std::endl;

	std::cin.ignore();

	std::getline(std::cin, msg);

	size_t pose = 0;
	while (msg.find("'", pose) != std::string::npos)
	{
		pose = msg.find("'", pose);
		msg.replace(pose, pose, "\\\'");
		pose += 2;
	}
	return msg;
}

void MyMSG(CommandServeur* serv, PlayerStruct* player)
{
	system("cls");
	std::string request;
	char answer;

	std::cout << "Messagerie \n" << std::endl;
	std::cout << "0- see all your message\n"
		<< "1- see your new message\n"
		<< "2- see your invitation\n"
		<< "other if you want to go back\n" << std::endl;

	std::cin >> answer;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	request = "SELECT mail.id, mail.contenu, perso.name FROM mail, perso WHERE perso.id = mail.idSender AND mail.idReception = '" + std::to_string(player->character.id) + "' ";
	if (answer == '0')
	{
		request += "AND (command = 'N' OR command = '')";

	}
	else if (answer == '1')
	{
		request += "AND command = 'N'";
	}
	else if (answer == '2')
	{
		request += "AND command != 'N' AND command != ''";
	}
	serv->Request(request.c_str());
	int choix;

	std::vector<std::string> idMsg;
	int i = 1;
	while (serv->GetRow())
	{
		idMsg.push_back(serv->Getvalue(0));
		std::cout << i << "- sender : " << serv->Getvalue(2) << "\n\n" << std::endl;
		std::cout << serv->Getvalue(1) << "\n\n\n" << std::endl;
		i++;
	}

	std::cout << i << "- go back \n" << std::endl;

	std::cin >> choix;

	while (choix > i || choix < 1)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		AnswerNotValid();
		std::cin >> choix;
	}

	serv->FreeResult();

	system("cls");
	std::string idSender;
	std::string commande;
	if (choix < i)
	{
		request = "SELECT mail.contenu, perso.name, mail.command, perso.id FROM mail, perso WHERE perso.id = mail.idSender AND mail.id = " + idMsg[choix - 1];
		serv->Request(request.c_str());
		if (serv->GetRow())
		{
			commande = serv->Getvalue(2);
			idSender = serv->Getvalue(3);
			std::cout << serv->Getvalue(1) << "\n\n" << serv->Getvalue(0) << std::endl;
			serv->FreeResult();

			std::cout << "what do you want to do\n" << std::endl;
		}
		else
		{
			serv->FreeResult();
			std::cout << "error message not found \n" << std::endl;
			answer = 'e';
		}
		if (answer == '0' || answer == '1')
		{
			std::cout << "0- delete\t\t1- Respound\t\t2- nothing\n" << std::endl;

			std::cin >> answer;

			if (answer == '0')
			{
				request = "DELETE FROM `mail` WHERE id = " + idMsg[choix - 1];
				serv->Request(request.c_str());
				serv->FreeResult();
			}
			else if (answer == '1')
			{
				std::string message = ContentMSG();

				request = "INSERT INTO `mail`(`id`, `idReception`, `idSender`, `contenu`, `command`)";
				request += " VALUES (NULL,'" + idSender + "','" + std::to_string(player->character.id) + "','" + message + "','N');";
				serv->Request(request.c_str());
				serv->FreeResult();
				request = " UPDATE `mail` SET command = ' ' WHERE id = " + idMsg[choix - 1];
				serv->Request(request.c_str());
				serv->FreeResult();
			}
			else if (answer == '2')
			{
				request = "UPDATE `mail` SET command = ' ' WHERE id = " + idMsg[choix - 1];
				serv->Request(request.c_str());
				serv->FreeResult();
			}
		}
		else if (answer == '2')
		{
			if (commande.find("IG") != std::string::npos)
			{
				std::cout << "invitation to a guild\n\n";
			}
			if (commande.find("IF") != std::string::npos)
			{
				std::cout << "friend request\n\n";
			}

			std::cout << "0- delete\t\t1- accept\t\t2- nothing\n" << std::endl;

			if (answer == '0')
			{
				request = "DELETE FROM `mail` WHERE id = " + idMsg[choix - 1];
				serv->Request(request.c_str());
				serv->FreeResult();
			}
			else if (answer == '1')
			{

				request = "UPDATE `perso` SET `id_guild`=" + std::to_string(std::stoi(commande)) + " WHERE id = " + std::to_string(player->character.id) + ";";
				request += "UPDATE `mail` SET command = ' ' WHERE id = " + idMsg[choix - 1];

				serv->Request(request.c_str());
				serv->FreeResult();
			}

		}

	}


}

void MSGTo(CommandServeur* serv, PlayerStruct* player, To to, std::string Command)
{
	system("cls");
	std::string request;
	int answer;

	std::cout << "to whom do you want to your msg to \n" << std::endl;

	switch (to)
	{
	case ZONE:
		request = "SELECT id, name FROM perso WHERE id != " + std::to_string(player->character.id) + " AND id_map = " + std::to_string(player->character.idMap);
		break;
	case GUILD:
		request = "SELECT id, name FROM perso WHERE id != " + std::to_string(player->character.id) + " AND id_guild = " + std::to_string(player->character.idGuild);
		break;
	case FRIENDS:
		request = "SELECT perso.id,perso.name FROM `friendlist`, `perso`";
		request += "WHERE(friendlist.idP1 = " + std::to_string(player->character.id) + " AND perso.id = friendlist.idP2)";
		request += " OR(friendlist.idP2 = " + std::to_string(player->character.id) + " AND perso.id = friendlist.idP1) ";
		break;
	default:
		break;
	}
	serv->Request(request.c_str());

	std::vector<std::string> idCharac;
	int i = 1;
	while (serv->GetRow())
	{
		idCharac.push_back(serv->Getvalue(0));
		std::cout << i << "- " << serv->Getvalue(1) << std::endl;
		i++;
	}
	std::cout << i << "- to all\n";
	i++;
	std::cout << i << "- go back \n" << std::endl;

	std::cin >> answer;

	while (answer > i || answer < 1)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		AnswerNotValid();
		std::cin >> answer;
	}
	serv->FreeResult();
	system("cls");
	std::string message;
	if (answer != i)
		message = ContentMSG();
	if (answer - 1 < idCharac.size())
	{
		request = "INSERT INTO `mail`(`id`, `idReception`, `idSender`, `contenu`, `command`)";
		request += " VALUES (NULL,'" + idCharac[answer - 1] + "','" + std::to_string(player->character.id) + "','" + message + "','" + Command + "')";
		serv->Request(request.c_str());
		serv->FreeResult();

	}
	else if (answer == i - 1)
	{
		for (int j = 0; j < idCharac.size(); j++)
		{
			request = "INSERT INTO `mail`(`id`, `idReception`, `idSender`, `contenu`, `command`)";
			request += " VALUES (NULL,'" + idCharac[j] + "','" + std::to_string(player->character.id) + "','" + message + "','" + Command + "')";
			serv->Request(request.c_str());
			serv->FreeResult();
		}
	}

}

void Invitation(CommandServeur* serv, PlayerStruct* player)
{
	system("cls");
	std::string request;
	char answer;

	std::cout << "Messagerie \n" << std::endl;
	std::cout << "0- go back to game\n"
		<< "1- send a friends request to someone in the zone\n";
	if (player->character.idGuild != -1)
	{
		std::cout << "2- send an invitation to join the Guild to someone in the zone\n"
			<< "3- send a friends request to somone in Guild\n"
			<< "4- send an invitation to a friend to join the Guild\n";
	}

	std::cin >> answer;

	if (answer == '1')
	{
		MSGTo(serv, player, ZONE, "IF" + player->character.id);
	}
	else if (player->character.idGuild != -1)
		if (answer == '2')
		{
			MSGTo(serv, player, ZONE, "IG" + player->character.idGuild);
		}
		else if (answer == '3')
		{
			MSGTo(serv, player, GUILD, "If" + player->character.id);
		}
		else if (answer == '4')
		{
			MSGTo(serv, player, FRIENDS, "IG" + player->character.idGuild);
		}

}

void Message(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode)
{
	system("cls");
	std::string request;
	char answer;

	std::cout << "Messagerie \n" << std::endl;
	std::cout << "0- go back to game\n"
		<< "1- see your message\n"
		<< "2- send a message to someone in the zone\n"
		<< "3- send a message to a friend\n"
		<< "4- send an invite\n";
	if (player->character.idGuild != -1)
	{
		std::cout << "5- send a message to someone in the Guild\n";
	}

	std::cin >> answer;

	if (answer == '0')
	{
		*gameMode = IN_GAME;
	}
	else if (answer == '1')
	{
		MyMSG(serv, player);
	}
	else if (answer == '2')
	{
		MSGTo(serv, player, ZONE, "N");
	}
	else if (answer == '3')
	{
		MSGTo(serv, player, FRIENDS, "N");
	}
	else if (answer == '4')
	{
		Invitation(serv, player);
	}
	else if (answer == '5' && player->character.idGuild != -1)
	{
		MSGTo(serv, player, GUILD, "N");
	}
}
