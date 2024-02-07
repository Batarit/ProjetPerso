#ifndef DEFINITION_H     // equivalently, #if !defined HEADER_H_
#define DEFINITION_H

#include "stdlib.h"
#include "time.h"
#include "conio.h"

#include <iostream>
#include <string>
#include <vector>

struct Character
{
	int id;
	std::string name;
	int lv;
	int exp;
	int hp;
	int mana;
	int Armor;
	bool logued;
	int idRace;
	int idPassif;
	int idGuild = NULL;
	int idMap;
};

struct PlayerStruct
{
	std::string playerName = "Admin";
	std::string password;
	std::string idPlayer = "3";
	std::string mail;
	Character character;
};

enum GameMode
{
	CONNECTION,
	CHARACTER,
	IN_GAME,
	MESSAGE,
	QUIT,

	NB_GAMEMODE
};

#endif // HEADER