#include "Game.h"
#include <iostream>

Game::Game(Board* dartBoard, int darts, uint32_t _numberOfRounds)
{
	DartBoard = dartBoard;
	GameRunning = false;
	RoundNumber = 0;
	DartsPerRound = darts;
	NumberOfRounds = _numberOfRounds;
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

//To be used at the end of the set to show statisitcs, currently incomplete
void Game::PrintStats()
{
	for (size_t i = 0; i < Players.size(); i++)
	{
		std::cout << Players[i]->GetPlayerName() << " got a score of " << Players[i]->GetCurrentScore() << " in " << Players[i]->GetThrows() << " throw(s)" << endl;
		std::cout << Players[i]->GetPlayerName() << " hit " << Players[i]->Getbulls() << " bulls in this set" << endl;
		std::cout << Players[i]->GetPlayerName() << " won " << Players[i]->GetRoundsWonInSet() << " rounds this set" << endl;
		std::cout << "--------------" << endl;
	}
}

//To be used at the end of a match to show stats about the sets that were played
void Game::PrintSetStats(uint32_t MatchNumber)
{
	std::cout << "Match Number: " << MatchNumber << endl;
	std::cout << "There were " << SetNumber << " sets this match" << endl;
	for (size_t i = 0; i < Players.size(); i++)
	{
		std::cout << Players[i]->GetPlayerName() << " won " << Players[i]->GetTotalSetWins() << " sets this match " << endl;
		std::cout << "--------------" << endl;
	}
	std::cout <<"	" << Players[GetMatchWinner()]->GetPlayerName() << " was the overall winner this match" << endl;
}

uint32_t Game::GetMatchWinner()
{
	uint32_t CurrentMaxScore = 0;
	for (uint32_t i = 0; i < Players.size(); i++)
	{
		if (CurrentMaxScore < Players[i]->GetTotalSetWins())
		{
			CurrentMaxScore = Players[i]->GetTotalSetWins();
		}
	}
	for (uint32_t i = 0; i < Players.size(); i++)
	{
		if (CurrentMaxScore == Players[i]->GetTotalSetWins())
		{
			return i;
		}
	}
	return 0;
}

//Main game logic is executed here
void Game::StartGame(uint32_t numberOfGames, bool displayText)
{
	NumberOfGames = numberOfGames;
	if (displayText)
	{
		for (uint32_t k = 0; k < numberOfGames; k++)
		{
			ResetSetNumber();
			//This do loop will continue until there is an overall match winner (aka if any player has a total sets won of more than or equal to 7)
			do
			{
				//3 rounds per set Loop
				for (size_t roundNo = 1; roundNo < 6; roundNo++)
				{
					GameRunning = true;
					InitialisePlayers();
					RoundNumber = 0;
					std::cout << "Round is now running\n";
					//This is an individual round
					//With each player individually taking turns to throw darts
					do
					{
						RoundNumber++;
						std::cout << "Round " << RoundNumber << endl;

						//This for loop means that potentially there could be more than 2 players, although in this program right now that would never be the case
						for (uint8_t i = 0; i < Players.size(); i++)
						{
							//Store their current state so it can be restored in the event of a foul
							Players[i]->StorePreviousState();

							//Using a variable here means that the amount of times the player throws at the dartboard can be changed easily
							for (uint8_t d = 1; d <= DartsPerRound; d++)
							{
								//Check if the player has bust already
								//If the have then skip their go
								if (!Players[i]->CheckBust())
								{
									Players[i]->ThrowDart(d);

									//Check if the player has hit 0 before the end of the round
									//If they have then restore them to their previous state
									//Also break out of the loop so that the other player can play their round
									if (Players[i]->GetCurrentScore() == 0 && RoundNumber < 3)
									{
										std::cout << "FOUL" << endl;
										std::cout << Players[i]->GetPlayerName() << " hit a " << Players[i]->GetLastScore() << " and went out before the last throw, the turn has been dismissed and has been handed to another player" << endl;
										Players[i]->RestorePreviousState();
										break;
									}

									//Report back what the player wanted to aim for (even if they didn't hit it)
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

									//Report what the player actually hit
									std::cout << static_cast<int>(DartBoard->segments[Players[i]->GetIntent().segmentNumber]) << endl;
									std::cout << Players[i]->GetPlayerName() << " threw and got " << Players[i]->GetLastScore() << ", Currently has a score of " << Players[i]->GetCurrentScore() << endl;
								}
								else
								{
									std::cout << Players[i]->GetPlayerName() << " has bust" << endl;
								}
							}
							
							//Reset the player bust flag so that they can play again in the next round
							Players[i]->ResetBust();
						}
						std::cout << "------------------------\n";
						//If the game has not exceeded the round limit then check if there is a winner
						if (RoundNumber < NumberOfRounds)
						{
							GameRunning = !CheckForWin();
						}
						else
						{
							//If the game has exceeded the round limit then end the game
							//Also check if there was a draw at this point
							GameRunning = false;
							if (!CheckForWin())
							{
								std::cout << "Game ended in a draw after " << NumberOfRounds << " rounds" << endl;
							}
						}

					} while (GameRunning);
					std::cout << "End of round\n";

					//If GetRoundWinner returns uint8_max (256) then it means that there was no winner
					if (GetRoundWinner() != UINT8_MAX)
					{
						std::cout << Players[GetRoundWinner()]->GetPlayerName() << " is the winner of this round\n";
						Players[GetRoundWinner()]->IncrementLifetimeWins();
						Players[GetRoundWinner()]->IncrementRoundsWonInSet();
					}
				}

				//Check who won that best of 3 here
				Players[GetSetWinner()]->IncrementSetWins();
				std::cout << Players[GetSetWinner()]->GetPlayerName() << " Won this set with " << Players[GetSetWinner()]->GetRoundsWonInSet() << " rounds won\n";
				PrintStats();
				for (size_t i = 0; i < Players.size(); i++)
				{
					Players[i]->ResetRoundsWon();
				}
				IncrementSetNumber();
			} while (!IsMatchWon());
			PrintSetStats(k);
			Players[GetMatchWinner()]->IncrementMatchWins();
		}
	}

	//Cut down version of the above code which does not make use of any cout statements to speed up execution
	else
	{
		for (uint32_t k = 0; k < numberOfGames; k++)
		{
			ResetSetNumber();
			//This do loop will continue until there is an overall match winner (aka if any player has a total sets won of more than or equal to 7)
			do
			{
				//3 rounds per set Loop
				for (size_t roundNo = 1; roundNo < 6; roundNo++)
				{
					GameRunning = true;
					InitialisePlayers();
					RoundNumber = 0;
					//This is an individual round
					//With each player individually taking turns to throw darts
					do
					{
						RoundNumber++;

						//This for loop means that potentially there could be more than 2 players, although in this program right now that would never be the case
						for (uint8_t i = 0; i < Players.size(); i++)
						{
							//Store their current state so it can be restored in the event of a foul
							Players[i]->StorePreviousState();

							//Using a variable here means that the amount of times the player throws at the dartboard can be changed easily
							for (uint8_t d = 1; d <= DartsPerRound; d++)
							{
								//Check if the player has bust already
								//If the have then skip their go
								if (!Players[i]->CheckBust())
								{
									Players[i]->ThrowDart(d);

									//Check if the player has hit 0 before the end of the round
									//If they have then restore them to their previous state
									//Also break out of the loop so that the other player can play their round
									if (Players[i]->GetCurrentScore() == 0 && RoundNumber < 3)
									{
										Players[i]->RestorePreviousState();
										break;
									}
								}
							}

							//Reset the player bust flag so that they can play again in the next round
							Players[i]->ResetBust();
						}
						//If the game has not exceeded the round limit then check if there is a winner
						if (RoundNumber < NumberOfRounds)
						{
							GameRunning = !CheckForWin();
						}
						else
						{
							//If the game has exceeded the round limit then end the game
							//Also check if there was a draw at this point
							GameRunning = false;
						}

					} while (GameRunning);

					//If GetRoundWinner returns uint8_max (256) then it means that there was no winner
					if (GetRoundWinner() != UINT8_MAX)
					{
						Players[GetRoundWinner()]->IncrementLifetimeWins();
						Players[GetRoundWinner()]->IncrementRoundsWonInSet();
					}
				}

				//Check who won that best of 3 here
				Players[GetSetWinner()]->IncrementSetWins();
				for (size_t i = 0; i < Players.size(); i++)
				{
					Players[i]->ResetRoundsWon();
				}
				IncrementSetNumber();
			} while (!IsMatchWon());
			Players[GetMatchWinner()]->IncrementMatchWins();
		}
	}
	PrintLifetimeStats();
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

uint8_t Game::GetRoundWinner()
{
	for (uint8_t i = 0; i < Players.size(); i++)
	{
		if (Players[i]->GetCurrentScore() == 0)
		{
			return i;
		}
	}
	return UINT8_MAX;
}

void Game::PrintLifetimeStats()
{
	std::cout << "______________________Lifetime Stats________________________\n";
	std::cout << "Total matches were " << NumberOfGames << endl << endl;
	for (size_t i = 0; i < Players.size(); i++)
	{
		std::cout << Players[i]->GetPlayerName() << " Total throws = " << Players[i]->GetLifetimeThrows() << endl;
		std::cout << "Total bulls hit = " << Players[i]->GetLifetimeBulls() << endl;
		std::cout << "Total precise hits = " << Players[i]->GetLifetimePreciseHits() << endl;
		std::cout << "Total wins (Individual rounds) = " << Players[i]->GetLifetimeWins() << endl;
		std::cout << "Total sets won = " << Players[i]->GetTotalSetWins() << endl;
		std::cout << "Total matches won = " << Players[i]->GetTotalMatchWins() << endl;
		std::cout << "Reported accuracy = " << Players[i]->GetAccuracy() << "% \n";
		std::cout << "Projected Accuracy = " << static_cast<double>(Players[i]->GetAccuracy()) * (static_cast<double>(Players[i]->GetAccuracy()) / 100) << "% \n";
		
		std::cout << "Real accuracy: " << (static_cast<double>(Players[i]->GetLifetimePreciseHits()) / static_cast<double>(Players[i]->GetLifetimeThrows())) * 100 << "%" << endl;

		std::cout << "-------------------\n";
	}
	std::cout << "When calculating accuracy, keep in mind that this simulation intentionally makes hitting trebles and doubles harder than just a single, the value needs to be lower than accuracy% of accuracy (This is because a double or treble box is smaller). \n";
}

uint8_t Game::GetSetWinner()
{
	//This function is not very efficient but it gets the job done
	//It gets the highest score in the round and then checks afterwards who's score that was
	//Doesn't make much sense here since it's only 2 players, but my code has been designed so that if I wanted to I could easily add more players
	uint8_t CurrentMaxScore = 0;
	for (uint32_t i = 0; i < Players.size(); i++)
	{
		if (CurrentMaxScore < Players[i]->GetRoundsWonInSet())
		{
			CurrentMaxScore = Players[i]->GetRoundsWonInSet();
		}
	}
	for (uint32_t i = 0; i < Players.size(); i++)
	{
		if (CurrentMaxScore == Players[i]->GetRoundsWonInSet())
		{
			return i;
		}
	}
	return 0;
}

void Game::IncrementSetNumber()
{
	SetNumber++;
}

void Game::ResetSetNumber()
{
	SetNumber = 0;
}

bool Game::IsMatchWon()
{
	uint8_t CurrentMaxScore = 0;
	for (size_t i = 0; i < Players.size(); i++)
	{
		if (CurrentMaxScore < Players[i]->GetTotalSetWins())
		{
			CurrentMaxScore = Players[i]->GetTotalSetWins();
		}
	}
	//If any one player has a score of 7 or more then it is impossible for the other player to win, so declare them a winner now instead
	if (CurrentMaxScore >= 7 || SetNumber >= 13)
	{
		return true;
	}
	return false;
}
