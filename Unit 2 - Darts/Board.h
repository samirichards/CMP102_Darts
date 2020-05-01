#pragma once
#include <cstdint>
class Board
{
private:

public:
	Board();
	Board(int _segments[21]);
	void SetSegments(int _segments[21]);

	uint8_t segments[21] = { 20,1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20 };

	int AimForSegment(int segmentNumber, uint8_t aimPreference, int accuracy);
	int AimForBull(int accuracy, bool aimPreference);

	int GetSegmentNumber(int target);
};