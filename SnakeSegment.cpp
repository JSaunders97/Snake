# include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;
	forward = nullptr;
	backward = nullptr;
}