#pragma once
#include "Game.h"
class Config
{
public:
	void GetConfig();

	uint16_t StartingScore = 501;
	uint16_t MaxRounds = 30;
	uint32_t NumberOfGames = 1;

	uint8_t JoeAcc = 71;
	uint8_t SidAcc = 73;

	bool displayText = false;
	
};

