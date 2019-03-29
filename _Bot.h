#pragma once
#ifndef _BOT_H_
#define _BOT_H_
#include "_Board.h"
#include <cstdlib>
#include <ctime>
#include "_Common.h"
class _Bot 
{
	int _x, _y;
	_Point *root;
public:
	_Bot();
	 int alphaBeta(bool, _Board*, int, int, int);
	 int maxValue(bool, _Board*, int, int, int);
	 int minValue(bool, _Board*, int, int, int);
	 int getX();
	 int getY();
	 void moveRandom(_Board*);
};
#endif