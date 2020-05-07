#pragma once
#include "Board.h"
#include "Player.h"
#include <vector>
class Game
{
public:
	Game(Board* dartBoard, int darts, uint32_t _numberOfRounds);
	void StartGame(uint32_t numberOfGames, bool displayText);

	void AddPlayer(Player* player);
	void InitialisePlayers();
	void PrintStats();

	void PrintSetStats(uint32_t MatchNumber);
	uint32_t GetMatchWinner();
	void PrintLifetimeStats();
	void IncrementSetNumber();
	uint8_t GetRoundWinner();
	uint8_t GetSetWinner();
	void ResetSetNumber();
	bool CheckForWin();
	bool IsMatchWon();



private:
	std::vector<Player*> Players;
	Board* DartBoard;
	bool GameRunning;

	uint32_t DartsPerRound = 3;
	uint32_t RoundNumber = 0;

	uint32_t SetNumber = 0;

	uint32_t NumberOfRounds = 0;
	uint32_t NumberOfGames = 0;
};