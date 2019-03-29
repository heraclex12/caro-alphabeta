#include "_Point.h"
_Point::_Point() {
	_x = _y = _check = 0;
}
_Point::_Point(int pX, int pY) {
	_x = pX;
	_y = pY;
	_check = 0;
}
int _Point::getX() {
	return _x;
}
int _Point::getY() {
	return _y;
}
int _Point::getCheck() {
	return _check;
}
void _Point::setX(int pX) {
	_x = pX;
}
void _Point::setY(int pY) {
	_y = pY;
}
/*
HÀM ĐÁNH DẤU VỊ TRÍ NƯỚC ĐI (-1 = PLAYER 1, 1 = PLAYER 2, 0 = Không có)
-Đầu vào: giá trị được đánh dấu
-Đầu ra: TRUE nếu đánh dấu thành công, ngược lại FALSE
*/
bool _Point::setCheck(int pCheck) {
	if (pCheck == -1 || pCheck == 1 || pCheck == 0) { 
		_check = pCheck;
		return true;
	}
	return false;
}
