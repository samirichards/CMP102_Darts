#pragma once
#include <cstdint>

struct SegmentTarget {
	uint8_t segmentNumber;
	uint8_t AimModifier;
};

class Board
{
public:
	Board();
	//Board(int _segments[21]);
	//void SetSegments(int _segments[21]);

	uint8_t segments[22] = { 20,1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20, 25 };

	int AimForSegment(int segmentNumber, uint8_t aimPreference, double accuracy);
	//int AimForBull(int accuracy, bool aimPreference);

	uint8_t GetSegmentNumber(int target);

	SegmentTarget GetBestTarget(uint8_t goal);
};