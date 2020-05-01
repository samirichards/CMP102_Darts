#pragma once
#include "Board.h"
#include "Player.h"
#include <vector>
class Game
{
public:
	Game(Board* dartBoard, int darts);
	void SetBoard(Board* dartBoard);
	void AddPlayer(Player* player);
	void InitialisePlayers();
	void PrintStats();
	void StartGame();

private:
	Board* DartBoard;
	std::vector<Player*> Players;
	bool GameRunning;
	int RoundNumber;
	int DartsPerRound;
};