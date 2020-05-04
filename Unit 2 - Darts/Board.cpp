#include "Board.h"
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <vector>



Board::Board()
{
}

//Board::Board(int _segments[21])
//{
//	memcpy(segments, _segments, 21 * sizeof(int));
//}

//void Board::SetSegments(int _segments[21])
//{
//	memcpy(segments, _segments, 21 * sizeof(int));
//}

int Board::AimForSegment(int segmentNumber, uint8_t aimPreference, uint8_t accuracy)
{
	//aimPreference == 1 == Just aim for the normal segment
	//aimPreference == 2 == Aim for a double
	//aimPreference == 3 == Aim for a treble

	srand(time(NULL));
	uint8_t value = rand() % 100;
	int retValue = 0;

	//If the value is below the accuracy stat then set the return value to the desired segment number
	if (value < accuracy)
	{
		retValue = segments[segmentNumber]; // THIS DOES NOT WORK, NEED TO FIGURE IT OUT
		//PROGRAM IS ATTEMPTING TO ACCESS MEM LOCATION 0X0 WHICH IS OFC ILLEGAL
	}
	//This means that if the value is in the bottom half of numbers between the accuracy stat and 100 then set the return value to one segment to the left
	if (value < (accuracy + (100 - accuracy) / 2))
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
		if (segmentNumber == 20)
		{
			retValue = segments[0];
		}
		else
		{
			retValue = segments[segmentNumber + 1];
		}
	}

	//AimPreference modifier takes effect here
	//If the value is less than accuracy% of accuracy then return the value they want multiplied by the given modifier, else just give them the segment as a single
	//This respects the accuracy stat, and rewards players with a high accuracy (this will be important in task 3 where the player can achieve a 100% accuracy)

	if (value < accuracy * (accuracy/100))
	{
		return retValue * aimPreference;
	}
	else
	{
		return retValue;
	}

	return 0;
}

int Board::AimForBull(int accuracy, bool aimPreference)
{
	//aimPreference == 1 == aim for outer ring (25)
	//aimPreference == 2 == aim for inner ring (50)
	srand(time(NULL));
	uint8_t value = rand() % 100;

	//If the player misses then return a random number from around the bull
	//Using the same double/treble formula as above, return the exact number the player is aiming for if they have a high accuracy, else just return the outer ring value
	//A side effect of this is that if the player is aiming for the 25 and they clear the first bar then they are always going to get it, since the default is 25 anyway

	if (value < accuracy)
	{
		if (value < (accuracy * (accuracy / 100)))
		{
			return 25 * aimPreference;
		}
		else
		{
			return 25;
		}
	}
	else {
		srand(time(NULL));
		uint8_t segTarget = rand() % 20;
		return segments[segTarget];
	}
	return 0;
}

//Find the segment number that corresponds with that given target value
uint8_t Board::GetSegmentNumber(int target)
{
	for (size_t i = 0; i < sizeof(segments); i++)
	{
		if (segments[i] == target)
		{
			return i;
		}
	}
	return NULL;
}

//This function will return the segment number and aim preference which should be used to get the desired goal / value closest to the goal
//TODO make this recognise that bulls exist
SegmentTarget Board::GetBestTarget(uint8_t goal)
{
	if (goal > 60)
	{
		return { 0, 3 };
	}
	else
	{
		if (goal % 3 == 0)
		{
			return { GetSegmentNumber(goal / 3), 3 };
		}
		if (goal % 2 == 0)
		{
			return { GetSegmentNumber(goal / 2), 2 };
		}
		else
		{
			return { GetSegmentNumber(goal), 1 };
		}
	}
}
