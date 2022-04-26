#include "Menu.h"
#include "Playgame.h"
// boxColor 140
// test1Color 228
// test2Color 134
string strMainMenu[6];
string strLevelMenu[4];
string strSkinMenu[5];
string tempStr = "Audio: OFF";
Box boxMainMenu[6];
Box boxLevelMenu[4];
Box boxSkinMenu[5];
int Lv = 1;
int skin = 0;
bool isPlay = false;
bool inMainMenu = true, inLevelMenu = false, inHighscore = false, inIntroduction = false, inSkin = false;
int idMainMenu = 0;
// 0 <= idMainMenu < 5
int idLevelMenu = 0;    //  0 <= idLevelMenu < 4
int idSkinMenu = 0;

void setStringBox()
{
	strMainMenu[0] = "Start";
	strMainMenu[1] = "Level";
	strMainMenu[2] = "Skin";
	strMainMenu[3] = "Highscore";
	strMainMenu[4] = "Audio: ON";
	strMainMenu[5] = "Introduction";

	strLevelMenu[0] = "Eazy";
	strLevelMenu[1] = "Medium";
	strLevelMenu[2] = "Hard";
	strLevelMenu[3] = "Expert";

	strSkinMenu[0] = "ooooo0";
	strSkinMenu[1] = "ooooo0";
	strSkinMenu[2] = "ooooo0";
	strSkinMenu[3] = "ooooo0";
	strSkinMenu[4] = "ooooo0";
}
void setBox()
{
	boxMainMenu[0] = { (LENGTH_CS1 - LENGTH_BOX) / 2,10,LENGTH_BOX ,WIDTH_BOX };
	boxMainMenu[1] = { (LENGTH_CS1 - LENGTH_BOX) / 2,13,LENGTH_BOX ,WIDTH_BOX };
	boxMainMenu[2] = { (LENGTH_CS1 - LENGTH_BOX) / 2,16,LENGTH_BOX ,WIDTH_BOX };
	boxMainMenu[3] = { (LENGTH_CS1 - LENGTH_BOX) / 2,19,LENGTH_BOX ,WIDTH_BOX };
	boxMainMenu[4] = { (LENGTH_CS1 - LENGTH_BOX) / 2,22,LENGTH_BOX ,WIDTH_BOX };
	boxMainMenu[5] = { (LENGTH_CS1 - LENGTH_BOX) / 2,25,LENGTH_BOX ,WIDTH_BOX };

	boxLevelMenu[0] = { (LENGTH_CS1 - LENGTH_BOX) / 2,13,LENGTH_BOX,WIDTH_BOX };
	boxLevelMenu[1] = { (LENGTH_CS1 - LENGTH_BOX) / 2,16,LENGTH_BOX,WIDTH_BOX };
	boxLevelMenu[2] = { (LENGTH_CS1 - LENGTH_BOX) / 2,19,LENGTH_BOX,WIDTH_BOX };
	boxLevelMenu[3] = { (LENGTH_CS1 - LENGTH_BOX) / 2,22,LENGTH_BOX,WIDTH_BOX };

	boxSkinMenu[0] = { (LENGTH_CS1 - LENGTH_BOX) / 2,13,LENGTH_BOX ,WIDTH_BOX };
	boxSkinMenu[1] = { (LENGTH_CS1 - LENGTH_BOX) / 2,17,LENGTH_BOX ,WIDTH_BOX };
	boxSkinMenu[2] = { (LENGTH_CS1 - LENGTH_BOX) / 2,20,LENGTH_BOX ,WIDTH_BOX };
	boxSkinMenu[3] = { (LENGTH_CS1 - LENGTH_BOX) / 2,23,LENGTH_BOX ,WIDTH_BOX };
	boxSkinMenu[4] = { (LENGTH_CS1 - LENGTH_BOX) / 2,27,LENGTH_BOX ,WIDTH_BOX };
}



void gotoXY(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void FixConsoleWindow() {

	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void setColor(int id)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, id);
}
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

