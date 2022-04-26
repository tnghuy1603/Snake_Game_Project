#pragma once
#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include <thread>

#define LENGTH_CS1 120  // Phan game
#define LENGTH_CS2  36   // Phan huong dan 
#define WIDTH_CS 36
#define WIDTH_BOX 3
#define LENGTH_BOX 16
#define STUDENT_ID "@2112047321120480211204881912046320120409"
#define MAX_FOOD_SIZE 3
using namespace std;
struct Box
{
	int x, y, length, width;     //x y la toa do goc tren ben trai cua box
};
struct Player {
	string name;
	int score;
};
void writeThankYou();
void updateIsPlay();
void drawBoard(int speed);
void Nocursortype();
void FixConsoleWindow();
void setColor(int color);
void gotoXY(int x, int y);
void setBox();
void drawBox(int x, int y, int length, int width);
void writeText(int x, int y, int length, string txt, int color);
void mainMenu();
void drawMainMenu(int cdt);
void drawLevelMenu(int cdt);
void drawSkinMenu(int cdt);
int Level();
void setStringBox();
void introductionMenu();
void clrscr();
void title1();
void title2();
int returnIdSkinColor();



