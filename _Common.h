#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;
class _Common {
public:
	static void fixConsoleWindow();
	static void gotoXY(int, int);
	static void SetColor(int);
	static void ShowConsoleCursor(bool);
};
#endif
