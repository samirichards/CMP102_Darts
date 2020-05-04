// Unit 2 - Darts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Player.h"

int main()
{
    Board DartBoard;
    Game MainGame = Game(&DartBoard, 3, 20);

    Player Joe = Player("Joe", 80, 501);
    Player Sid = Player("Sid", 60, 501);

    MainGame.AddPlayer(&Joe);
    MainGame.AddPlayer(&Sid);

    MainGame.StartGame();
    system("pause");
}
