#pragma once
#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Player.h"
class Config
{
public:
	void GetConfig();

	uint16_t StartingScore = 501;
	//uint16_t DartsPerRound = 3;
	uint16_t MaxRounds = 30;
	uint16_t NumberOfGames = 1;

	uint8_t JoeAcc = 71;
	uint8_t SidAcc = 73;

	bool displayText;
	
};

