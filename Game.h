#include "Snake.h"

class Game {

public:

	char gameBoard[21][21] = { ' ' };

	Snake snake;

	int xPineapple = -1;

	int yPineapple = -1;

	bool pineappleEaten = false;

	int xBonusPineapple = -1;

	int yBonusPineapple = -1;

	bool bonusPineapple = false;

	int bonusPineappleCounter = 0;

	int score = 0;

	int pineapplesEaten = 0;

	int gameSpeed = 10;

	int bonusPineappleTime = 0;

	Game();

	void initalise();

	void printGameBoard();

	void clearBoard();

	void drawSnake();

	void start();

	void end();

	void restart();

	void spawnPineapple();

	bool legalPineappleSpawn(int x, int y);

	int eatenPineapple();

	void increaseGameSpeed();

	int bonusTime();

};