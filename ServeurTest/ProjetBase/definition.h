#ifndef DEFINITION_H     // equivalently, #if !defined HEADER_H_
#define DEFINITION_H

#include "stdlib.h"
#include "time.h"
#include "conio.h"

#include <iostream>
#include <string>
#include <vector>

enum TYPE_RUNE
{
	FEHU,
	URUZ,
	THURISAZ,
	ANSUZ,
	RAIDHO,
	KENAZ,
	GEBO,

	MAX_TYPE_RUNE
};

struct Rune
{
	TYPE_RUNE type;
	int Damage;
	int Mana;
	int Armor;
};


struct Character
{
	int id;
	std::string name;
	int lv;
	int exp;
	int hp;
	int ActualHp;
	float mana;
	int manaMax;
	int Armor;
	int BonusArmor = 0;
	bool logued;
	int idRace;
	int idPassif;
	int idGuild = NULL;
	int idMap;
	std::vector<Rune> runes;
};

struct PlayerStruct
{
	std::string playerName = "Admin";
	std::string password;
	std::string idPlayer = "3";
	std::string mail;
	std::string adressMail;
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

struct Effect
{
	int damage = 0;
	int armor = 0;
	float mana = 0.0f;
};

#endif // HEADER