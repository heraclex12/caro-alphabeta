#pragma once
#include "_Board.h"
#include <fstream>
#include "_Common.h"
#include "_Bot.h"
class _Game {
public:
	static int _countTurn;
	static int _countWinA1;
	static int _countWinB;
	static int _countWinA2;
private:
	_Board *_b;
	bool _turn;
	int _x, _y;
	int _command;
	bool _loop;
	bool _defTurn;
public:
	_Game(int, int, int);
	~_Game();
	bool getTurn();
	int getCommand();
	bool isContinue();
	char waitKeyboard();   //ham nhan phim cua nguoi dung
	char askContinue();
	void startGame();  //bat dau game
	void exitGame(int);   //ket thuc game
	string getNameFile(int);
	int processFinish();
	int processAIGame(_Bot*&); //AI
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void mainMenu();
	void loadGame();
	void newGame();
	void saveGame(int);
	void guideGame();
	void settingGame();
	void AIGame(int);
	void PlayerGame(int);
};