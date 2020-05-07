#include "Player.h"
#include <iostream>

Player::Player(string name, int accuracy, int startingScore)
{
	PlayerName = name;
	Accuracy = accuracy;
	CurrentScore = startingScore;
}

int Player::GetAccuracy()
{
	return Accuracy;
}

int Player::GetThrows()
{
	return Throws;
}

void Player::ThrowDart(uint8_t currentRound)
{
	//Set the targets before throwing
	CheckAim(currentRound);
	
	int temp = TargetBoard->AimForSegment(Aim, AimPref, Accuracy);

	//Check if the score coming back from the board would be valid if deducted from the players score
	if (CurrentScore - temp >= 0)
	{
		//Increment stats if the player managed to hit a bull (inner or outer)
		if (temp == 50 || temp == 25)
		{
			HitBulls++;
			lifetimeBulls++;
		}
		CurrentScore -= temp;

		//Verify that the player hit what they were intending to aim for, if they did then register it as a precise hit
		if (temp == (TargetBoard->segments[Aim] * AimPref))
		{
			lifetimePreciseHits++;
		}
	}

	//Flag that the player has bust this round if the score they would have got would have dipped below 0
	else 
	{
		BustFlag = true;
	}

	//Regardless of if the score was deducted or not register a throw from the player
	Throws++;
	lifetimeThrows++;
	LastScoreHit = temp;
}

void Player::ResetStats()
{
	Throws = 0;
	LastScoreHit = 0;
	CurrentScore = 501;
}

int Player::Getbulls()
{
	return HitBulls;
}

void Player::SetTarget(Board *target)
{
	TargetBoard = target;
}


//If the player score is above 63 then just set the aim to the highest option
//Else begin aiming for targets which will get you to 0 in 3 throws from the current score
void Player::CheckAim(uint8_t currentRound) {
	if (CurrentScore == 1)
	{
		//Being at a score of 1 at any point should not be allowed since you can only finish from an even number 2 and up on the last throw
		BustFlag = true;
	}
	if (CurrentScore > 63)
	{
		//Above this value it really is best to just aim for the highest value you can
		//Below this is where you need to strategize  based on the current situation 
		Aim = 0;
		AimPref = 3;
	}
	else
	{
		//Aim for 1/currentRound of what is left of your score, if all goes well then this should result in the player winning this round
		if (currentRound == 1)
		{
			int goal = static_cast<int>(floor(CurrentScore / 3));
			Aim = TargetBoard->GetBestTarget(goal).segmentNumber;
			AimPref = TargetBoard->GetBestTarget(goal).AimModifier;
		}
		if (currentRound == 2)
		{
			int goal = static_cast<int>(floor(CurrentScore / 2));
			Aim = TargetBoard->GetBestTarget(goal).segmentNumber;
			AimPref = TargetBoard->GetBestTarget(goal).AimModifier;
		}
		if (currentRound == 3)
		{
			int goal = CurrentScore;
			Aim = TargetBoard->GetBestTarget(goal).segmentNumber;
			AimPref = TargetBoard->GetBestTarget(goal).AimModifier;
		}
	}
}

string Player::GetPlayerName()
{
	return PlayerName;
}

int Player::GetLastScore()
{
	return LastScoreHit;
}

int Player::GetCurrentScore()
{
	return CurrentScore;
}

void Player::StorePreviousState()
{
	prev.score = CurrentScore;
	prev.lastScoreHit = LastScoreHit;
	prev.hitBulls = HitBulls;
}

void Player::RestorePreviousState()
{
	CurrentScore = prev.score;
	LastScoreHit = prev.lastScoreHit;
	HitBulls = prev.hitBulls;
}

SegmentTarget Player::GetIntent()
{
	return { Aim, AimPref };
}

bool Player::CheckBust()
{
	return BustFlag;
}

void Player::ResetBust()
{
	BustFlag = false; 
}

uint32_t Player::GetLifetimeThrows()
{
	return lifetimeThrows;
}

uint32_t Player::GetLifetimeBulls()
{
	return lifetimeBulls;
}

uint32_t Player::GetLifetimePreciseHits()
{
	return lifetimePreciseHits;
}

void Player::IncrementLifetimeWins()
{
	lifetimeTotalWins++;
}

uint32_t Player::GetLifetimeWins()
{
	return lifetimeTotalWins;
}

uint32_t Player::GetTotalSetWins()
{
	return TotalSetWins;
}

uint32_t Player::GetTotalMatchWins()
{
	return TotalMatchWins;
}

void Player::IncrementSetWins()
{
	TotalSetWins++;
}

void Player::IncrementMatchWins()
{
	TotalMatchWins++;
}

uint32_t Player::GetRoundsWonInSet()
{
	return RoundWonInSet;
}

void Player::IncrementRoundsWonInSet()
{
	RoundWonInSet++;
}

void Player::ResetRoundsWon()
{
	RoundWonInSet = 0;
}
