#include "Snake.h"

Snake::Snake(int xCoord, int yCoord) {
	SnakeSegment* headSegment = new SnakeSegment(xCoord, yCoord);
	head = headSegment;
	tail = headSegment;
	x_tail = xCoord;
	y_tail = yCoord;
	snakeDirection = 0;
}

void Snake::addSegment(int xCoord, int yCoord) {
	// Add new segment to tail of snake

	SnakeSegment* newSegment = new SnakeSegment(xCoord, yCoord);

	SnakeSegment* old_tail = tail;

	tail->backward = newSegment;
	tail = newSegment;
	tail->forward = old_tail;
}

void Snake::addSegmentToEnd() {
	addSegment(x_tail, y_tail);
}

void Snake::printSnake() {
	// Print out snake from head to tail
	SnakeSegment* tmp = head;

	while (tmp->backward != nullptr) {
		std::cout << "(" << (*tmp).x << "," << (*tmp).y << ")" << std::endl;
		tmp = tmp->backward;
	}

	std::cout << "(" << (*tmp).x << "," << (*tmp).y << ")" << std::endl;

}

void Snake::moveSnake() {
	// Move snake according to snakeDirection
	SnakeSegment* tmp = tail;
	x_tail = (*tail).x;
	y_tail = (*tail).y;

	while (tmp->forward != nullptr) {
		tmp->x = tmp->forward->x;
		tmp->y = tmp->forward->y;
		tmp = tmp->forward;
	}

	switch (snakeDirection)
	{
	case 0: // Snake moving up
		if ((*head).y == 0) {(*head).y = 20;}
		else{ (*head).y--; }
		break;
	case 1: // Snake moving right
		if ((*head).x == 20) { (*head).x = 0; }
		else { (*head).x++; }
		break;
	case 2: // Snake moving down
		if ((*head).y == 20) { (*head).y = 0; }
		else { (*head).y++; }
		break;
	case 3: // Snake moving left
		if ((*head).x == 0) { (*head).x = 20; }
		else { (*head).x--; }
		break;
	}
}

void Snake::switchDirection(std::string newDirection) {
	// Change snake direction
	if (newDirection == "UP" && validMove(newDirection)) {
		snakeDirection = 0;
	}
	else if (newDirection == "RIGHT" && validMove(newDirection)) {
		snakeDirection = 1;
	}
	else if (newDirection == "DOWN" && validMove(newDirection)) {
		snakeDirection = 2;
	}
	else if (newDirection == "LEFT" && validMove(newDirection)) {
		snakeDirection = 3;
	}
	else {
		std::cout << "Error: Unacceptable snake direction, try: UP, RIGHT, DOWN or LEFT!";
	}
}

bool Snake::isCollision() {
	// Check if a collision has occured

	SnakeSegment* tmp = head;
	int newXCoord = (*tmp).x; 
	int newYCoord = (*tmp).y;

	while (tmp->backward != nullptr) {
		tmp = tmp->backward;
		if (newXCoord == (*tmp).x && newYCoord == (*tmp).y) {
			return true;
		}
	}

	return false;
}

bool Snake::validMove(std::string newDirection) {
	// Checks new move direction is valid i.e. snake cannot go back on itself
	if (newDirection == "UP") {
		if ((snakeDirection - 0) == 2) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (newDirection == "RIGHT") {
		if ((snakeDirection - 1) == 2) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (newDirection == "DOWN") {
		if ((2 - snakeDirection) == 2) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (newDirection == "LEFT") {
		if ((3 - snakeDirection) == 2) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}