int Level() {
	return Lv;
}

void drawBoard(int speed) // thoi gian Sleep
{
	setColor(34);
	for (int i = LENGTH_CS1; i > 0; i--)
	{
		gotoXY(i, 1);
		printf("%c", 196);
		Sleep(speed);
	}
	for (int i = 2; i <= WIDTH_CS; i++)
	{
		gotoXY(1, i);
		printf("%c", 179);
		Sleep(speed);
	}
	for (int i = 2; i <= LENGTH_CS1; i++)
	{
		gotoXY(i, WIDTH_CS);
		printf("%c", 196);
		Sleep(speed);
	}
	for (int i = WIDTH_CS; i >= 2; i--)
	{
		gotoXY(LENGTH_CS1, i);
		printf("%c", 179);
		Sleep(speed);
	}

	for (int i = LENGTH_CS1 + 2; i <= LENGTH_CS1 + LENGTH_CS2 + 2; i++)
	{
		gotoXY(i, 1);
		printf("%c", 196);
		Sleep(speed);
	}
	for (int i = 2; i <= WIDTH_CS; i++)
	{
		gotoXY(LENGTH_CS1 + LENGTH_CS2 + 2, i);
		printf("%c", 179);
		Sleep(speed);
	}
	for (int i = LENGTH_CS1 + LENGTH_CS2 + 1; i >= LENGTH_CS1 + 2; i--)
	{
		gotoXY(i, WIDTH_CS);
		printf("%c", 196);
		Sleep(speed);
	}
	for (int i = WIDTH_CS - 1; i >= 2; i--)
	{
		gotoXY(LENGTH_CS1 + 2, i);
		printf("%c", 179);
		Sleep(speed);
	}
	for (int i = 1; i <= WIDTH_CS / 2; i++)
	{
		gotoXY(LENGTH_CS1 + 1, i);
		printf("%c", 179);
		gotoXY(LENGTH_CS1 + 1, WIDTH_CS + 1 - i);
		printf("%c", 179);
		Sleep(speed);
	}
	if (!isPlay && !inIntroduction) title1();
}
void drawBox(int x, int y, int length, int width)
{
	setColor(136);
	gotoXY(x, y);
	cout << char(218);
	gotoXY(x + length - 1, y);
	cout << char(191);
	gotoXY(x, y + width - 1);
	cout << char(192);
	gotoXY(x + length - 1, y + width - 1);
	cout << char(217);
	for (int i = 1; i < length - 1; i++)
	{
		gotoXY(x + i, y);
		cout << char(196);
		gotoXY(x + i, y + width - 1);
		cout << char(196);
	}
	gotoXY(x + length - 1, y);
	cout << char(191);

	for (int i = 1; i < width - 1; i++)
	{
		gotoXY(x, y + i);
		cout << char(179);
		gotoXY(x + length - 1, y + i);
		cout << char(179);
	}
}
void drawMainMenu(int cdt) // Ve tu` o bg den' o ed nhung to dam. o cdt
{
	for (int i = 0; i < 6; i++) {
		if (i == cdt)
			writeText(boxMainMenu[i].x, boxMainMenu[i].y, boxMainMenu[i].length, strMainMenu[i], 228);
		else
			writeText(boxMainMenu[i].x, boxMainMenu[i].y, boxMainMenu[i].length, strMainMenu[i], 134);
	}
}
void drawLevelMenu(int cdt) // Ve tu` o bg den' o ed nhung to dam. o cdt
{
	for (int i = 0; i < 4; i++) {
		if (i == cdt)
			writeText(boxLevelMenu[i].x, boxLevelMenu[i].y, boxLevelMenu[i].length, strLevelMenu[i], 228);
		else
			writeText(boxLevelMenu[i].x, boxLevelMenu[i].y, boxLevelMenu[i].length, strLevelMenu[i], 134);
	};
}
void drawSkinMenu(int cdt) // Ve tu` o bg den' o ed nhung to dam. o cdt
{
	int color = 0;
	int color_cdt = 0;
	for (int i = 0; i < 5; i++) {
		if (i == cdt) {
			if (i == 0) color = 225;
			else if (i == 1) color = 228;
			else if (i == 2) color = 229;
			else if (i == 3) color = 230;
			else color = 237;
			color_cdt = color;
		}
		else {
			if (i == 0) color = 129;
			else if (i == 1) color = 132;
			else if (i == 2) color = 133;
			else if (i == 3) color = 134;
			else color = 141;
		}
		writeText(boxSkinMenu[i].x, boxSkinMenu[i].y, boxSkinMenu[i].length, strSkinMenu[i], color);
	}
	setColor(color_cdt);
	int pointStart = boxSkinMenu[cdt].x + (boxSkinMenu[1].length - 6) / 2;
	vector <Point> snakeMenu;
	snakeMenu.resize(6);
	snakeMenu[0] = { pointStart + 5,boxSkinMenu[0].y + 1 };
	snakeMenu[1] = { pointStart + 4,boxSkinMenu[0].y + 1 };
	snakeMenu[2] = { pointStart + 3,boxSkinMenu[0].y + 1 };
	snakeMenu[3] = { pointStart + 2,boxSkinMenu[0].y + 1 };
	snakeMenu[4] = { pointStart + 1,boxSkinMenu[0].y + 1 };
	snakeMenu[5] = { pointStart ,boxSkinMenu[0].y + 1 };
	while (1) {
		int x0 = 0;
		if (_kbhit()) return;
		for (int i = 0; i < 6; i++) {
			if (i == 0) {
				x0 = snakeMenu[i].x;
				if (snakeMenu[i].x + 1 <= boxSkinMenu[1].x + boxSkinMenu[1].length - 3)
					snakeMenu[i].x++;
				else snakeMenu[i].x = boxSkinMenu[1].x + 1;
			}
			else {
				int x00 = snakeMenu[i].x;
				snakeMenu[i].x = x0;
				x0 = x00;
			}
		}
		for (int i = 0; i < 6; i++) {
			gotoXY(snakeMenu[i].x, boxSkinMenu[cdt].y + 1);
			if (i == 0) cout << "0";
			else cout << "o";
		}
		gotoXY(x0, boxSkinMenu[cdt].y + 1);
		cout << " ";
		Sleep(50);
	}
}

