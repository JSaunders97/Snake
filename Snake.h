#include <iostream>
#include "SnakeSegment.h"

class Snake {

public:

	SnakeSegment *head, *tail;
	int snakeDirection, x_tail, y_tail;

	Snake(int xCoord=0, int yCoord=0);

	void addSegment(int xCoord, int yCoord);

	void printSnake();

	void moveSnake();

	void addSegmentToEnd();

	void switchDirection(std::string newDirection);

	bool isCollision();

	bool validMove(std::string newDirection);

};