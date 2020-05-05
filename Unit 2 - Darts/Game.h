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
	uint8_t GetWinner();
	void PrintLifetimeStats();

private:
	Board* DartBoard;
	std::vector<Player*> Players;
	bool GameRunning;

	int RoundNumber;
	int DartsPerRound;

	int SetNumber;
	uint16_t NumberOfRounds;
	uint16_t NumberOfGames = 0;
};