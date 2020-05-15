#pragma once
#include <string>
#include "Board.h"
using namespace std;

struct PlayerBackup {
	uint8_t lastScoreHit;
	uint8_t hitBulls;
	uint8_t score;
};


class Player
{
public:
	Player(string name, int accuracy, int startingScore);
	
	void ThrowDart(uint8_t currentRound);
	void CheckAim(uint8_t currentRound);
	void SetTarget(Board* target);

	void RestorePreviousState();
	void StorePreviousState();

	bool CheckBust();
	void ResetBust();

	void IncrementRoundsWonInSet();
	void IncrementLifetimeWins();
	void IncrementMatchWins();
	void IncrementSetWins();

	void ResetRoundsWon();
	void ResetStats();

	uint32_t GetLifetimePreciseHits();
	uint32_t GetLifetimeThrows();
	uint32_t GetTotalMatchWins();
	uint32_t GetRoundsWonInSet();
	uint32_t GetLifetimeBulls();
	uint32_t GetTotalSetWins();
	uint32_t GetLifetimeWins();
	SegmentTarget GetIntent();
	string GetPlayerName();
	int GetCurrentScore();
	int GetLastScore();
	int GetAccuracy();
	int GetThrows();
	int Getbulls();

protected:
	string PlayerName;
	int LastScoreHit;
	int CurrentScore;
	int Accuracy;
	int HitBulls;
	int Throws;

	Board* TargetBoard;
	PlayerBackup prev;
	uint8_t AimPref;
	bool BustFlag;
	uint8_t Aim;

	uint32_t TotalMatchWins;
	uint32_t RoundWonInSet;
	uint32_t TotalSetWins;

	uint32_t lifetimePreciseHits;
	uint32_t lifetimeThrows;
	uint32_t lifetimeBulls;

	//This means total individual round wins
	uint32_t lifetimeTotalWins;
};

