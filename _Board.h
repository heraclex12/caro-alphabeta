#pragma once
#include "_Point.h"
#include "_Common.h"
class _Board {
private:
	int _size;
	int _left, _top;
	_Point** _pArr;

public: 
	_Board(int, int, int);
	~_Board();
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	int getCheckAt(int, int);
	void resetData();
	void drawBoard(int);
	void drawFrame();
	int checkBoard(int, int, bool);
	int testBoard(int, int);
	int drawGame();			//Xet dieu kien hoa
	int winGame(int, int);
	void saveBoard(string);		//Luu bang game
	void loadBoard(string);    //Mo bang game da luu
	void makeMove(int, int, bool);
	void unMove(int, int);
	int getScore(int, bool);
	int heuristic(_Point*);
	int evaluate(_Point*);
};
int max4(int a, int b, int c, int d);
int min2(int a, int b);