#include "Playgame.h"
#include "Menu.h"
#include <mmsystem.h>
vector<Point> snake;
vector<Point> food;
int score = 0;
int speed = 70;
bool isGateExist = false;
int foodIndex;
bool isAlive = true;
Point levelUp;
int charLock;
int movingDirection;
int gameRound;
int difficulty;
char selecting = ' ';
bool isStoppingThread = false;
int skinColor;
vector<Player> playerList;
vector<Point> obstacleRound2;
vector<Point> obstacleRound3;
void writeFile() {
	fstream playerInfor("users.txt", ios_base::out);
	for (int i = 0; i < playerList.size(); i++) {
		playerInfor << playerList[i].name << endl;
		playerInfor << playerList[i].score << endl;
	}
}
void readFile()
{
	playerList.resize(0);
	fstream playerInfor("users.txt", ios_base::in);
	string a;
	while (!playerInfor.eof()) {
		Player temp;
		getline(playerInfor, temp.name);
		getline(playerInfor, a);
		temp.score = atoi(a.c_str());

		playerList.push_back(temp);
	}
	playerInfor.close();
}
int returnCharLock() {
	return charLock;
}

// check coordinate is valid or not
bool isValid(int x, int y) {
	for (int i = 0; i < snake.size(); i++) {
		if (snake[i].y == y && snake[i].x == x) {
			return false;
		}
	}
	if (gameRound == 2) {
		for (int i = 0; i < obstacleRound2.size(); i++) {
			if (x == obstacleRound2[i].x && y == obstacleRound2[i].y) {
				return false;
			}
		}
	}
	if (gameRound == 3) {
		for (int i = 0; i < obstacleRound3.size(); i++) {
			if (x == obstacleRound3[i].x && y == obstacleRound3[i].y) {
				return false;
			}
		}
	}
	return true;
}
void drarwObstacle() {
	int curPosX = 0;
	int curPosY = 0;
	// draw round 2 obstacle
	if (gameRound == 2) {
		for (int i = LENGTH_CS1 / 2 - 15; i <= LENGTH_CS1 / 2 + 15; i++)
		{
			if (i < LENGTH_CS1 / 2 - 4 || i> LENGTH_CS1 / 2 + 4)
			{
				gotoXY(i, WIDTH_CS / 2 - 2);
				cout << (unsigned char)223;
				gotoXY(i, WIDTH_CS / 2 + 2);
				cout << (unsigned char)223;
				obstacleRound2.push_back({ i,WIDTH_CS / 2 - 2 });
				obstacleRound2.push_back({ i,WIDTH_CS / 2 + 2 });
			}

		}
		for (int i = WIDTH_CS / 2 - 8; i <= WIDTH_CS / 2 + 8; i++)
		{
			if (i <= WIDTH_CS / 2 - 2 || i >= WIDTH_CS / 2 + 2)
			{
				gotoXY(LENGTH_CS1 / 2 - 4, i);
				cout << (unsigned char)219;
				gotoXY(LENGTH_CS1 / 2 + 4, i);
				cout << (unsigned char)219;
				obstacleRound2.push_back({ LENGTH_CS1 / 2 - 4,i });
				obstacleRound2.push_back({ LENGTH_CS1 / 2 + 4,i });
			}
		}
		gotoXY(curPosX, curPosY);
	}
	if (gameRound == 3) {
		//delete map2 obstacle
		for (int i = LENGTH_CS1 / 2 - 15; i <= LENGTH_CS1 / 2 + 15; i++)
		{
			if (i < LENGTH_CS1 / 2 - 4 || i> LENGTH_CS1 / 2 + 4)
			{
				gotoXY(i, WIDTH_CS / 2 - 2);
				cout << ' ';
				gotoXY(i, WIDTH_CS / 2 + 2);
				cout << ' ';
				obstacleRound2.push_back({ i,WIDTH_CS / 2 - 2 });
				obstacleRound2.push_back({ i,WIDTH_CS / 2 + 2 });
			}

		}
		for (int i = WIDTH_CS / 2 - 8; i <= WIDTH_CS / 2 + 8; i++)
		{
			if (i <= WIDTH_CS / 2 - 2 || i >= WIDTH_CS / 2 + 2)
			{
				gotoXY(LENGTH_CS1 / 2 - 4, i);
				cout << ' ';
				gotoXY(LENGTH_CS1 / 2 + 4, i);
				cout << ' ';
				obstacleRound2.push_back({ LENGTH_CS1 / 2 - 4,i });
				obstacleRound2.push_back({ LENGTH_CS1 / 2 + 4,i });
			}
		}
		// draw map3 obstacle
		for (int i = 2; i <= 2 * LENGTH_CS1 / 5; i++)
		{
			if (i <= 4 * LENGTH_CS1 / 25 || i >= 7 * LENGTH_CS1 / 25)
			{
				gotoXY(i, WIDTH_CS / 3);
				cout << 'X';
				gotoXY(i, WIDTH_CS / 3);
				cout << 'X';
				obstacleRound3.push_back({ i, WIDTH_CS / 3 });
				obstacleRound3.push_back({ i, WIDTH_CS / 3 });
			}

		}
		for (int i = LENGTH_CS1 - 1; i >= 2 * LENGTH_CS1 / 5; i--)
		{
			if (i <= 3 * LENGTH_CS1 / 5 || i >= 4 * LENGTH_CS1 / 5)
			{
				gotoXY(i, 2 * WIDTH_CS / 3);
				cout << 'X';
				gotoXY(i, 2 * WIDTH_CS / 3);
				cout << 'X';
				obstacleRound3.push_back({ i, 2 * WIDTH_CS / 3 });
				obstacleRound3.push_back({ i, 2 * WIDTH_CS / 3 });
			}
		}
		for (int i = WIDTH_CS / 3; i > 0; i--)
		{
			gotoXY(2 * LENGTH_CS1 / 5, i);
			cout << 'X';
			obstacleRound3.push_back({ 2 * LENGTH_CS1 / 5, i });
		}
		for (int i = 2 * WIDTH_CS / 3; i < WIDTH_CS; i++)
		{
			gotoXY(2 * LENGTH_CS1 / 5, i);
			cout << 'X';
			obstacleRound3.push_back({ 2 * LENGTH_CS1 / 5, i });
		}
		gotoXY(curPosX, curPosY);
	}

}
bool crashObstacle() {
	if (gameRound == 3) {
		for (int i = 0; i < obstacleRound3.size(); i++) {
			if (snake[0].x == obstacleRound3[i].x && snake[0].y == obstacleRound3[i].y) {
				return true;
			}
		}
	}
	if (gameRound == 2) {
		for (int i = 0; i < obstacleRound2.size(); i++) {
			if (snake[0].x == obstacleRound2[i].x && snake[0].y == obstacleRound2[i].y) {
				return true;
			}
		}
	}
	return false;
}
// Generate food for snake to eat
void generateFood() {
	int x, y;
	srand((unsigned int)time(NULL));
	food.resize(MAX_FOOD_SIZE);
	for (int i = 0; i < MAX_FOOD_SIZE; i++)
	{
		do
		{
			x = rand() % (LENGTH_CS1 - 2) + 1;
			y = rand() % (WIDTH_CS - 2) + 1;
		} while (isValid(x, y) == false || x <= 2 || y <= 2);
		food[i] = { x,y };
	}
}
// reset data of game
void resetGame() {
	if (returnIdSkinColor() == 0)
		skinColor = 129;
	else if (returnIdSkinColor() == 1)
		skinColor = 132;
	else if (returnIdSkinColor() == 2)
		skinColor = 133;
	else if (returnIdSkinColor() == 3)
		skinColor = 134;
	else skinColor = 141;
	difficulty = Level();
	if (difficulty == 0) speed = 55;
	else if (difficulty == 1) speed = 40;
	else if (difficulty == 2) speed = 25;
	else speed = 10;
	gameRound = 1; charLock = 'A', movingDirection = 'D', foodIndex = 0, isGateExist = false, score = 0;
	snake.resize(6);
	snake[0] = { LENGTH_CS1 / 2 + 3, WIDTH_CS / 2 };
	snake[1] = { LENGTH_CS1 / 2 + 2, WIDTH_CS / 2 };
	snake[2] = { LENGTH_CS1 / 2 + 1, WIDTH_CS / 2 };
	snake[3] = { LENGTH_CS1 / 2 + 0, WIDTH_CS / 2 };
	snake[4] = { LENGTH_CS1 / 2 - 1, WIDTH_CS / 2 };
	snake[5] = { LENGTH_CS1 / 2 - 2, WIDTH_CS / 2 };
	generateFood();
}
void moveLeft()
{
	if (crashWall() || crashItsBody() || (crashGate() && isGateExist) || crashObstacle())
	{
		processDead();
	}
	else
	{
		if (snake[0].x - 1 == food[foodIndex].x && snake[0].y == food[foodIndex].y)
		{
			eatFood();
		}
		Point previousTail = { snake[snake.size() - 1].x, snake[snake.size() - 1].y };
		for (int i = snake.size() - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
		snake[0].x--;
		// delete previous tail
		gotoXY(previousTail.x, previousTail.y);
		cout << " ";
		charLock = 'D';
	}
}

void moveRight() {
	if (crashWall() || crashItsBody() || (crashGate() && isGateExist) || crashObstacle())
	{
		processDead();
	}
	else
	{
		if (snake[0].x - 1 == food[foodIndex].x && snake[0].y == food[foodIndex].y)
		{
			eatFood();
		}
		Point previousTail = { snake[snake.size() - 1].x, snake[snake.size() - 1].y };
		for (int i = snake.size() - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
		snake[0].x++;
		// delete previous tail
		gotoXY(previousTail.x, previousTail.y);
		cout << " ";
		charLock = 'A';
	}

}

void moveDown() {
	if (crashWall() || crashItsBody() || (crashGate() && isGateExist) || crashObstacle())
	{
		processDead();
	}
	else
	{
		if (snake[0].x == food[foodIndex].x && snake[0].y + 1 == food[foodIndex].y)
		{
			//PlaySound(TEXT("eating.wav"), NULL,| SND_SYNC);
			eatFood();

		}
		Point previousTail = { snake[snake.size() - 1].x, snake[snake.size() - 1].y };
		for (int i = snake.size() - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
		snake[0].y++;
		// delete previous tail
		gotoXY(previousTail.x, previousTail.y);
		cout << " ";
		charLock = 'W';
	}
}

void moveUp() {
	if (crashWall() || crashItsBody() || (crashGate() && isGateExist) || crashObstacle())
	{
		processDead();
	}
	else
	{
		if (snake[0].x == food[foodIndex].x && snake[0].y - 1 == food[foodIndex].y)
		{
			eatFood();
		}
		Point previousTail = { snake[snake.size() - 1].x, snake[snake.size() - 1].y };
		for (int i = snake.size() - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
		snake[0].y--;
		// delete previous tail
		gotoXY(previousTail.x, previousTail.y);
		cout << " ";
		charLock = 'S';
	}
}

bool crashItsBody() {
	for (int i = 1; i < snake.size(); i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			return true;
		}
	}
	return false;
}
bool crashWall() {
	if (snake[0].x <= 1 || snake[0].x >= LENGTH_CS1 || snake[0].y >= WIDTH_CS || snake[0].y <= 1) {
		return true;
	}
	return false;
}
bool crashGate() {
	if ((snake[0].x == levelUp.x + 1 && snake[0].y == levelUp.y) || (snake[0].x == levelUp.x - 1 && snake[0].y == levelUp.y - 1) || (snake[0].x == levelUp.x && snake[0].y == levelUp.y && charLock == 'S') || (snake[0].x == levelUp.x + 1 && snake[0].y == levelUp.y - 1) || (snake[0].x == levelUp.x - 1 && snake[0].y == levelUp.y)) {
		return true;
	}
	return false;
}

void processDead() {
	isAlive = false;
	PlaySound(NULL, NULL, SND_FILENAME | SND_SYNC);//Thêm âm thanh
	blinkedSnake();
}

void drawSnake() {
	setColor(skinColor);
	for (int i = 0; i < snake.size(); i++) {
		char point = STUDENT_ID[i];
		gotoXY(snake[i].x, snake[i].y);
		cout << point;
	}
}
// Draw gate to snake walk through
void drawGate() {
	setColor(0);
	do
	{
		levelUp.x = rand() % (LENGTH_CS1 - 4) + 2;
		levelUp.y = rand() % (WIDTH_CS - 4) + 3;
	} while (!isValid(levelUp.x, levelUp.y) || !isValid(levelUp.x - 1, levelUp.y) || !isValid(levelUp.x + 1, levelUp.y)
		|| !isValid(levelUp.x - 1, levelUp.y - 1) || !isValid(levelUp.x + 1, levelUp.y - 1));

	gotoXY(levelUp.x + 1, levelUp.y);
	cout << (unsigned char)223;
	gotoXY(levelUp.x - 1, levelUp.y - 1);
	cout << (unsigned char)219;
	gotoXY(levelUp.x, levelUp.y);
	cout << (unsigned char)223;
	gotoXY(levelUp.x + 1, levelUp.y - 1);
	cout << (unsigned char)219;
	gotoXY(levelUp.x - 1, levelUp.y);
	cout << (unsigned char)223;
	isGateExist = true;

}
void drawFood() {
	gotoXY(food[foodIndex].x, food[foodIndex].y);
	cout << "o";
}

void processGate() {
	if (isGateExist == false) {
		drawFood();
	}
	if (snake[0].y == levelUp.y && snake[0].x == levelUp.x && charLock == 'W' && isGateExist) {
		snake.erase(snake.begin());
	}
	if (snake.size() == 0) {
		gotoXY(levelUp.x + 1, levelUp.y);
		cout << " ";
		gotoXY(levelUp.x - 1, levelUp.y - 1);
		cout << " ";
		gotoXY(levelUp.x, levelUp.y);
		cout << " ";
		gotoXY(levelUp.x + 1, levelUp.y - 1);
		cout << " ";
		gotoXY(levelUp.x - 1, levelUp.y);
		cout << " ";
		isGateExist = false;
		movingDirection = 'D', charLock = 'A', gameRound++, speed++, foodIndex = 0;
		// display sound and effect
		// keep length unchange(length = 6) after level up
		snake.resize(6);
		snake[0] = { LENGTH_CS1 / 2 + 3, WIDTH_CS / 2 };
		snake[1] = { LENGTH_CS1 / 2 + 2, WIDTH_CS / 2 };
		snake[2] = { LENGTH_CS1 / 2 + 1, WIDTH_CS / 2 };
		snake[3] = { LENGTH_CS1 / 2 + 0, WIDTH_CS / 2 };
		snake[4] = { LENGTH_CS1 / 2 - 1, WIDTH_CS / 2 };
		snake[5] = { LENGTH_CS1 / 2 - 2, WIDTH_CS / 2 };
		drarwObstacle();
		generateFood();
	}
}

void eatFood() {
	snake.push_back(food[foodIndex]);
	score++;
	writeScore();
	if (foodIndex == MAX_FOOD_SIZE - 1) {
		drawGate();
		foodIndex = 0;
		generateFood();
	}
	else {
		foodIndex++;
	}
}

void pauseGame(HANDLE t) {
	SuspendThread(t);
}

void exitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);
}
void updateCharLock(int c) {
	charLock = c;
}
void updateMovingDirection(int mD) {
	if (mD == 'a' || mD == 's' || mD == 'd' || mD == 'w') {
		if (mD != (charLock + 32))
			movingDirection = mD;
	}
	else if (mD != charLock)
		movingDirection = mD;
}
void threadFunction() {
	while (1) {
		if (isAlive) {//If my snake is alive
			switch (movingDirection) {
			case 'A':
				moveLeft();
				break;
			case 'D':
				moveRight();
				break;
			case 'W':
				moveUp();
				break;
			case 'S':
				moveDown();
				break;
			}
			processGate();
			drawSnake();
			Sleep(2000 / speed);
		}
		else {
			bool wantToContinue = wantToPlayMore();
			if (!wantToContinue) {
				system("cls");
				drawBoard(0);
				writeThankYou();
				Sleep(5000);
				exit(0);
			}
		}
	}
}

// effect when snake dead
void blinkedSnake() {
	PlaySound(TEXT("gameover3.wav"), NULL, SND_FILENAME | SND_ASYNC);//Thêm âm thanh
	for (int i = 0; i < 5; i++) {
		Sleep(100);
		for (int i = 0; i < snake.size(); i++)
		{
			gotoXY(snake[i].x, snake[i].y);
			cout << STUDENT_ID[i];
		}
		Sleep(100);
		for (int i = 0; i < snake.size(); i++)
		{
			gotoXY(snake[i].x, snake[i].y);
			cout << " ";
		}
	}
	Sleep(500);
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);//Thêm âm thanh
}
// check player's name condition
bool isAlreadyExistedFileName(string fileName) {
	fstream inFile("users.txt", ios_base::in);
	string temp;
	string strScore;
	while (!inFile.eof()) {
		getline(inFile, temp);
		getline(inFile, strScore);
		if (strcmp(fileName.c_str(), temp.c_str()) == 0) {
			inFile.close();
			return true;
		}
	}
	inFile.close();
	return false;

}
bool isValidFileName(string fileName) {
	for (int i = 0; i < fileName.length(); i++) {
		if (fileName[i] == '>' || fileName[i] == '<' || fileName[i] == ':' || fileName[i] == '"' || fileName[i] == '/' || fileName[i] == '\\' || fileName[i] == '|' || fileName[i] == '?' || fileName[i] == '*') {
			return false;
		}
	}
	return true;
}

