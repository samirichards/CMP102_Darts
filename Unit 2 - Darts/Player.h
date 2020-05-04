#pragma once
#include <string>
#include "Board.h"
using namespace std;

struct PlayerBackup {
	uint8_t score;
	uint8_t lastScoreHit;
	uint8_t hitBulls;
};


class Player
{
public:
	Player(string name, int accuracy, int startingScore);
	string GetAccuracy();
	void SetAccuracy(int value);
	int GetThrows();
	void ThrowDart(uint8_t currentRound);
	void ResetStats();
	int Getbulls();
	void SetTarget(Board* target);
	void CheckScore(uint8_t currentRound);
	string GetPlayerName();
	void SetAim(int segmentNumber);
	int GetLastScore();
	int GetCurrentScore();
	void StorePreviousState();
	void RestorePreviousState();

private:
	string PlayerName;
	int Accuracy;
	int CurrentScore;
	int Throws;
	int LastScoreHit;
	int HitBulls;
	Board* TargetBoard;
	int Aim;
	uint8_t AimPref;
	PlayerBackup prev;
};

