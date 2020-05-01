#include "Player.h"
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

void Player::ThrowDart()
{
	cout << "Need to implement ThrowDart";
}

void Player::ResetStats()
{
	Throws = 0;
	LastScoreHit = 0;
	CurrentScore = 0;
}

int Player::Getbulls()
{
	return HitBulls;
}

void Player::SetTarget(Board& target)
{
	*TargetBoard = target;
}

void Player::CheckScore() {
	cout << "Need to implement CheckScore";
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