bool isFileNameTooLong(string fileName) {
	if (fileName.length() > 20) {
		return true;
	}
	return false;
}

void saveGame() {
	string fileName;
	int lengthbox = 30;
	int widthBox = 8;
	int xBox = LENGTH_CS1 / 2 - 15;
	int yBox = WIDTH_CS / 2 - 3;
	setColor(134);
	drawBox(xBox, yBox, lengthbox, widthBox);
	setColor(135);
	gotoXY(xBox + 9, yBox + 2);
	cout << "     Save game:    ";
	gotoXY(xBox + 3, yBox + 3);
	cout << "Name: ";
	do
	{
		gotoXY(xBox + 9, yBox + 3);
		cin >> fileName;
		gotoXY(xBox + 3, yBox + 4);
		setColor(134);
		if (isAlreadyExistedFileName(fileName)) {
			cout << "Already exist name";
		}
		if (!isValidFileName(fileName)) {
			cout << "Your name contain special character";
		}
		if (isFileNameTooLong(fileName)) {
			cout << "Your name is too long";
		}
		if (isAlreadyExistedFileName(fileName) || !isValidFileName(fileName) || isFileNameTooLong(fileName))
		{
			gotoXY(xBox + 9, yBox + 3);
			for (int i = 0; i < fileName.size(); i++)
				cout << " ";
		}
	} while (isAlreadyExistedFileName(fileName) || !isValidFileName(fileName) || isFileNameTooLong(fileName));
	deleteBox(xBox, yBox, lengthbox, widthBox);
	gotoXY(xBox + 3, yBox + 4);
	for (int i = 0; i < 40; i++) {
		cout << " ";
	}
	for (int i = 0; i < 6 + fileName.size(); i++)
	{
		gotoXY(xBox + 3 + i, yBox + 3);
		cout << " ";
	}

	ofstream outFile("users.txt", ios_base::app);// users.txt contain all player's name
	outFile << fileName << endl;
	outFile << score << endl;
	outFile.close();
	// save all information about game into <fileName>.txt
	ofstream saveGame(fileName + ".txt", ios_base::out);
	saveGame << snake.size() << endl;
	for (int i = 0; i < snake.size(); i++) {
		saveGame << snake[i].x << " " << snake[i].y << endl;
	}
	saveGame << foodIndex << endl;
	saveGame << food[foodIndex].x << " " << food[foodIndex].y << endl;
	if (isGateExist) {
		saveGame << levelUp.x << " " << levelUp.y << endl;
	}
	else {
		saveGame << -1 << " " << -1 << endl;
	}
	saveGame << movingDirection << endl;
	saveGame << charLock << endl;
	saveGame << score << endl;
	saveGame << speed << endl;
	saveGame << gameRound << endl;
	saveGame.close();
}

