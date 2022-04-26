// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Menu.h"
#include "Playgame.h"

int main() {
	FixConsoleWindow();
	Nocursortype();
	drawBoard(0);
	mainMenu();
	int temp;
	while (true) {
		setColor(132);
		startGame();
		drawSnake();
		thread t1(threadFunction); //Create thread for snake
		HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
		while (1) {
			while (!returnisStoppingThread()) {
				temp = toupper(_getch());
				if (returnisAlive()) {
					if (temp == 'P') {
						pauseGame(handle_t1);
					}
					else if (temp == 27) {
						exitGame(handle_t1);
						exit(0);
					}
					else if (temp == 'k' || temp == 'K') {
						pauseGame(handle_t1);
						saveGame();
						system("cls");
						drawBoard(0);
						updateIsPlay();
						mainMenu();
						startGame();
					}
					else if (temp == 'l' || temp == 'L') {
						pauseGame(handle_t1);
						loadGame();
						ResumeThread(handle_t1);
					}
					else {
						ResumeThread(handle_t1);
						if ((temp != returnCharLock()) && (temp == 'D' || temp == 'A' || temp ==
							'W' || temp == 'S'))
						{
							if (temp == 'D') updateCharLock('A');
							else if (temp == 'W') updateCharLock('S');
							else if (temp == 'S') updateCharLock('W');
							else updateCharLock('D');
							updateMovingDirection(temp);
						}
					}
				}
				else updateSelecting(temp);
			}
		}
	}
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
