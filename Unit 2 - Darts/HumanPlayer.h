#pragma once
#include "Player.h"
class HumanPlayer : public Player
{

	HumanPlayer(string _name, int _startingScore);

	void ThrowDart();

};

