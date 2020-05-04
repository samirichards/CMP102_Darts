#include "Game.h"
#include <iostream>
#include <time.h>

Game::Game(Board* dartBoard, int darts, uint16_t _numberOfRounds)
{
	DartBoard = dartBoard;
	GameRunning = false;
	RoundNumber = 0;
	DartsPerRound = darts;
	NumberOfRounds = _numberOfRounds;
}

void Game::SetBoard(Board* dartBoard)
{
	DartBoard = dartBoard;
}

void Game::AddPlayer(Player* player)
{
	Players.push_back(player);
}

//Prepares all players in the game to play by resetting their scores and desginating a DartBoard object as the target
void Game::InitialisePlayers()
{
	for (size_t i = 0; i < Players.size(); i++)
	{
		Players[i]->ResetStats();
		Players[i]->SetTarget(DartBoard);
		Players[i]->CheckAim(3);
	}
}

//To be used at the end of the game to show statisitcs, currently incomplete
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

//Main game logic is executed here
void Game::StartGame()
{
	GameRunning = true;
	InitialisePlayers();
	RoundNumber = 0;

	do
	{
		RoundNumber++;
		std::cout << "Round " << RoundNumber << endl;

		for (uint8_t i = 0; i < Players.size(); i++)
		{
			Players[i]->StorePreviousState();
			for (uint8_t d = 1; d <= DartsPerRound; d++)
			{
				if (!Players[i]->CheckBust())
				{
					Players[i]->ThrowDart(d);

					if (Players[i]->GetCurrentScore() == 0 && RoundNumber < 3)
					{
						std::cout << "FOUL" << endl;
						std::cout << Players[i]->GetPlayerName() << " hit a " << Players[i]->GetLastScore() << " and went out before the last throw, the turn has been dismissed and has been handed to another player" << endl;
						Players[i]->RestorePreviousState();
						d = DartsPerRound;
						break;
					}

					std::cout << Players[i]->GetPlayerName() << " Aimed for a ";
					if (Players[i]->GetIntent().AimModifier == 1)
					{
						std::cout << "Single ";
					}
					if (Players[i]->GetIntent().AimModifier == 2)
					{
						std::cout << "Double ";
					}
					if (Players[i]->GetIntent().AimModifier == 3)
					{
						std::cout << "Treble ";
					}
					std::cout << (int)DartBoard->segments[Players[i]->GetIntent().segmentNumber] << endl;
					std::cout << Players[i]->GetPlayerName() << " threw and got " << Players[i]->GetLastScore() << ", Currently has a score of " << Players[i]->GetCurrentScore() << endl;
				}
				else 
				{
					std::cout << Players[i]->GetPlayerName() << " has bust" << endl;
				}
			}
			Players[i]->ResetBust();
		}
		std::cout << "------------------------\n";
		if (RoundNumber < 30)
		{
			GameRunning = !CheckForWin();
		}
		else
		{
			if (CheckForWin())
			{
				GameRunning = false;
			}
			else
			{
				std::cout << "Game ended in a draw after 30 rounds" << endl;
				GameRunning = false;
			}
		}

	} while (GameRunning);
	if (GetWinner() != UINT8_MAX)
	{
		std::cout << Players[GetWinner()]->GetPlayerName() << " is the winner\n";
	}
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

uint8_t Game::GetWinner()
{
	for (size_t i = 0; i < Players.size(); i++)
	{
		if (Players[i]->GetCurrentScore() == 0)
		{
			return i;
		}
	}
	return UINT8_MAX;
}
