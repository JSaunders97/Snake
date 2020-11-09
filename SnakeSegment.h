class SnakeSegment {

public:

	int x, y;
	SnakeSegment* forward; 
	SnakeSegment* backward;

	SnakeSegment(int xCoord, int yCoord);

};