// Unit 2 - Darts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Player.h"

int main()
{
    Board DartBoard;
    Game MainGame = Game(&DartBoard, 3);

    Player Joe = Player("Joe", 71, 501);
    Player Sid = Player("Sid", 73, 501);

    MainGame.AddPlayer(&Joe);
    MainGame.AddPlayer(&Sid);

    MainGame.StartGame();
    system("pause");
}
