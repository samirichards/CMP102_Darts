#pragma once
#include "Board.h"
#include "Player.h"
#include <vector>
class Game
{
public:
	Game(Board* dartBoard, int darts, uint32_t _numberOfRounds);
	void StartGame(uint32_t numberOfGames, bool displayText);

	void SetBoard(Board* dartBoard);
	void AddPlayer(Player* player);
	void InitialisePlayers();
	void PrintStats();

	bool CheckForWin();
	uint8_t GetRoundWinner();
	void PrintLifetimeStats();
	uint8_t GetSetWinner();
	void IncrementSetNumber();
	void ResetSetNumber();
	bool IsMatchWon();
	void PrintSetStats(uint32_t MatchNumber);
	uint32_t GetMatchWinner();

private:
	Board* DartBoard;
	std::vector<Player*> Players;
	bool GameRunning;

	uint32_t RoundNumber = 0;
	uint32_t DartsPerRound = 3;

	uint32_t SetNumber = 0;
	//uint32_t NumberOfSets = 0;

	//uint32_t MatchNumber = 0;
	//uint32_t NumberOfMatches = 0;

	uint32_t NumberOfRounds = 0;
	uint32_t NumberOfGames = 0;
};