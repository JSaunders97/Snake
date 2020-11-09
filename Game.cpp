#include "Game.h"
#include <conio.h>
#include <Windows.h>
#include <ctime>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

Game::Game() 
{
	Snake newSnake(10, 10);
	snake = newSnake;
}

void Game::initalise() {
	// Start screen for game
	std::cout << " - - - - - - - - - - - - - - - - - - - - - " << std::endl;
	for (int i = 0; i < 7; i++) { std::cout << "|                                         |" << std::endl; }
	std::cout << "|      SSS  N   N    A    K    K EEEEE    |" << std::endl;
	std::cout << "|     S   S NN  N   A A   K   K  E        |" << std::endl;
	std::cout << "|     S     NN  N  A   A  K  K   E        |" << std::endl;
	std::cout << "|      SSS  N N N  A   A  KKK    EEEE     |" << std::endl;
	std::cout << "|         S N  NN A AAA A K  K   E        |" << std::endl;
	std::cout << "|     S   S N  NN A     A K   K  E        |" << std::endl;
	std::cout << "|      SSS  N   N A     A K    K EEEEE    |" << std::endl;
	for (int i = 0; i < 3; i++) { std::cout << "|                                         |" << std::endl; }
	std::cout << "|          PRESS ENTER TO START!          |" << std::endl;
	for (int i = 0; i < 3; i++) { std::cout << "|                                         |" << std::endl; }
	std::cout << " - - - - - - - - - - - - - - - - - - - - - " << std::endl;

	int key = 0;
	while (key != KEY_ENTER) {
		key = _getch();
	}

	srand(time(0));
	start();

	return;

}

void Game::end() {
	system("cls");
	std::string scoreOut;
	std::cout << " - - - - - - - - - - - - - - - - - - - - - " << std::endl;
	for (int i = 0; i < 3; i++) { std::cout << "|                                         |" << std::endl; }
	std::cout << "|       GGGG     A    MM   MM EEEEE       |" << std::endl;
	std::cout << "|      G        A A   M M M M E           |" << std::endl;
	std::cout << "|      G   GG  AAAAA  M  M  M EEEE        |" << std::endl;
	std::cout << "|      G   G  A     A M     M E           |" << std::endl;
	std::cout << "|       GGGG  A     A M     M EEEEE       |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << "|          OOO  V   V EEEEE RRRR          |" << std::endl;
	std::cout << "|         O   O V   V E     R   R         |" << std::endl;
	std::cout << "|         O   O  V V  EEEE  RRRR          |" << std::endl;
	std::cout << "|         O   O  V V  E     R  R          |" << std::endl;
	std::cout << "|          OOO    V   EEEEE R   R         |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	scoreOut = (score < 10) ? ("|            YOUR SCORE WAS: ") : ("|           YOUR SCORE WAS: ");
	std::cout << scoreOut << score << "            |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << "|       PRESS ENTER TO RESTART NOW!       |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << "|            PRESS ESC TO EXIT            |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << " - - - - - - - - - - - - - - - - - - - - - " << std::endl;

	int key = 0;
	while (key != KEY_ESC && key != KEY_ENTER) {
		key = _getch();
	}

	if (key == KEY_ENTER) {
		restart();
	}

	return;
}

void Game::restart() {
	// Restart snake game
	Snake newSnake(10, 10);
	snake = newSnake;
	xPineapple = -1;
	yPineapple = -1;
	pineappleEaten = false;
	xBonusPineapple = -1;
	yBonusPineapple = -1;
	bonusPineapple = false;
	bonusPineappleCounter = 0;
	score = 0;
	pineapplesEaten = 0;
	gameSpeed = 10;
	start();
}

void Game::printGameBoard() {
	system("cls");
	std::cout << " - - - - - - - - - - - - - - - - - - - - - " << std::endl;
	for (int row = 0; row < 21; row++) {
		std::cout << "|";
		for (int col = 0; col < 21; col++) {
			if (col == 20) {
				std::cout << gameBoard[row][col];
			}
			else
			{
				std::cout << gameBoard[row][col] << " ";
			}
		}
		std::cout << "|" << std::endl;
	}
	std::cout << " - - - - - - - - - - - - - - - - - - - - - " << std::endl;
	// Debugging print out
	/*
	std::cout << "Score is: " << score << std::endl;
	std::cout << "bonusPineapple is: " << bonusPineapple << std::endl;
	std::cout << "bonusPineappleCounter is: " << bonusPineappleCounter << std::endl;
	std::cout << "pineapplesEaten is: " << pineapplesEaten << std::endl;
	std::cout << "gameSpeed is: " << gameSpeed << std::endl;
	std::cout << "pineappleEaten is: " << pineappleEaten << std::endl;
	*/
}

void Game::clearBoard() {
	//std::fill(std::begin(gameBoard[0]), std::end(gameBoard[40]), ' ');
	// Fill game board with spaces
	std::fill(&gameBoard[0][0], &gameBoard[0][0] + sizeof(gameBoard), ' ');
}

