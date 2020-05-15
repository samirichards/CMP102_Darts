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

        Player* Joe = new Player("Joe", GameConfig.JoeAcc, GameConfig.StartingScore);
        Player* Sid = new  Player("Sid", GameConfig.SidAcc, GameConfig.StartingScore);

        MainGame.AddPlayer(Joe);
        MainGame.AddPlayer(Sid);

        MainGame.StartGame(GameConfig.NumberOfGames, GameConfig.displayText);
        delete Joe;
        delete Sid;
        system("pause");

        std::cout << "Would you like to run another simulation? (0 for no, anything else for yes)\n";
        std::cin >> loopGame;
    }
    while (loopGame);
}
