#include "definition.h"
#include "CommandFunction.h"
#include "CommandServeur.h"
#include <time.h> 
#include <string>
#include <thread>


void ThreadGainMana(PlayerStruct* player, bool* inFight);

void GetRune(CommandServeur* serv, PlayerStruct* player)
{
	std::string request;
	request = "SELECT * FROM `runes`";
	serv->Request(request.c_str());
	if (serv->GetRow())
	{
		player->character.runes.reserve(serv->GetNbRow());
		while (serv->GetRow())
		{
			Rune tempRune;
			std::string value = serv->Getvalue(1);
			tempRune.type = (TYPE_RUNE)(int)(value[0] - 0x30);
			value = serv->Getvalue(2);
			tempRune.Damage = (int)(value[0] - 0x30);
			value = serv->Getvalue(3);
			tempRune.Mana = (int)(value[0] - 0x30);
			value = serv->Getvalue(4);
			tempRune.Armor = (int)(value[0] - 0x30);
			player->character.runes.push_back(tempRune);
		}
		serv->FreeResult();
	}
}

std::thread* BeginFight(PlayerStruct* player, bool* inFight)
{
	*inFight = true;
	player->character.ActualHp = player->character.hp;
	player->character.BonusArmor = 0;
	player->character.mana = player->character.manaMax;
	std::thread manaGestion(ThreadGainMana, player, inFight);
	return &manaGestion;
}

void EndFight(bool* inFight, std::thread& manaGestion)
{
	*inFight = false;
	manaGestion.join();
}

Effect Combo(PlayerStruct* player, std::string value)
{
	char pose = 0;
	TYPE_RUNE precType = FEHU;
	Effect effect;
	
	while ((int)pose < value.size())
	{
		if (value[(int)pose] >= 0x2F && value[(int)pose] <= 0x39)
		{

			bool isBegining = (pose == 0);

			std::string val;
			while (value[(int)pose] != '/')
			{
				val += value[(int)pose];
				pose++;
			}
			while ((int)pose < value.size() && value[(int)pose] == '/')
			{
				pose++;
			}

			int idOfRune = std::stoi(val) - 1;
			if (idOfRune >= 0 && idOfRune < player->character.runes.size() && !isBegining)
			{
				if (player->character.runes[idOfRune].type == precType)
				{
					effect.damage += player->character.runes[idOfRune].Damage;
					effect.armor += player->character.runes[idOfRune].Armor;
					effect.mana += player->character.runes[idOfRune].Mana;
				}
				else if (player->character.runes[idOfRune].type == ((int)precType + 1 - (((int)precType + 1) >= TYPE_RUNE::MAX_TYPE_RUNE) * (TYPE_RUNE::MAX_TYPE_RUNE - 1)))
				{

					effect.damage -= player->character.runes[idOfRune].Damage;
					effect.mana += player->character.runes[idOfRune].Mana;
				}
				else if (player->character.runes[idOfRune].type == ((int)precType + 2 - (((int)precType + 2) >= TYPE_RUNE::MAX_TYPE_RUNE) * (TYPE_RUNE::MAX_TYPE_RUNE - 1)))
				{

					effect.armor += player->character.runes[idOfRune].Armor * 2;
					effect.mana += player->character.runes[idOfRune].Mana;
				}
				else if (player->character.runes[idOfRune].type == ((int)precType + 3 - (((int)precType + 3) >= TYPE_RUNE::MAX_TYPE_RUNE) * (TYPE_RUNE::MAX_TYPE_RUNE - 1)))
				{
					effect.mana += player->character.runes[idOfRune].Mana * 2;

				}
				else if (player->character.runes[idOfRune].type == ((int)precType + 4 - (((int)precType + 4) >= TYPE_RUNE::MAX_TYPE_RUNE) * (TYPE_RUNE::MAX_TYPE_RUNE - 1)))
				{
					effect.mana -= player->character.runes[idOfRune].Mana * 2;

				}
				else if (player->character.runes[idOfRune].type == ((int)precType + 5 - (((int)precType + 5) >= TYPE_RUNE::MAX_TYPE_RUNE) * (TYPE_RUNE::MAX_TYPE_RUNE - 1)))
				{
					effect.armor -= player->character.runes[idOfRune].Armor;
					effect.mana += player->character.runes[idOfRune].Mana;

				}
				else if (player->character.runes[idOfRune].type == ((int)precType + 6 - (((int)precType + 6) >= TYPE_RUNE::MAX_TYPE_RUNE) * (TYPE_RUNE::MAX_TYPE_RUNE - 1)))
				{
					effect.damage += player->character.runes[idOfRune].Damage * 2;
					effect.mana += player->character.runes[idOfRune].Mana;
				}
			}
			else if (isBegining)
			{
				effect.damage += player->character.runes[idOfRune].Damage;
				effect.armor += player->character.runes[idOfRune].Armor;
				effect.mana += player->character.runes[idOfRune].Mana;
			}
		}
		else
		{
			pose++;
		}
	}
	return effect;
}

void LoseHP(PlayerStruct* player, Effect effect)
{
	int damage = effect.damage;
	damage -= player->character.BonusArmor;
	damage -= player->character.Armor;
	if (damage < 0)
	{
		damage = 0;
	}
	player->character.BonusArmor = 0;
	player->character.hp -= damage;
}

void ThreadGainMana(PlayerStruct* player, bool* inFight)
{
	time_t precTimer;
	time(&precTimer);
	time_t actualTimer;
	while (*inFight)
	{
		time(&actualTimer);

		float value = difftime(actualTimer, precTimer) * (player->character.manaMax * 0.1);

		player->character.mana += value;
		if (player->character.mana > player->character.manaMax)
		{
			player->character.mana = player->character.manaMax;
		}
		precTimer = actualTimer;
	}
}

Effect LaunchSpell(PlayerStruct* player)
{
	std::string spell;
	std::cin >> spell;

	Effect effect = Combo(player, spell);
	if (effect.mana <= player->character.mana)
	{
		player->character.mana -= effect.mana;
		if (player->character.mana > player->character.manaMax)
		{
			player->character.mana = player->character.manaMax;
		}
		player->character.BonusArmor += effect.armor;
		return effect;
	}
	return Effect();
}