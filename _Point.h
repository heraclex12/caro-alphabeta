#pragma once
class _Point {
	int _y, _x, _check;
	//_check = -1 -> X
	//_check = 1 -> O
	//_check = 0 -> .
public:
	_Point();
	_Point(int, int);
	bool setCheck(int);
	int getX();
	int getY();
	int getCheck();
	void setX(int);
	void setY(int);
};