void updateIsPlay() {
	isPlay = false;
	inMainMenu = true;
}
void mainMenu()
{
	setBox();
	setStringBox();
	drawMainMenu(0);
	while (!isPlay) {
		if (_kbhit())
		{
			char c = _getch();
			if (c == 'w' || c == 'W') {
				if (inMainMenu) {
					if (idMainMenu > 0) idMainMenu--;
					else idMainMenu = 5;
					drawMainMenu(idMainMenu);
				}
				else if (inLevelMenu) {
					if (idLevelMenu > 0) idLevelMenu--;
					else idLevelMenu = 3;
					drawLevelMenu(idLevelMenu);
				}
				else if (inSkin) {
					if (idSkinMenu > 0) idSkinMenu--;
					else idSkinMenu = 4;
					drawSkinMenu(idSkinMenu);
				}
			}
			else if (c == 's' || c == 'S') {
				if (inMainMenu) {
					if (idMainMenu < 5) idMainMenu++;
					else idMainMenu = 0;
					drawMainMenu(idMainMenu);
				}
				else if (inLevelMenu) {
					if (idLevelMenu < 3)idLevelMenu++;
					else idLevelMenu = 0;
					drawLevelMenu(idLevelMenu);
				}
				else if (inSkin) {
					if (idSkinMenu < 4) idSkinMenu++;
					else idSkinMenu = 0;
					drawSkinMenu(idSkinMenu);
				}
			}
			else if (c == 13) {
				if (inMainMenu) {
					inMainMenu = false;
					if (idMainMenu == 0) isPlay = true;
					else if (idMainMenu == 1) {
						inLevelMenu = true;
						clrscr();
						drawBoard(0);
						writeText(boxMainMenu[1].x - 3, boxMainMenu[1].y - 3, boxMainMenu[1].length + 6, strMainMenu[1], 228);
						drawLevelMenu(0);
					}
					else if (idMainMenu == 2) {
						inSkin = true;
						system("cls");
						setColor(134);
						drawBoard(0);
						writeText(boxMainMenu[2].x - 3, boxMainMenu[2].y - 6, boxMainMenu[2].length + 6, strMainMenu[2], 228);
						drawSkinMenu(0);
					}
					else if (idMainMenu == 3)
					{
						inHighscore = true;
						system("cls");
						drawBoard(0);
						highscoreMenu();
					}
					else if (idMainMenu == 4) {
						strMainMenu[4].swap(tempStr);
						drawMainMenu(4);
						inMainMenu = true;
					}
					else {
						inIntroduction = true;
						setColor(134);
						system("cls");
						drawBoard(0);
						introductionMenu();
					}
				}
				else if (inLevelMenu) Lv = idLevelMenu;
				else if (inSkin) {
					skin = idSkinMenu;
					drawSkinMenu(idSkinMenu);
				}
			}
			else if (c == 27) {
				if (inMainMenu) idMainMenu = 0;
				else if (inLevelMenu) inLevelMenu = false;
				else if (inSkin) inSkin = false;
				else if (inHighscore) inHighscore = false;
				else inIntroduction = false;
				inMainMenu = true;
				setColor(134);
				system("cls");
				drawBoard(0);
				drawMainMenu(idMainMenu);
			}
		}
	}
}

