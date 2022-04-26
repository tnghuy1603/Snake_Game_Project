#pragma once
#include "Menu.h"
using namespace std;
struct Point {
	int x, y;
};
bool returnisStoppingThread();

void updateCharLock(int c);

void updateSelecting(int c);

void highscoreMenu();

void writeFile();

void readFile();

bool isValid(int x, int y);

void generateFood();

void resetGame();

void moveLeft();

void moveRight();

void moveDown();

void moveUp();

bool crashItsBody();

bool crashWall();

bool crashGate();

void processDead();

void drawSnake();

void drawGate();

void drawFood();

void processGate();

void eatFood();

void pauseGame(HANDLE t);

void exitGame(HANDLE t);

void threadFunction();

void blinkedSnake();

bool isAlreadyExistedFileName(string fileName);

bool isValidFileName(string fileName);

bool isFileNameTooLong(string fileName);

void saveGame();

void loadGame();

void swapPlayer(Player& a, Player& b);

void sortHighScore();

void deleteBox(int x, int y, int length, int width);

void writeScore();

void startGame();

bool wantToPlayMore();

int returnCharLock();

bool returnisAlive();

void updateMovingDirection(int mD);

void drawObstacle();

bool crashObstacle();


