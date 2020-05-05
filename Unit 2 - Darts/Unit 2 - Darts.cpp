// Unit 2 - Darts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Config.h"

int main()
{
    Board DartBoard;
    
    Config GameConfig;
    GameConfig.GetConfig();

    Game MainGame = Game(&DartBoard, 3, GameConfig.MaxRounds);

    Player Joe = Player("Joe", GameConfig.JoeAcc, GameConfig.StartingScore);
    Player Sid = Player("Sid", GameConfig.SidAcc, GameConfig.StartingScore);

    MainGame.AddPlayer(&Joe);
    MainGame.AddPlayer(&Sid);

    MainGame.StartGame(GameConfig.NumberOfGames, GameConfig.displayText);
    system("pause");
}
