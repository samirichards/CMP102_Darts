#include "Board.h"
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <iostream>



Board::Board()
{
}

Board::Board(int _segments[21])
{
	memcpy(segments, _segments, 21 * sizeof(int));
}

void Board::SetSegments(int _segments[21])
{
	memcpy(segments, _segments, 21 * sizeof(int));
}

int Board::AimForSegment(int segmentNumber, uint8_t aimPreference, int accuracy)
{
	//aimPreference == 1 == Just aim for the normal segment
	//aimPreference == 2 == Aim for a double
	//aimPreference == 3 == Aim for a treble

	srand(time(NULL));
	uint8_t value = rand() % 100;

	if (value <= accuracy)
	{

	}
	else
	{
		//Reuse random number here to determine which number is returned if the player misses their hit
		if (value < 50)
		{
			srand(time(NULL));
			uint8_t temp = rand() % 100;
			if (segmentNumber > 0)
			{
				if (temp > 20)
				{
					std::cout << segments[segmentNumber - 1] << " was hit\n";
					return segments[segmentNumber - 1];
				}
				if (temp >= 10 || temp <= 20)
				{
					std::cout << "Double " << segments[segmentNumber - 1] << " was hit\n";
					return 2 * segments[segmentNumber - 1];
				}
				if (temp >= 0 || temp < 10)
				{
					std::cout << "Treble " << segments[segmentNumber - 1] << " was hit\n";
					return 3 * segments[segmentNumber - 1];
				}
			}
			else
			{
				if (temp > 20)
				{
					std::cout << segments[20] << " was hit\n";
					return segments[20];
				}
				if (temp >= 10 || temp <= 20)
				{
					std::cout << "Double " << segments[20] << " was hit\n";
					return 2 * segments[20];
				}
				if (temp >= 0 || temp < 10)
				{
					std::cout << "Treble " << segments[20] << " was hit\n";
					return 3 * segments[20];
				}
			}
		}
		else
		{
			if (segmentNumber < 20)
			{
				return segments[segmentNumber + 1];
			}
			else
			{
				return segments[0];
			}
		}
	}

	return 0;
}

int Board::AimForBull(int accuracy, bool aimPreference)
{
	//aimPreference == 0 == aim for outer ring (25)
	//else aim for inner ring (50)
	return 0;
}

int Board::GetSegmentNumber(int target)
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
