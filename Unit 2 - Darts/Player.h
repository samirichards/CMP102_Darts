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
	uint32_t GetLifetimethrows();
	uint32_t GetLifetimeBulls();
	uint32_t GetLifetimeprecisehits();
	void IncrementLifetimeWins();
	uint32_t GetLifetimeWins();

	uint32_t GetTotalSetWins();
	uint32_t GetTotalMatchWins();
	void IncrementSetWins();
	void IncrementMatchWins();

	uint32_t GetRoundsWonInSet();
	void IncrementRoundsWonInSet();
	void ResetRoundsWon();

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

	uint32_t RoundWonInSet;
	uint32_t TotalSetWins;
	uint32_t TotalMatchWins;

	uint32_t lifetimeThrows;
	uint32_t lifetimeBulls;
	uint32_t lifetimePreciseHits;

	//This means individual round wins
	uint32_t lifetimeTotalWins;
};

