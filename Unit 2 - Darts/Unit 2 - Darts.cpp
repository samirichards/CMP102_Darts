// Unit 2 - Darts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Config.h"

int main()
{
    bool loopGame = false;
    Board DartBoard;
    Config GameConfig;
	
    do
    {
        std::cout << "-----------------------------\n";
        GameConfig.GetConfig();

        Game MainGame = Game(&DartBoard, 3, GameConfig.MaxRounds);

        Player* player1 = new Player("Joe", GameConfig.JoeAcc, GameConfig.StartingScore);
        Player* player2 = new  Player("Sid", GameConfig.SidAcc, GameConfig.StartingScore);

        MainGame.AddPlayer(player1);
        MainGame.AddPlayer(player2);

        MainGame.StartGame(GameConfig.NumberOfGames, GameConfig.displayText);
        delete player1;
        delete player2;
        system("pause");

        std::cout << "Would you like to run another simulation? (0 for no, anything else for yes)\n";
        std::cin >> loopGame;
    }
    while (loopGame);
}
