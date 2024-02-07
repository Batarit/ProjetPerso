#ifndef COMMANDSERVEUR_H     // equivalently, #if !defined HEADER_H_
#define COMMANDSERVEUR_H
#include "mysql.h"
#endif // HEADER



class CommandServeur
{
private:
	MYSQL* _my;
	MYSQL_RES* result;
	MYSQL_ROW row;

public:
	const char* ConnectBDD(const char* adresse);

	~CommandServeur();

	bool Request(const char* commande);

	int GetSizeColumn();

	bool GetRow();

	int GetNbRow();


	const char* Getvalue(int column);

	void FreeResult();

};

