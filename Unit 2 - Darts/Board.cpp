#include "Board.h"
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <vector>

Board::Board() = default;

int Board::AimForSegment(int segmentNumber, uint8_t aimPreference, double accuracy)
{
	//aimPreference == 1 == Just aim for the normal segment
	//aimPreference == 2 == Aim for a double
	//aimPreference == 3 == Aim for a treble

	uint8_t value = rand() % 100;
	//std::cout << "Board returned value: " << (int)value << std::endl;
	int retValue = 0;

	//Bull targeting has been moved to the AimForSegment function
	//This is to reduce the work required for allowing the players to target bulls
	if (segmentNumber == 21)
	{
		if (static_cast<double>(value) < accuracy)
		{
			if (value < (accuracy * (accuracy / 100)))
			{
				return segments[segmentNumber] * aimPreference;
			}
			else
			{
				return segments[segmentNumber];
			}
		}
		else {
			srand(time(nullptr));
			uint8_t segTarget = rand() % 20;
			return segments[segTarget];
		}
	}

	//This section of code is used to target anything but a bull
	//If the value is below the accuracy stat then set the return value to the desired segment number
	if (value < accuracy)
	{
		retValue = segments[segmentNumber];
	}
	else 
	{
		if (value < ((accuracy + (100 - accuracy) / 2)))
		{
			if (segmentNumber == 0)
			{
				retValue = segments[20];
			}
			else
			{
				retValue = segments[segmentNumber - 1];
			}
		}
		//This means that if the value is in the top half of numbers between the accuracy stat and 100 then set the return value to one segment to the right
		else
		{
			if (segmentNumber == 21)
			{
				retValue = segments[0];
			}
			else
			{
				retValue = segments[segmentNumber + 1];
			}
		}
	}

	//AimPreference modifier takes effect here
	//If the value is less than accuracy% of accuracy then return the value they want multiplied by the given modifier, else just give them the segment as a single
	//This respects the accuracy stat, and rewards players with a high accuracy (this will be important in task 3 where the player can achieve a 100% accuracy)

	if (value < static_cast<int>(floor(accuracy * (accuracy / 100))))
	{
		return retValue * aimPreference;
	}
	else
	{
		return retValue;
	}
}

//int Board::AimForBull(int accuracy, bool aimPreference)
//{
	//aimPreference == 1 == aim for outer ring (25)
	//aimPreference == 2 == aim for inner ring (50)
	//srand(time(NULL));
	//uint8_t value = rand() % 100;

	//If the player misses then return a random number from around the bull
	//Using the same double/treble formula as above, return the exact number the player is aiming for if they have a high accuracy, else just return the outer ring value
	//A side effect of this is that if the player is aiming for the 25 and they clear the first bar then they are always going to get it, since the default is 25 anyway


//}

//Find the segment number that corresponds with that given target value
uint8_t Board::GetSegmentNumber(int target)
{
	for (uint8_t i = 0; i < sizeof(segments); i++)
	{
		if (segments[i] == target)
		{
			return i;
		}
	}
	return NULL;
}

//This function will return the segment number and aim preference which should be used to get the desired goal / value closest to the goal
SegmentTarget Board::GetBestTarget(uint8_t goal)
{
	if (goal > 60)
	{
		return { 0, 3 };
	}
	else
	{
		//Revised aiming tactic if the goal is low enough then simply aim for the normal segment
		//This will increase the odds of actually hitting the value you want (since hitting a double 2 is much harder than a single 4)
		if (goal == 50)
		{
			//Special case for if the goal is 50, since the below code would be unable to deal with it without significant modification
			return{ 21, 2 };
		}
		if (goal == 25)
		{
			return { 21, 1 };
		}

		//Find if the goal can be found in the array as a single target (including the outer bull)
		uint8_t* searchArray = std::find(std::begin(segments), std::end(segments), goal);
		if (searchArray != std::end(segments))
		{
			if (GetSegmentNumber(goal) != NULL)
			{
				return { GetSegmentNumber(goal), 1 };
			}
			else 
			{
				return { GetSegmentNumber(1), 1 };
			}
		}

		//If the above check fails then try to find if the target could be gotten with doubles or trebles
		else
		{
			if (goal % 2 == 0)
			{
				return { GetSegmentNumber(static_cast<uint8_t>(floor(goal / 2))), 2 };
			}
			else if (goal % 3 == 0)
			{
				return { GetSegmentNumber(static_cast<uint8_t>(floor(goal / 3))), 3 };
			}
		}
		return { GetSegmentNumber(1), 1 };
	}
}
