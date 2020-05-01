#include "Game.h"

Game::Game(Board* dartBoard, int darts)
{
	DartBoard = dartBoard;
	GameRunning = false;
	RoundNumber = 0;
	DartsPerRound = darts;
}

void Game::SetBoard(Board* dartBoard)
{
	DartBoard = dartBoard;
}

void Game::AddPlayer(Player* player)
{
	Players.push_back(player);
}

void Game::InitialisePlayers()
{
	for (size_t i = 0; i < sizeof(Players); i++)
	{
		((Player)*Players[i]).ResetStats();
		((Player)*Players[i]).SetTarget(*DartBoard);
		((Player)*Players[i]).CheckScore();
	}
}

void Game::PrintStats()
{
	//Do this when you need to get around to it
}

void Game::StartGame()
{
	//Implement this when you need to my dude
}