void Game::drawSnake() {
	Game::clearBoard();

	// Draw snake on board
	SnakeSegment* tmp = snake.head;
	gameBoard[(*tmp).y][(*tmp).x] = '+';
	while (tmp->backward != nullptr) {
		tmp = tmp->backward;
		gameBoard[(*tmp).y][(*tmp).x] = 'o';
	}

	// Draw pineapple
	if (!pineappleEaten) {
		gameBoard[yPineapple][xPineapple] = '@';
	}

	// Draw bonus pineapple
	if (bonusPineapple && bonusPineappleCounter < bonusPineappleTime) {
		gameBoard[yBonusPineapple][xBonusPineapple] = '$';
		bonusPineappleCounter++;
	}
	else if (bonusPineappleCounter == bonusPineappleTime) {
		bonusPineapple = false;
		bonusPineappleCounter = 0;
		if (pineappleEaten) {
			spawnPineapple();
		}
	}
}

void Game::start() {
	// start game
	int key = 0;
	int n = 0;
	int eat = 0;
	spawnPineapple();

	while (!(snake.isCollision())) {
		// While no collision has occured
		drawSnake();
		printGameBoard();
		key = 0;
		n = 0;
		while(n < gameSpeed){
			n++;
			Sleep(10);
			if (_kbhit() != 0) {
				switch ((key = _getch())) {
				case KEY_UP:
					//key up
					snake.switchDirection("UP");
					break;
				case KEY_DOWN:
					// key down
					snake.switchDirection("DOWN");
					break;
				case KEY_LEFT:
					// key left
					snake.switchDirection("LEFT");
					break;
				case KEY_RIGHT:
					// key right
					snake.switchDirection("RIGHT");
					break;
				default:
					// not arrow
					break;
				}
			}
		}

		snake.moveSnake();
		eat = eatenPineapple();
		if (eat != 0) {
			snake.addSegmentToEnd();
			switch (eat) {
			case 1:
				// Normal pineapple eaten
				score++;
				if (!bonusPineapple) {
					spawnPineapple();
				}
				break;
			case 2:
				// Bonus pineapple eaten
				bonusPineapple = false;
				bonusPineappleCounter = 0;
				score += 2;

				break;
			}
			increaseGameSpeed();
		}

	}

	end();

	return;
}

void Game::spawnPineapple() {
	// Spawn new pineapple
	pineappleEaten = false;
	do {
		xPineapple = rand() % 21;
		yPineapple = rand() % 21;
	} while (!legalPineappleSpawn(xPineapple, yPineapple));

	if (pineapplesEaten % 10 == 0 && pineapplesEaten != 0) {
		// Spawn bonus pineapple worth 2 points
		bonusPineapple = true;
		do {
			xBonusPineapple = rand() % 21;
			yBonusPineapple = rand() % 21;
			bonusPineappleTime = bonusTime();
		} while (!legalPineappleSpawn(xBonusPineapple, yBonusPineapple));
	}
}

bool Game::legalPineappleSpawn(int x, int y) {
	// Returns true if Pineapple spawn is legal and false otherwise
	SnakeSegment* tmp = snake.head;
	
	// Check head
	if (x == (*tmp).x && y == (*tmp).y) {
		return false;
	}

	// Check rest of snake
	while (tmp->backward != nullptr) {
		tmp = tmp->backward;
		if (x == (*tmp).x && y == (*tmp).y) {
			return false;
		}
	}

	return true;

}

int Game::eatenPineapple() {
	// Check if pineapple has been eaten

	if (snake.head->x == xPineapple && snake.head->y == yPineapple) {
		pineappleEaten = true;
		pineapplesEaten++;
		return 1;
	}
	else if (snake.head->x == xBonusPineapple && snake.head->y == yBonusPineapple && bonusPineapple) {
		pineapplesEaten++;
		return 2;
	}else {
		return 0;
	}
}

void Game::increaseGameSpeed() {
	// Increase game speed after 10 pineapples eaten
	if (pineapplesEaten % 10 == 0 && gameSpeed != 1 && pineapplesEaten != 0) {
		gameSpeed--;
	}
}

int Game::bonusTime() {
	// Compute bonus pineapple time based on distance

	int xDist, yDist;

	if (snake.head->x > xBonusPineapple) {
		xDist = snake.head->x - xBonusPineapple;
	}
	else {
		xDist = xBonusPineapple - snake.head->x;
	}

	if (snake.head->y > yBonusPineapple) {
		yDist = snake.head->y - yBonusPineapple;
	}
	else {
		yDist = yBonusPineapple - snake.head->y;
	}

	if (xDist > 10) {
		xDist = 21 - xDist;
	}

	if (yDist > 10) {
		yDist = 21 - yDist;
	}

	return xDist + yDist + 10;

}