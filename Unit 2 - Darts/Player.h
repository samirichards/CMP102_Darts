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
	int GetAccuracy();
	void SetAccuracy(int value);
	int GetThrows();
	void ThrowDart(uint8_t currentRound);
	void ResetStats();
	int Getbulls();
	void SetTarget(Board* target);
	void CheckAim(uint8_t currentRound);
	string GetPlayerName();
	void SetAim(int segmentNumber);
	int GetLastScore();
	int GetCurrentScore();
	void StorePreviousState();
	void RestorePreviousState();
	SegmentTarget GetIntent();
	bool CheckBust();
	void ResetBust();
	uint16_t GetLifetimethrows();
	uint16_t GetLifetimeBulls();
	uint16_t GetLifetimeprecisehits();
	void IncrementLifetimeWins();
	uint16_t GetLifetimeWins();

private:
	string PlayerName;
	int Accuracy;
	int CurrentScore;
	int Throws;
	int LastScoreHit;
	int HitBulls;

	Board* TargetBoard;
	uint8_t Aim;
	uint8_t AimPref;
	PlayerBackup prev;
	bool BustFlag;

	uint16_t lifetimeThrows;
	uint16_t lifetimeBulls;
	uint16_t lifetimePreciseHits;
	uint16_t lifetimeTotalWins;
};

