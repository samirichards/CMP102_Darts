#include "Game.h"
#include <iostream>

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
	for (size_t i = 0; i < Players.size(); i++)
	{
		((Player)*Players[i]).ResetStats();
		((Player)*Players[i]).SetTarget(DartBoard);
		((Player)*Players[i]).CheckScore(3);
	}
}

void Game::PrintStats()
{
	std::cout << "There were " << to_string(RoundNumber) << " rounds this game" << endl;
	for (size_t i = 0; i < Players.size(); i++)
	{
		std::cout << Players[i]->GetPlayerName() << " got a score of " << Players[i]->GetCurrentScore() << " in " << Players[i]->GetThrows() << " throw(s)" << endl;
		std::cout << Players[i]->GetPlayerName() << " hit " << Players[i]->Getbulls() << " bulls in the game" << endl;
		std::cout << "--------------" << endl;
	}
}

void Game::StartGame()
{
	GameRunning = true;
	InitialisePlayers();
	RoundNumber = 0;

	do
	{
		RoundNumber++;
		std::cout << "Round " << RoundNumber << endl;

		for (size_t i = 0; i < Players.size(); i++)
		{
			for (size_t d = 0; d < DartsPerRound; d++)
			{
				Players[i]->ThrowDart(d);
				std::cout << Players[i]->GetPlayerName() << " threw and hit a " << Players[i]->GetLastScore() << ", Currently has a score of " << Players[i]->GetCurrentScore();
			}
		}
		GameRunning = !CheckForWin();
	} while (GameRunning);
	PrintStats();
}

//return true if there is any winner
bool Game::CheckForWin()
{
	bool value = false;
	for (size_t i = 0; i < Players.size(); i++)
	{
		if (Players[i]->GetCurrentScore() == 0)
		{
			value = true;
		}
	}
	return value;
}
