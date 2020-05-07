#pragma once
#include <cstdint>

struct SegmentTarget {
	uint8_t segmentNumber;
	uint8_t AimModifier;
};

class Board
{
public:
	Board() = default;
	uint8_t segments[22] = { 20,1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20, 25 };

	//This functions name is misleading, it returns the value which was actually hit using the given accuracy stat
	int AimForSegment(int segmentNumber, uint8_t aimPreference, double accuracy);

	//Gets the highest/closest value to the goal
	//Returns index of the number on the board as well as whether or not to aim for a double or treble
	SegmentTarget GetBestTarget(uint8_t goal);

	//Gets the index of the desired number in the segments array
	uint8_t GetSegmentNumber(int target);
};