#include "CommandServeur.h"
#include <iostream>

#include "stdlib.h"
#include "time.h"
#include "conio.h"

// conection a la base de donné
const char* CommandServeur::ConnectBDD(const char* adresse)
{
	const char* error = "";
	_my = mysql_init(NULL);
	if (_my == NULL)
	{
		//permet de récupérer de potentiel erreur
		error = mysql_error(_my);
	}
	//fonction qui permet la connexion avec la base de donné renvoie NULL si il y a une erreur lort de la connection.
	if (mysql_real_connect(_my, adresse, "Serveur", "IamHereAndYouAreNot", "meuporg", 0, NULL, 0) == NULL)
	{
		error = mysql_error(_my);
		//arrête la connection avec le serveur
		mysql_close(_my);
	}
	return error;
}

CommandServeur::~CommandServeur()
{
	mysql_close(_my);

}

bool CommandServeur::Request(const char* commande)
{
	if (mysql_query(_my, commande))
	{
		std::cout << mysql_error(_my) << std::endl;
		system("pause");
		exit(0);
	}
	else
	{
		result = mysql_store_result(_my);
		//std::cout << "requete ok\n";
		return false;
	}

	return true;
}

int CommandServeur::GetSizeColumn()
{
	return (int)result->lengths;
}

bool CommandServeur::GetRow()
{
	row = mysql_fetch_row(result);
	return row != nullptr;
}

int CommandServeur::GetNbRow()
{
	return result->row_count;
}


const char* CommandServeur::Getvalue(int column)
{
	return row[column];
}

void CommandServeur::FreeResult()
{
	mysql_free_result(result);
}
