#pragma once
#include <string>
#include "Board.h"
using namespace std;
class Player
{
public:
	Player(string name, int accuracy, int startingScore);
	string GetAccuracy();
	void SetAccuracy(int value);
	int GetThrows();
	void ThrowDart();
	void ResetStats();
	int Getbulls();
	void SetTarget(Board& target);
	void CheckScore();
	string GetPlayerName();
	void SetAim(int segmentNumber);
	int GetLastScore();

private:
	string PlayerName;
	int Accuracy;
	int CurrentScore;
	int Throws;
	int LastScoreHit;
	int HitBulls;
	Board* TargetBoard;
	int Aim;
};

