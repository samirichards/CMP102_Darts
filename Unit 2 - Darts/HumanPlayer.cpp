#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(string _name, int _startingScore) {
	PlayerName = _name;
	CurrentScore = _startingScore;
}

void HumanPlayer::ThrowDart() {
	std::cout << "What number do you want to aim for? \n";
	int _targetNo = 0;
	std::cin >> _targetNo;
	std::cout << "Do you want to aim for a single, double, or treble? (enter 1, 2, or 3 respectively)\n";
	int _targetSeg = 1;
	std::cin >> _targetSeg;
	std::cout << "What do you want your accuracy to be (TEMP)\n";
	int _acc = 0;
	std::cin >> _acc;

	TargetBoard->AimForSegment(TargetBoard->GetSegmentNumber(_targetNo), _targetSeg, static_cast<double>(_acc));

	//FINISH THIS WHEN YOU CAN BE ARSED
}
