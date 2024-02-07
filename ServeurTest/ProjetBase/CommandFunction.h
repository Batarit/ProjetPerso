#pragma once

class CommandServeur;
struct PlayerStruct;
enum GameMode;




void AnswerNotValid();

void Connection(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode);

void CharacterSelection(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode);

void Game(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode);

void Message(CommandServeur* serv, PlayerStruct* player, GameMode* gameMode);

