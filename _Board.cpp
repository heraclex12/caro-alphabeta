#include "_Board.h"
#include "_Game.h"
#include <fstream>

int _Board::getLeft() {
	return _left;
}
int _Board::getTop() {
	return _top;
}
int _Board::getSize() {
	return _size;
}
int _Board::getXAt(int i, int j) {
	return _pArr[i][j].getX();
}
int _Board::getYAt(int i, int j) {
	return _pArr[i][j].getY();
}
int _Board::getCheckAt(int i, int j) {
	return _pArr[i][j].getCheck();
}
_Board::_Board(int pSize, int pX, int pY) {
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point*[pSize];
	for (int i = 0; i < pSize; i++) _pArr[i] = new _Point[pSize];
}
_Board::~_Board() {
	for (int i = 0; i < _size; i++) delete[] _pArr[i];
	delete[] _pArr;
}
/*
HÀM PHỤC HỒI DỮ LIỆU BÀN CỜ LẠI BAN ĐẦU
*/
void _Board::resetData() {
	if (_size == 0) {
		return;
	}
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_pArr[i][j].setX(4 * j + _left);
			_pArr[i][j].setY(2 * i + _top);
			_pArr[i][j].setCheck(0);
		}
	}
}
/*
HÀM VẼ BÀN CỜ VÀ GIAO DIỆN TRẬN ĐẤU
-Đầu vào: Chế độ chơi (1 - Nếu giữa người chơi với người chơi, 0 - Nếu giữa người chơi và máy)
*/
void _Board::drawBoard(int mode) {
	if (_pArr == NULL) return;
	printf("\n\n\n\n");
	printf("                                      ");
	printf("%c", 218);
	for (int i = 0; i < _size - 1; i++)
	{
		printf("%c%c%c%c", 196, 196, 196, 194);
	}
	printf("%c%c%c%c\n", 196, 196, 196, 191);
	printf("                                      ");
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = 0; j < _size + 1; j++)
		{
			printf("%c   ", 179);
		}
		printf("\n");
		printf("                                      ");
		printf("%c", 195);
		for (int i = 0; i < _size - 1; i++)
		{
			printf("%c%c%c%c", 196, 196, 196, 197);
		}
		printf("%c%c%c%c\n", 196, 196, 196, 180);
		printf("                                      ");
	}
	for (int j = 0; j < _size + 1; j++)
	{
		printf("%c   ", 179);
	}
	printf("\n");
	printf("                                      ");
	printf("%c", 192);
	for (int i = 0; i < _size - 1; i++)
	{
		printf("%c%c%c%c", 196, 196, 196, 193);
	}
	printf("%c%c%c%c\n", 196, 196, 196, 217);
	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY());
	_Common::gotoXY(28, 7); printf("%c", 187);
	_Common::gotoXY(28, 11); printf("%c", 188);
	for (int i = 5; i <= 27; i++)
	{
		_Common::gotoXY(i, 7); printf("%c", 205);
	}
	for (int i = 5; i <= 27; i++)
	{
		_Common::gotoXY(i, 11); printf("%c", 205);
	}
	for (int i = 8; i <= 10; i++)
	{
		_Common::gotoXY(28, i); printf("%c", 186);
	}
	_Common::gotoXY(88, 7); printf("%c", 201);
	_Common::gotoXY(88, 11); printf("%c", 200);
	for (int i = 89; i <= 114; i++)
	{
		_Common::gotoXY(i, 7); printf("%c", 205);
	}
	for (int i = 89; i <= 114; i++)
	{
		_Common::gotoXY(i, 11); printf("%c", 205);
	}
	for (int i = 8; i <= 10; i++)
	{
		_Common::gotoXY(88, i); printf("%c", 186);
	}
	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY());
	if (mode) {
		_Common::gotoXY(98, 8); cout << "Player 2";
		_Common::gotoXY(94, 10); cout << "Wins: ";
		_Common::gotoXY(13, 8); cout << "Player 1";
		_Common::gotoXY(8, 10); cout << "Wins: ";
		_Common::gotoXY(19, 10); _Common::SetColor(245); cout << _Game::_countWinA1;
		_Common::gotoXY(105, 10); _Common::SetColor(245); cout << _Game::_countWinA2;
	}
	else {
		_Common::gotoXY(98, 8); cout << "Com.";
		_Common::gotoXY(94, 10); cout << "Wins: ";
		_Common::gotoXY(13, 8); cout << "Player 1";
		_Common::gotoXY(8, 10); cout << "Wins: ";
		_Common::gotoXY(19, 10); _Common::SetColor(245); cout << _Game::_countWinA1;
		_Common::gotoXY(105, 10); _Common::SetColor(245); cout << _Game::_countWinB;
	}
}
/*
HÀM VẼ KHUNG VIỀN CHO CỬA SỔ GAME
*/
void _Board::drawFrame()
{
	_Common::SetColor(245);
	_Common::gotoXY(2, 0); printf("%c", 201);
	_Common::gotoXY(2, 28); printf("%c", 200);
	_Common::gotoXY(117, 0); printf("%c", 187);
	_Common::gotoXY(117, 28); printf("%c", 188);
	for (int i = 3; i <= 116; i++)
	{
		_Common::gotoXY(i, 0); printf("%c", 205);
	}
	for (int i = 3; i <= 116; i++)
	{
		_Common::gotoXY(i, 28); printf("%c", 205);
	}
	for (int i = 1; i <= 27; i++)
	{
		_Common::gotoXY(2, i); printf("%c", 186);
	}
	for (int i = 1; i <= 27; i++)
	{
		_Common::gotoXY(117, i); printf("%c", 186);
	}
	_Common::SetColor(245);
	_Common::gotoXY(4, 1); printf("%c", 201);
	_Common::gotoXY(4, 27); printf("%c", 200);
	_Common::gotoXY(115, 1); printf("%c", 187);
	_Common::gotoXY(115, 27); printf("%c", 188);
	for (int i = 5; i <= 114; i++)
	{
		_Common::gotoXY(i, 1); printf("%c", 205);
	}
	for (int i = 5; i <= 114; i++)
	{
		_Common::gotoXY(i, 27); printf("%c", 205);
	}
	for (int i = 2; i <= 26; i++)
	{
		_Common::gotoXY(4, i); printf("%c", 186);
	}
	for (int i = 2; i <= 26; i++)
	{
		_Common::gotoXY(115, i); printf("%c", 186);
	}
	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY());
}
/*
HÀM ĐÁNH DẤU BƯỚC ĐI LÊN BÀN CỜ
-Đầu vào: Tọa độ pX, pY, lượt đánh pTurn
-Đầu ra: Nếu đánh dấu được (-1 = TRUE, 1 = FALSE), 0 nếu tọa độ đã bị đánh dấu
*/
int _Board::checkBoard(int pX, int pY, bool pTurn) {
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0) {
				_Game::_countTurn++;
				if (pTurn) _pArr[i][j].setCheck(-1); //Neu luot hien hanh la true: c = -1
				else _pArr[i][j].setCheck(1);   //Neu luot hien hanh la false: c = 1
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}
/*
HÀM KIỂM TRA ĐIỀU KIỆN 2 NGƯỜI CHƠI HÒA NHAU (0 - Hòa, 1 - Tiếp tục)
*/
int _Board::drawGame() {
	if (_Game::_countTurn == _size * _size)          //tổng lượt đánh = số ô bàn cờ
		return 0;
	return 1;
}
/*
HÀM KIỂM TRA ĐIỀU KIỆN THẮNG THUA
-Đầu vào: Tọa độ người chơi mới đánh
*/
int _Board::winGame(int pX, int pY) {
	int x = 0, y = 0;
	bool next = true;
	//TÌM TỌA ĐỘ pX, pY tương ứng với vị trí [i,j]
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY) {
				x = i;
				y = j;
				next = false;
				break;
			}
		}
		if (!next) break;
	}

	//XÉT TRÊN HÀNG NGANG
	int count1 = 1;
	bool a1 = true, b1 = true;
	for (int i = 1; i <= 5; i++) {
		if (y - i >= 0) {
			if (_pArr[x][y - i].getCheck() == _pArr[x][y].getCheck())
			{
				count1++;
			}
			else if (_pArr[x][y - i].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				a1 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (y + i < _size) {
			if (_pArr[x][y + i].getCheck() == _pArr[x][y].getCheck()) {
				count1++;
			}
			else if (_pArr[x][y + i].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				b1 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count1 >= 5 && (a1 || b1)) return _pArr[x][y].getCheck();
	//XÉT TRÊN HÀNG DỌC
	int count2 = 1;
	bool a2 = true, b2 = true;
	for (int i = 1; i <= 5; i++) {
		if (x - i >= 0) {
			if (_pArr[x - i][y].getCheck() == _pArr[x][y].getCheck()) count2++;
			else if (_pArr[x - i][y].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				a2 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (x + i < _size) {
			if (_pArr[x + i][y].getCheck() == _pArr[x][y].getCheck()) count2++;
			else if (_pArr[x + i][y].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				b2 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count2 >= 5 && (a2 || b2)) return _pArr[x][y].getCheck();
	//XÉT TRÊN ĐƯỜNG CHÉO TRÁI TRÊN
	int count3 = 1;
	bool a3 = true, b3 = true;
	for (int i = 1; i <= 5; i++) {
		if (x - i >= 0 && y - i >= 0) {
			if (_pArr[x - i][y - i].getCheck() == _pArr[x][y].getCheck()) count3++;
			else if (_pArr[x - i][y - i].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				a3 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (x + i < _size && y + i < _size) {
			if (_pArr[x + i][y + i].getCheck() == _pArr[x][y].getCheck()) count3++;
			else if (_pArr[x + i][y + i].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				b3 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count3 >= 5 && (a3 || b3)) return _pArr[x][y].getCheck();
	//XÉT TRÊN ĐƯỜNG CHÉO PHẢI TRÊN
	int count4 = 1;
	bool a4 = true, b4 = true;
	for (int i = 1; i <= 5; i++) {
		if (x - i >= 0 && y + i < _size) {
			if (_pArr[x - i][y + i].getCheck() == _pArr[x][y].getCheck()) count4++;
			else if (_pArr[x - i][y + i].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				a4 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (x + i < _size && y - i >= 0) {
			if (_pArr[x + i][y - i].getCheck() == _pArr[x][y].getCheck()) count4++;
			else if (_pArr[x + i][y - i].getCheck() == (-1)*_pArr[x][y].getCheck()) {
				b4 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count4 >= 5 && (a4 || b4)) return _pArr[x][y].getCheck();
	return 0;
}
/*
HÀM TÌM SỐ NHỎ NHẤT TRONG 2 CHỮ SỐ
-Đầu vào: 2 số nguyên
-Đầu ra: số nguyên nhỏ nhất
*/
int min2(int a, int b) {
	return a < b ? a : b;
}
/*
HÀM TÌM SỐ LỚN NHẤT TRONG 4 CHỮ SỐ
-Đầu vào: 4 số nguyên
-Đầu ra: số nguyên lớn nhất
*/
int max4(int a, int b, int c, int d) {
	if (a > b && a > c && a > d) return a;
	if (b > a && b > c && b > d) return b;
	if (c > a && c > b && c > d) return c;
	return d;
}
/*
HÀM TÍNH ĐIỂM CỦA CÁC ĐÁNH DẤU LIÊN TIẾP
-Đầu vào: Số lượt đánh dấu liên tiếp, biến block thể hiện có đầu bị chặn
-Đầu ra: Số điểm có được
*/
int _Board::getScore(int n, bool block) {
	switch (n) {
	case 1: return 1; break;                                          //1 nút -> 1đ
	case 2: if (!block) return 3; else return 5; break;               //2 nút liên tiếp, bị chặn -> 3đ, không bị chặn 5đ
	case 3: if (!block) return 9; else return 11; break;              //3 nút liên tiếp, bị chặn -> 9đ, không bị chặn 11đ
	case 4: if (!block) return 99; else  return 101; break;           //4 nút liên tiếp, nếu bị chặn -> 99đ, không bị chặn -> 101đ
	case 5: return 100000; break;                   //5 nút liên tiếp
	default: return 100000; break;
	}
}
int _Board::heuristic(_Point* root) {

	int score = 0;
	int x = root->getX();
	int y = root->getY();
	//11
	int count11 = 0;
	int score11 = 0;
	bool a1 = true;
	for (int i = 1; i <= 6; i++) {
		if (y - i >= 0) {
			if (_pArr[x][y - i].getCheck() == -1) count11++;
			else if (_pArr[x][y - i].getCheck() == 1) {
				a1 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count11 >= 3) {
		score11 = 20;
		if (count11 == 4 && a1) score11 = 25000;
		else
		if (count11 == 3 && a1) score11 = 20000;
		else
		if (count11 >= 4 && !a1) score11 = 30000;
		if (count11 == 5) {
			if (a1)
				score11 = 50000;
			else score11 = 55000;
		}
	}
	//12
	int count12 = 0;
	int score12 = 0;
	bool b1 = true;
	for (int i = 1; i <= 6; i++) {
		if (y + i < _size) {
			if (_pArr[x][y + i].getCheck() == -1) count12++;
			else if (_pArr[x][y + i].getCheck() == 1) {
				b1 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count12 >= 3) {
		score12 = 20;
		if (count12 == 4 && b1) score12 = 25000;
		else
		if (count12 == 3 && b1) score12 = 20000;
		else
		if (count12 >= 4 && !b1) score12 = 30000;
		if (count12 == 5) {
			if (b1)
				score12 = 50000;
			else score12 = 55000;
		}
	}
	if (count12 != 0 && count11 != 0) {
		if (count12 + count11 >= 4) {
			score11 = max(40000,score11);
			score12 = max(40000,score12);
		}
	}
	//21
	int count21 = 0;
	bool a2 = true;
	int score21 = 0;
	for (int i = 1; i <= 6; i++) {
		if (x - i >= 0) {
			if (_pArr[x - i][y].getCheck() == -1) count21++;
			else if (_pArr[x - i][y].getCheck() == 1) {
				a2 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count21 >= 3) {
		score21 = 20;
		if (count21 == 4 && a2) score21 = 25000;
		else
		if (count21 == 3 && a2) score21 = 20000;
		else
		if (count21 >= 4 && !a2) score21 = 30000;
		if (count21 == 5) {
			if (a2)
				score21 = 50000;
			else score21 = 55000;
		}
	}
	//22
	int count22 = 0;
	bool b2 = true;
	int score22 = 0;
	for (int i = 1; i <= 6; i++) {
		if (x + i < _size) {
			if (_pArr[x + i][y].getCheck() == -1) count22++;
			else if (_pArr[x + i][y].getCheck() == 1) {
				b2 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count22 >= 3) {
		score22 =20;
		if (count22 == 4 && b2) score22 = 25000;
		else
		if (count22 == 3 && b2) score22 = 20000;
		else
		if (count22 >= 4 && !b2) score22 = 30000;
		if (count22 == 5) {
			if (b2)
				score22 = 50000;
			else score22 = 55000;
		}
	}
	if (count22 != 0 && count21 != 0) {
		if (count22 + count21 >= 4) {
			score21 = max(40000, score21);
			score22 = max(40000, score22);
		}
	}
	//31
	int count31 = 0;
	bool a3 = true;
	int score31 = 0;
	for (int i = 1; i <= 6; i++) {
		if (y - i >= 0 && x - i >= 0) {
			if (_pArr[x - i][y - i].getCheck() == -1) count31++;
			else if (_pArr[x - i][y - i].getCheck() == 1) {
				a3 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count31 >= 3) {
		score31 = 20;
		if (count31 == 4 && a3) score31 = 25000;
		else
		if (count31 == 3 && a3) score31 = 20000;
		else
		if (count31 >= 4 && !a3) score31 = 30000;
		if (count31 == 5) {
			if (a3)
				score31 = 50000;
			else score31 = 55000;
		}
	}
	//32
	int count32 = 0;
	bool b3 = true;
	int score32 = 0;
	for (int i = 1; i <= 6; i++) {
		if (y + i < _size && x + i < _size) {
			if (_pArr[x + i][y + i].getCheck() == -1) count32++;
			else if (_pArr[x + i][y + i].getCheck() == 1) {
				b3 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count32 >= 3) {
		score32 = 20;
		if (count32 == 4 && b3) score32 = 25000;
		else
		if (count32 == 3 && b3) score32 = 20000;
		else
		if (count32 >= 4 && !b3) score32 = 30000;
		if (count32 == 5) {
			if (b3)
				score32 = 50000;
			else score32 = 55000;
		}
	}
	if (count32 != 0 && count31 != 0) {
		if (count32 + count31 >= 4) {
			score31 = max(40000, score31);
			score32 = max(40000, score31);
		}
	}
	//41
	int count41 = 0;
	int score41 = 0;
	bool a4 = true;
	for (int i = 1; i <= 6; i++) {
		if (y + i < _size && x - i >= 0) {
			if (_pArr[x - i][y + i].getCheck() == -1) count41++;
			else if (_pArr[x - i][y + i].getCheck() == 1) {
				a4 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count41 >=3) {
		score41 = 20;
		if (count41 == 4 && a4) score41 = 25000;
		else
		if (count41 == 3 && a4) score41 = 20000;
		else
		if (count41 >= 4 && !a4) score41 = 30000;
		if (count41 == 5) {
			if (a4)
				score41 = 50000;
			else score41 = 55000;
		}
	}
	//42
	int count42 = 0;
	bool b4 = true;
	int score42 = 0;
	for (int i = 1; i <= 6; i++) {
		if (y - i >= 0 && x + i < _size) {
			if (_pArr[x + i][y - i].getCheck() == -1) count42++;
			else if (_pArr[x + i][y - i].getCheck() == 1) {
				b4 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (count42 >= 3) {
		score42 = 20;
		if (count42 == 4 && b4) score42 = 25000;
		else
		if (count42 == 3 && b4) score42 = 20000;
		else
		if (count42 >= 4 && !b4) score42 = 30000;
		if (count42 == 5) {
			if (b4)
				score42 = 50000;
			else score42 = 55000;
		}
	}
	if (count42 != 0 && count41 != 0) {
		if (count42 + count41 >= 4) {
			score41 = max(40000, score41);
			score42 = max(40000, score42);
		}
	}
	int scoreA = max4(score11, score21, score31, score41);
	int scoreB = max4(score12, score22, score32, score42);
	return scoreA > scoreB ? scoreA : scoreB;
}

int _Board::evaluate(_Point* root) {
	int score = 0;
	int x = root->getX();
	int y = root->getY();
	//XÉT TRÊN HÀNG NGANG
	int count1 = 1;
	int score1 = 0;
	bool a1 = true, b1 = true;
	for (int i = 1; i <= 5; i++) {
		if (y - i >= 0) {
			if (_pArr[x][y - i].getCheck() == 1) count1++;
			else if (_pArr[x][y - i].getCheck() == -1) {
				a1 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (y + i < _size) {
			if (_pArr[x][y + i].getCheck() == 1) count1++;
			else if (_pArr[x][y + i].getCheck() == -1) {
				b1 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (!a1 && !b1) score1 = 1;
	else
	score1 = getScore(count1, a1*b1);
	//XÉT TRÊN HÀNG DỌC
	int count2 = 1;
	int score2 = 0;
	bool a2 = true, b2 = true;
	for (int i = 1; i <= 5; i++) {
		if (x - i >= 0) {
			if (_pArr[x - i][y].getCheck() == 1) count2++;
			else if (_pArr[x - i][y].getCheck() == -1) {
				a2 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (x + i < _size) {
			if (_pArr[x + i][y].getCheck() == 1) count2++;
			else if (_pArr[x + i][y].getCheck() == -1) {
				b2 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (!a2 && !b2) score2 = 1;
	else
	score2 = getScore(count2, a2*b2);
	//XÉT TRÊN ĐƯỜNG XÉO TRÁI TRÊN
	int count3 = 1;
	int score3 = 0;
	bool a3 = true, b3 = true;
	for (int i = 1; i <= 5; i++) {
		if (x - i >= 0 && y - i >= 0) {
			if (_pArr[x - i][y - i].getCheck() == 1) count3++;
			else if (_pArr[x - i][y - i].getCheck() == -1) {
				a3 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (x + i <_size && y + i < _size) {
			if (_pArr[x + i][y + i].getCheck() == 1) count3++;
			else if (_pArr[x + i][y + i].getCheck() == -1) {
				b3 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (!a3 && !b3) score3 = 1;
	else
	score3 = getScore(count3, a3*b3);
	//XÉT TRÊN ĐƯỜNG XÉO PHẢI TRÊN
	int count4 = 1;
	int score4 = 0;
	bool a4 = true, b4 = true;
	for (int i = 1; i <= 5; i++) {
		if (x - i >= 0 && y + i < _size) {
			if (_pArr[x - i][y + i].getCheck() == 1) count4++;
			else if (_pArr[x - i][y + i].getCheck() == -1) {
				a4 = false;
				break;
			}
			else break;
		}
		else break;
	}
	for (int i = 1; i <= 5; i++) {
		if (x + i < _size && y - i >= 0) {
			if (_pArr[x + i][y - i].getCheck() == 1) count4++;
			else if (_pArr[x + i][y - i].getCheck() == -1) {
				b4 = false;
				break;
			}
			else break;
		}
		else break;
	}
	if (!a4 && !b4) score4 = 1;
	else
	score4 = getScore(count4, a4*b4);
	//ALL
	score = score1 + score2 + score3 + score4;
	int bonus = heuristic(root);
	return score + bonus;
}
/*
KIỂM TRA TRẠNG THÁI BÀN CỜ
-ĐẦU VÀO: TỌA ĐỌ x, y
-ĐẦU RA: 0 - Hòa, -1 - X thắng, 1 - O thắng, 2 - tiếp tục đánh
*/
int _Board::testBoard(int x, int y) {
	int result = winGame(x, y);
	if (result == -1) return -1; else if (result == 1) return 1;
	if (drawGame() == 0) return 0;
	return 2;
}
/*
TẢI LẠI BÀN CỜ TỪ FILE
-ĐẦU VÀO: TÊN FILE
-ĐẦU RA: KHÔNG CÓ
*/
void _Board::loadBoard(string filename) {
	ifstream file;
	file.open(filename);         //mở file để đọc
	string skipline;
	//Bỏ qua các dòng đầu
	getline(file, skipline);
	int mode = skipline[0] - 48;
	getline(file, skipline);
	getline(file, skipline);
	int s, l, t;
	//Đọc kích thước, tọa độ trái, tọa độ trên
	file >> s >> l >> t;
	_size = s;
	_left = l;
	_top = t;
	_pArr = new _Point*[_size];
	for (int i = 0; i < _size; i++) _pArr[i] = new _Point[_size];     
	resetData();       //khởi tạo bàn cờ
	drawBoard(mode);   //vẽ bàn cờ
	int temp;
	//Đọc bàn cờ
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			file >> temp;
			_pArr[i][j].setCheck(temp);
			_Common::gotoXY(_left + 4 * j, _top + 2 * i);
			if (_pArr[i][j].getCheck() == -1) {
				_Common::SetColor(249); 
				cout << "X";
			}
			else
				if (_pArr[i][j].getCheck() == 1) {
					_Common::SetColor(252); 
					cout << "O";
				}
		}
	}
	file.close();
}
/*
LƯU TRẠNG THÁI BẢNG VÀO FILE
-ĐẦU VÀO: TÊN FILE LƯU
-ĐẦU RA: KHÔNG CÓ
*/
void _Board::saveBoard(string filename) {
	ofstream file;
	file.open(filename, ios::app);             //mở file đã có để ghi
	file << _size <<" "<< _left <<" "<< _top << endl;             //ghi kích thước, tọa độ trái, tọa độ trên
	//ghi trạng thái bàn cờ
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			file << _pArr[i][j].getCheck() << " ";
		}
		file << endl;
	}
	file.close();
}
/*
ĐÁNH DẤU TẠI VỊ TRÍ CHỈ ĐỊNH
-ĐẦU VÀO: VỊ TRÍ [I,J], lượt đánh _turn
-ĐẦU RA: KHÔNG CÓ
*/
void _Board::makeMove(int i, int j, bool _turn) {
	if (_turn) {
		_pArr[i][j].setCheck(-1);  //-> Lượt X
	}
	else {
		_pArr[i][j].setCheck(1);   //-> Lượt O
	}
}
/*
BỎ ĐÁNH DẤU TẠI VỊ TRÍ CHỈ ĐỊNH
-ĐẦU VÀO: VỊ TRÍ [I,J]
-ĐẦU RA: KHÔNG CÓ
*/
void _Board::unMove(int i, int j) {
	_pArr[i][j].setCheck(0);   //-> Chưa có đánh dấu
}
