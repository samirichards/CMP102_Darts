#include "Player.h"
#include <math.h>
#include <iostream>

Player::Player(string name, int accuracy, int startingScore)
{
	PlayerName = name;
	Accuracy = accuracy;
	CurrentScore = startingScore;
}

string Player::GetAccuracy()
{
	return to_string(Accuracy) + "/%";
}

void Player::SetAccuracy(int value)
{
	Accuracy = value;
}

int Player::GetThrows()
{
	return Throws;
}

void Player::ThrowDart(uint8_t currentRound)
{
	//Set the targets before throwing
	CheckScore(currentRound);

	//Special condition for aiming at the bull which is easily recognised
	if (Aim == INT_MAX)
	{
		//If an inner or outer bull was hit then increment the bull counter
		int temp = TargetBoard->AimForBull(Accuracy, AimPref);
		if (temp == 50 || temp == 25)
		{
			HitBulls++;
		}
		//But regardless of if a bull was hit or not, reduce the score by what came back (since the player can miss and hit a segment around the bull)
		CurrentScore -= temp;
		LastScoreHit = temp;
	}
	else
	{
		//Decrement the current score as long as it won't cause it to dip below 0

		//---------------------
		//	DEV NOTE: THIS WILL LIKELY NEED REWORKING, IF THE SCORE WOULD DIP BELOW 0 THEN THEN GAME OBJECT NEEDS TO RESTORE THE PLAYER SINCE THAT ROUND IS INVALID
		//---------------------

		int temp = TargetBoard->AimForSegment(Aim, AimPref, Accuracy);
		if (CurrentScore - temp >= 0)
		{
			CurrentScore -= temp;
		}
		LastScoreHit = temp;
	}
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
void Player::CheckScore(uint8_t currentRound) {
	if (CurrentScore > 63)
	{
		Aim = 0;
		AimPref = 3;
	}
	else
	{
		if (currentRound == 1)
		{
			int goal = (int)floor(CurrentScore / 3);
			Aim = TargetBoard->GetBestTarget(goal).segmentNumber;
			AimPref = TargetBoard->GetBestTarget(goal).AimModifier;
		}
		if (currentRound == 2)
		{
			int goal = (int)floor(CurrentScore / 2);
			Aim = TargetBoard->GetBestTarget(goal).segmentNumber;
			AimPref = TargetBoard->GetBestTarget(goal).AimModifier;
		}
		if (currentRound == 3)
		{
			int goal = (int)floor(CurrentScore);
			Aim = TargetBoard->GetBestTarget(goal).segmentNumber;
			AimPref = TargetBoard->GetBestTarget(goal).AimModifier;
		}
	}
}

string Player::GetPlayerName()
{
	return PlayerName;
}

void Player::SetAim(int segmentNumber)
{
	Aim = segmentNumber;
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
