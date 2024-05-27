#pragma once
#include <string>



enum typeRune
{
	FEHU,
	WRUZ,
	THURISAZ,
	ANSUZ,
	RAIDHO,
	KENAZ,
	GEBO,
	NUM_RUNE
};

struct Rune
{
	typeRune type;

	int id;

	int damage;

	int armor;

	int mama;

};

class Player
{

private:

	std::string commande;

	int pv;

	int pvMax;

	Rune runes[10];

	std::string name;

	int lvl;

	float exp;

	int mana;

	int manaMax;

	int armor;

	int armorBonus;

	int id;



};