void loadGame() {
	string fileName;
	int lengthBox = 30;
	int widthBox = 8;
	int xBox = LENGTH_CS1 / 2 - 15;
	int yBox = WIDTH_CS / 2 - 3;
	setColor(134);
	for (int i = 0; i < widthBox; i++)
	{
		gotoXY(xBox, yBox + i);
		for (int j = 0; j < lengthBox; j++)
		{
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == widthBox - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == lengthBox - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}
	setColor(135);
	gotoXY(xBox + 9, yBox + 2);
	cout << "Load game:";
	gotoXY(xBox + 14, yBox + 5);
	gotoXY(xBox + 3, yBox + 3);
	cout << "Name: ";

	do
	{
		gotoXY(xBox + 9, yBox + 3);
		cin >> fileName;
		gotoXY(xBox + 3, yBox + 4);
		setColor(134);
		if (!isAlreadyExistedFileName(fileName)) {
			cout << "Not existed name";
		}
		if (!isAlreadyExistedFileName(fileName))
		{
			gotoXY(xBox + 9, yBox + 3);
			for (int i = 0; i < 20; i++)
				cout << " ";
		}
	} while (!isAlreadyExistedFileName(fileName));
	for (int i = 0; i < snake.size(); i++) {
		gotoXY(snake[i].x, snake[i].y);
		cout << " ";
	}
	// delete current food
	gotoXY(food[foodIndex].x, food[foodIndex].y);
	cout << " ";
	ifstream inFile(fileName + ".txt", ios_base::in);
	int snakeSize;
	inFile >> snakeSize;
	snake.resize(snakeSize);
	for (int i = 0; i < snake.size(); i++) {
		inFile >> snake[i].x >> snake[i].y;
	}
	
	inFile >> foodIndex;
	inFile >> food[foodIndex].x >> food[foodIndex].y;
	inFile >> levelUp.x >> levelUp.y;
	if (levelUp.x != -1 && levelUp.y != -1) {
		//draw gate
		gotoXY(levelUp.x + 1, levelUp.y);
		cout << (unsigned char)223;
		gotoXY(levelUp.x - 1, levelUp.y - 1);
		cout << (unsigned char)219;
		gotoXY(levelUp.x, levelUp.y);
		cout << (unsigned char)223;
		gotoXY(levelUp.x + 1, levelUp.y - 1);
		cout << (unsigned char)219;
		gotoXY(levelUp.x - 1, levelUp.y + 1);
		cout << (unsigned char)223;
		isGateExist = true;
	}
	inFile >> movingDirection;
	inFile >> charLock;
	inFile >> speed;
	inFile >> score;
	inFile >> gameRound;
	inFile.close();
}
void swapPlayer(Player& a, Player& b) {
	Player temp = a;
	a = b;
	b = temp;
}
void sortHighScore() {
	for (int i = 0; i < playerList.size() - 1; i++) {
		for (int j = i + 1; j < playerList.size(); j++) {
			if (playerList[i].score < playerList[j].score) {
				swapPlayer(playerList[i], playerList[j]);
			}
		}
	}
}
void deleteBox(int x, int y, int length, int width) {
	cout << " ";
	gotoXY(x + length - 1, y + width - 1);
	cout << " ";
	for (int i = 1; i < length - 1; i++)
	{
		gotoXY(x + i, y);
		cout << " ";
		gotoXY(x + i, y + width - 1);
		cout << " ";
	}
	gotoXY(x + length - 1, y);
	cout << " ";

	for (int i = 1; i < width - 1; i++)
	{
		gotoXY(x, y + i);
		cout << " ";
		gotoXY(x + length - 1, y + i);
		cout << " ";
	}
}
void writeScore()
{
	gotoXY(111, 5);
	cout << score;
}
void startGame() {
	system("cls");
	resetGame();
	drawBoard(0);
	isAlive = true;
	PlaySound(TEXT("countdown321toplay.wav"), NULL, SND_FILENAME | SND_SYNC);
	PlaySound(TEXT("background2.wav"), NULL, SND_FILENAME| SND_ASYNC|SND_LOOP);
	// display sound and effect
}
void updateSelecting(int c) {
	selecting = c;
}
bool returnisStoppingThread() {
	return isStoppingThread;
}
// when snake is dead, ask player want to play more game
bool wantToPlayMore() {
	bool wantToPlay = true;
	int lengthBox = 30;
	int widthBox = 8;
	int xBox = LENGTH_CS1 / 2 - 15;
	int yBox = WIDTH_CS / 2 - 3;
	isStoppingThread = true;
	setColor(134);
	for (int i = 0; i < widthBox; i++)
	{
		gotoXY(xBox, yBox + i);
		for (int j = 0; j < lengthBox; j++)
		{
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == widthBox - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == lengthBox - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}
	setColor(135);
	gotoXY(xBox + 3, yBox + 2);
	cout << "        Game Over                ";
	gotoXY(xBox + 3, yBox + 3);
	cout << "Name: ";
	string fileName;

	do {
		setColor(135);
		gotoXY(xBox + 9, yBox + 3);
		getline(cin, fileName);
		gotoXY(xBox + 3, yBox + 4);
		setColor(134);
		if (isAlreadyExistedFileName(fileName)) {
			cout << "Alreday existed name";
		}
		if (!isValidFileName(fileName)) {
			cout << "Contain invalid char";
		}
		if (isFileNameTooLong(fileName)) {
			cout << "Too long name";
		}
		if (isAlreadyExistedFileName(fileName) || !isValidFileName(fileName) || isFileNameTooLong(fileName))
		{
			gotoXY(xBox + 9, yBox + 3);
			for (int i = 0; i < 35; i++)
				cout << " ";
		}
	} while (isAlreadyExistedFileName(fileName) || !isValidFileName(fileName) || isFileNameTooLong(fileName));
	gotoXY(xBox + 3, yBox + 4);
	// delete warning file name condition
	for (int i = 0; i < 35; i++) {
		cout << " ";
	}
	fstream outFile("users.txt", ios_base::app);
	outFile << fileName << endl;
	outFile << score << endl;
	outFile.close();
	// delete file name if it is valid 
	for (int i = 0; i < 6 + fileName.size(); i++)
	{
		gotoXY(xBox + 3 + i, yBox + 3);
		cout << " ";
	}
	isStoppingThread = false;
	// delete map2 obstacle
	//if (gameRound == 2) {
	//	for (int i = LENGTH_CS1 / 2 - 15; i <= LENGTH_CS1 / 2 + 15; i++)
	//	{
	//		if (i < LENGTH_CS1 / 2 - 4 || i> LENGTH_CS1 / 2 + 4)
	//		{
	//			gotoXY(i, WIDTH_CS / 2 - 2);
	//			cout << ' ';
	//			gotoXY(i, WIDTH_CS / 2 + 2);
	//			cout << ' ';
	//			obstacleRound2.push_back({ i,WIDTH_CS / 2 - 2 });
	//			obstacleRound2.push_back({ i,WIDTH_CS / 2 + 2 });
	//		}

	//	}
	//	for (int i = WIDTH_CS / 2 - 8; i <= WIDTH_CS / 2 + 8; i++)
	//	{
	//		if (i <= WIDTH_CS / 2 - 2 || i >= WIDTH_CS / 2 + 2)
	//		{
	//			gotoXY(LENGTH_CS1 / 2 - 4, i);
	//			cout << ' ';
	//			gotoXY(LENGTH_CS1 / 2 + 4, i);
	//			cout << ' ';
	//			obstacleRound2.push_back({ LENGTH_CS1 / 2 - 4,i });
	//			obstacleRound2.push_back({ LENGTH_CS1 / 2 + 4,i });
	//		}
	//	}
	//}
	//// delete map3 obstacle
	//if (gameRound == 3) {
	//	for (int i = 2; i <= 2 * LENGTH_CS1 / 5; i++)
	//	{
	//		if (i <= 4 * LENGTH_CS1 / 25 || i >= 7 * LENGTH_CS1 / 25)
	//		{
	//			gotoXY(i, WIDTH_CS / 3);
	//			cout << " ";
	//			gotoXY(i, WIDTH_CS / 3);
	//			cout << " ";
	//			obstacleRound3.push_back({ i, WIDTH_CS / 3 });
	//			obstacleRound3.push_back({ i, WIDTH_CS / 3 });
	//		}

	//	}
	//	for (int i = LENGTH_CS1 - 1; i >= 2 * LENGTH_CS1 / 5; i--)
	//	{
	//		if (i <= 3 * LENGTH_CS1 / 5 || i >= 4 * LENGTH_CS1 / 5)
	//		{
	//			gotoXY(i, 2 * WIDTH_CS / 3);
	//			cout << " ";
	//			gotoXY(i, 2 * WIDTH_CS / 3);
	//			cout << " ";
	//			obstacleRound3.push_back({ i, 2 * WIDTH_CS / 3 });
	//			obstacleRound3.push_back({ i, 2 * WIDTH_CS / 3 });
	//		}
	//	}
	//	for (int i = WIDTH_CS / 3; i > 0; i--)
	//	{
	//		gotoXY(2 * LENGTH_CS1 / 5, i);
	//		cout << " ";
	//		obstacleRound3.push_back({ 2 * LENGTH_CS1 / 5, i });
	//	}
	//	for (int i = 2 * WIDTH_CS / 3; i < WIDTH_CS; i++)
	//	{
	//		gotoXY(2 * LENGTH_CS1 / 5, i);
	//		cout << " ";
	//		obstacleRound3.push_back({ 2 * LENGTH_CS1 / 5, i });
	//	}
	//}
	/*drawBox(xBox, yBox, lengthBox, widthBox);*/
	gotoXY(xBox + 3, yBox + 2);
	setColor(135);
	cout << "Do you want to play more?";
	gotoXY(xBox + 20, yBox + 4);
	cout << "No";
	gotoXY(xBox + 8, yBox + 4);
	setColor(134);
	cout << "Yes";
	string choice = "Yes";
	while ((int)selecting != 13) {
		if (selecting == 'D' || selecting == 'd') {
			if (choice != "No") {
				setColor(134);
				gotoXY(xBox + 20, yBox + 4);
				cout << "No";
				gotoXY(xBox + 8, yBox + 4);
				setColor(135);
				cout << "Yes";
				choice = "No";
			}
		}
		else if (selecting == 'A' || selecting == 'a') {
			if (choice != "Yes") {
				setColor(135);
				gotoXY(xBox + 20, yBox + 4);
				cout << "No";
				gotoXY(xBox + 8, yBox + 4);
				setColor(134);
				cout << "Yes";
				choice = "Yes";
			}
		}
	}
	isStoppingThread = true;
	if (choice == "Yes") {
		system("cls");
		updateIsPlay();
		drawBoard(0);
		mainMenu();
		startGame();
		isStoppingThread = false;
	}
	if (choice == "No") {
		wantToPlay = false;
	}
	selecting = 12;
	/*deleteBox(xBox, yBox, lengthBox, widthBox);*/
	return wantToPlay;
}
void highscoreMenu() {
	setColor(246);
	gotoXY(LENGTH_CS1 / 2 - 8, 9);
	cout << "Player";
	gotoXY(LENGTH_CS1 / 2 + 8, 9);
	cout << "Score";
	setColor(134);
	readFile();
	sortHighScore();
	if (playerList.size() >= 5) {
		for (int i = 0; i < 5; i++) {
			gotoXY(LENGTH_CS1 / 2 - 8, 12 + 2 * i);
			cout << playerList[i].name;
			gotoXY(LENGTH_CS1 / 2 + 8, 12 + 2 * i);
			cout << playerList[i].score;
		}
	}
	if (playerList.size() > 0 && playerList.size() < 5) {
		for (int i = 0; i < playerList.size(); i++) {
			gotoXY(LENGTH_CS1 / 2 - 8, 12 + 2 * i);
			cout << playerList[i].name;
			gotoXY(LENGTH_CS1 / 2 + 8, 12 + 2 * i);
			cout << playerList[i].score;
		}
	}

}
bool returnisAlive() {
	return isAlive;
}