void introductionMenu() {
	setColor(142);
	gotoXY(60, 20);
	cout << "Do An: Snake-Game";
	gotoXY(60, 21);
	cout << "Nhom thuc hien: Nhom 17";
	gotoXY(60, 22);
	cout << "Giang vien: Truong Toan Thinh";
	gotoXY(60, 24);
	cout << "Danh sach thanh vien:";
	gotoXY(60, 25);
	cout << "21120473 - Tran Nguyen Gia Huy";
	gotoXY(60, 26);
	cout << "21120488 - Nguyen Dang Ba Kiet";
	gotoXY(60, 27);
	cout << "21120480 - Ta Ngoc Duy Khiem";
	gotoXY(60, 28);
	cout << "19120463 - Le Thanh Chau";
	gotoXY(60, 29);
	cout << "20120409 - Tran Thanh Tung";
	title2();
}
void writeText(int x, int y, int length, string txt, int color)
{
	setColor(color);
	int size = txt.length();
	int bien = (length - 2 - size) / 2;
	int i = 1;
	while (i < length - 1)
	{
		if (i <= bien || x > bien + size)
		{
			gotoXY(x + i, y + 1);
			cout << " ";
		}
		i++;
	}
	gotoXY(x + bien + 1, y + 1);
	cout << txt;
}
void title1() {
	fstream fp;
	setColor(135);
	fp.open("b.txt", ios::in);
	string str = {};
	int i = 0;
	while (!fp.eof()) {
		getline(fp, str);
		gotoXY(30, 2 + i);
		cout << str;
		i++;
		Sleep(15);
		cout << endl;
	}
}

void title2() {
	setColor(135);
	fstream fp;
	fp.open("a.txt", ios::in);
	string str = {};
	int i = 0;
	while (!fp.eof()) {
		getline(fp, str);
		gotoXY(20, 2 + i);
		cout << str;
		i++;
		Sleep(15);
		cout << endl;
	}
}

void writeThankYou() {
	setColor(135);
	fstream fp;
	fp.open("thankyou.txt", ios::in);
	string temp;
	int i = 0;
	while (!fp.eof()) {
		getline(fp, temp);
		gotoXY(10, 10 + i);
		cout << temp;
		i++;
		Sleep(15);
		cout << endl;
	}
}
int returnIdSkinColor() {
	return skin;
}
