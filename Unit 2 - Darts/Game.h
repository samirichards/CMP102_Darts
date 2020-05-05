#pragma once
#include "Board.h"
#include "Player.h"
#include <vector>
class Game
{
public:
	Game(Board* dartBoard, int darts, uint16_t _numberOfRounds);
	void SetBoard(Board* dartBoard);
	void AddPlayer(Player* player);
	void InitialisePlayers();
	void PrintStats();
	void StartGame(uint16_t numberOfGames, bool displayText);
	bool CheckForWin();
	uint8_t GetRoundWinner();
	void PrintLifetimeStats();
	uint8_t GetSetWinner();
	void IncrementSetNumber();
	void ResetSetNumber();
	bool IsMatchWon();
	void PrintSetStats();
	uint8_t GetMatchWinner();

private:
	Board* DartBoard;
	std::vector<Player*> Players;
	bool GameRunning;

	int RoundNumber = 0;
	int DartsPerRound = 3;

	int SetNumber = 0;
	int NumberOfSets = 0;

	int MatchNumber = 0;
	int NumberOfMatches = 0;

	uint16_t NumberOfRounds = 0;
	uint16_t NumberOfGames = 0;

	//3 Rounds per set
	//	Each set is best of 3

	//Max of 13 sets per match
	//	Effectively 7 is the finishing line for sets
};