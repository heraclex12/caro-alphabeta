#include "_Game.h"
#include <string>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
_Game::_Game(int pSize, int pLeft, int pTop) {
	_b = new _Board(pSize, pLeft, pTop);
	_loop = _turn = _defTurn = true;
	_command = -1;
	_x = pLeft;
	_y = pTop;
}
bool _Game::getTurn() {
	return _turn;
}
_Game::~_Game() {
	delete _b;
}
int _Game::getCommand() {
	return _command;
}
bool _Game::isContinue() {
	return _loop;
}
/*
HÀM CHỜ NGƯỜI CHƠI NHẬP BÀN PHÍM
-Đầu vào: Không có
-Đầu ra: Phím người dùng nhập
*/
char _Game::waitKeyboard() {
	_command = toupper(_getch());
	return _command;
}
char _Game::askContinue() {
	_Common::gotoXY(35, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 3);
	_Common::SetColor(124);
	cout << "Type \"Y\" if you want to continue, else \"N\": ";

	fflush(stdin);
	char c1 = toupper(getchar());
	char c2 = toupper(getchar());
	_Common::SetColor(245);
	return c1 == 'Y' ? c1 : c2;
}
string _Game::getNameFile(int pos) {
	ifstream nameFile("FILENAMESAVED.TXT");
	string name;
	while (!nameFile.eof()) {
		getline(nameFile, name);
		pos--;
		if (pos == 0) {
			nameFile.close();
			return name;
		}
	}
	nameFile.close();
	return "";
}
/*
HÀM MỞ TRẬN ĐẤU ĐÃ ĐƯỢC LƯU
*/
void _Game::loadGame() {
	_back:system("cls");
	_b->drawFrame();
	string filename;
	ifstream file;
	_Common::ShowConsoleCursor(false);
	getchar();
	_Common::gotoXY(_x + 15, _y);
	_Common::ShowConsoleCursor(true);
	cout << "<-Choose filename->"; 
	ifstream nameFile("FILENAMESAVED.TXT");
	int i = 4;
	string line;
	while (!nameFile.eof()) {
		getline(nameFile, line);
		if (line != "") {
			_Common::gotoXY(_x + 15, _y + i);
			cout << line << endl;
			i += 2;
		}
	}
	nameFile.close();
	unsigned char arrow = 175;
	int x = _x + 13, y = _y + 4;
	int pos = 1;
	bool break_loop = true;
	_Common::gotoXY(x, y);
	_Common::ShowConsoleCursor(false);
	cout << arrow;
	while (break_loop) {
		char ch = toupper(_getch());
		switch (ch) {
		case 'W':
			if (y > _y + 4) {
				y -= 2;
				pos--;
				_Common::gotoXY(x, y + 2);
				cout << " ";
				_Common::gotoXY(x, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 'S':
			if (y < _y + i - 2) {
				y += 2;
				pos++;
				_Common::gotoXY(x, y - 2);
				cout << " ";
				_Common::gotoXY(x, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 13: PlaySound(TEXT("enterrrr.wav"), NULL, SND_FILENAME | SND_ASYNC);
			filename = getNameFile(pos);
			break_loop = false;
			break;
		}
	}
	_Common::ShowConsoleCursor(true);
	file.open(filename);
	if (file.is_open()) {
		system("cls");
		int mode; //1 is PvP - 0 is PvC
		file >> mode;               //đọc chế độ chơi
		if (mode) {
			file >> _countWinA1 >> _countWinA2;           //Đọc số lượt thắng của Player1 và Player2
		}
		else {
			file >> _countWinA1 >> _countWinB;             //Đọc số lượt thắng của Player1 và Com.
		}
		file >> _turn >> _loop;             //đọc lượt đi, _loop -> trận đấu đã dừng hay chưa
		//Tải lại bàn cờ
		_b->loadBoard(filename);
		_x = _b->getXAt(0, 0);
		_y = _b->getYAt(0, 0);
		_Common::gotoXY(_x, _y);
		file.close();
		//Khởi động lại trận đấu
		if (mode) {
			PlayerGame(0);
		}
		else {
			AIGame(0);
		}
	}
	else { _Common::gotoXY(_x + 15, _y + 2); cout << "Unable to open file" << endl; _Common::ShowConsoleCursor(false); while (getchar() != '\n'); goto _back; }
}
/*
HÀM TẠO TRẬN ĐẤU MỚI
*/
void _Game::newGame() {
	system("cls");
	_b->drawFrame();
	string s;
	ifstream file("CARO.TXT");
	int i = 0;
	while (!file.eof()) {
		getline(file, s);
		_Common::gotoXY(_x - 10, _y + i);
		i += 1;
		cout << s << endl;
	}
	file.close();
	i += 2;
	_Common::ShowConsoleCursor(false);
	_Board *b1 = new _Board(3, _x + i, _y + i);
	b1->resetData();
	_Common::gotoXY(_x + 15, _y + i);
	int x1 = _x + 15, y1 = _y + i;
	cout << "PLAYER VS PLAYER" << endl;
	_Common::gotoXY(_x + 16, _y + i + 2);
	int x2 = _x + 16, y2 = _y + 2 + i;
	cout << "PLAYER VS COM." << endl;
	_Common::gotoXY(_x + 20, _y + i + 2 * 2);
	int x3 = _x + 20, y3 = _y + i + 2 * 2;
	cout << "BACK" << endl;
	int x = x1, y = y1;
	unsigned char arrow = 175;
	_Common::gotoXY(x - 4, y);
	cout << arrow;
	while (1) {
		char ch = toupper(_getch());
		switch (ch) {
		case 'W':
			if (y > y1) {
				y -= 2;
				_Common::gotoXY(x - 4, y + 2);
				cout << " ";
				_Common::gotoXY(x - 4, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 'S':
			if (y < b1->getYAt(b1->getSize() - 1, b1->getSize() - 1)) {
				y += 2;
				_Common::gotoXY(x - 4, y - 2);
				cout << " ";
				_Common::gotoXY(x - 4, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 13:PlaySound(TEXT("enterrrr.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (x == x1 && y == y1) { _Common::ShowConsoleCursor(true); delete b1; PlayerGame(1); return; }
			if (x == x2 - 1 && y == y2) { _Common::ShowConsoleCursor(true);  delete b1; AIGame(1); return; }
			if (x == x3 - 5 && y == y3) { mainMenu(); delete b1; return; }
			break;
		}
	}
}
/*
TẠO TRẬN ĐẤU MỚI CHẾ ĐỘ PLAYER VỚI PLAYER
*/
void _Game::PlayerGame(int check) {
	if (check) {
		system("cls");
		_b->resetData();   //Khởi tạo dữ liệu gốc
		_b->drawBoard(1);   //Vẽ bàn cờ
	}
	_b->drawFrame();
	//In mũi tên hiển thị lượt đánh
	if (_turn) {
		_Common::gotoXY(93, 8);
		cout << " ";
		_Common::gotoXY(23, 8);
		_Common::SetColor(252);
		unsigned char arrow = '<';
		cout << arrow;
	}
	else {
		_Common::gotoXY(23, 8);
		cout << " ";
		_Common::gotoXY(93, 8);
		_Common::SetColor(252);
		unsigned char arrow = '>';
		cout << arrow;
	}
	_x = _b->getXAt(_b->getSize() / 2 - 1, _b->getSize() / 2 - 1);
	_y = _b->getYAt(_b->getSize() / 2 - 1, _b->getSize() / 2 - 1);
	_Common::gotoXY(_x, _y);
	while (isContinue()) {
		waitKeyboard();
		if (getCommand() == 27) exitGame(1);
		else {
			switch (getCommand()) {
			case 'A': moveLeft(); break;
			case 'W': moveUp(); break;
			case 'D': moveRight(); break;
			case 'S': moveDown(); break;
			case 13:
				//Đánh dấu bàn cờ và kiểm tra thắng thua
				if (processCheckBoard()) {
					switch (processFinish()) {
					case -1: case 1: case 0:
						if (askContinue() != 'Y') {
							getchar(); exitGame(1);
						}
						else startGame();
						break;
					}
				}
			}
		}
	}
}
/*
HÀM HIỂN THỊ HƯỚNG DẪN CHƠI GAME
*/
void _Game::guideGame() {
	system("cls");
	_Common::gotoXY(_x + 15, _y);
	cout << "<========Guide=======>" << endl;
	_Common::gotoXY(_x + 21, _y + 2);
	cout << "|W| ->  UP" << endl;
	_Common::gotoXY(_x + 21, _y + 2 * 2);
	cout << "|A| ->  LEFT" << endl;
	_Common::gotoXY(_x + 21, _y + 2 * 3);
	cout << "|S| ->  DOWN" << endl;
	_Common::gotoXY(_x + 21, _y + 2 * 4);
	cout << "|D| ->  RIGHT" << endl;
	_Common::gotoXY(_x + 15, _y + 2 * 5);
	cout << "|ENTER| -> Put X or O" << endl;
	_Common::gotoXY(_x + 12, _y + 2 * 6);
	cout << "FIVE IN LINE (DON'T BLOCK) -> WIN" << endl;
	_Common::gotoXY(_x + 16, _y + 2 * 7);
	cout << "IF NO SPACES -> DRAW" << endl;
	_Common::gotoXY(_x + 15, _y + 2 * 8);
	cout << "---------------------" << endl;
	_Common::ShowConsoleCursor(false);
	getchar();
}
/*
TẠO TRẬN ĐẤU MỚI CHẾ ĐỘ PLAYER VỚI COMPUTER
*/
void _Game::AIGame(int check) {
	if (check) {
		system("cls");
		_b->resetData();   //khoi tao du lieu goc
		_b->drawBoard(0);   //ve man hinh game
	}
	_b->drawFrame();
	_x = _b->getXAt(_b->getSize() / 2 - 1, _b->getSize() / 2 - 1);
	_y = _b->getYAt(_b->getSize() / 2 - 1, _b->getSize() / 2 - 1);
	_Common::gotoXY(_x, _y);
	_Bot *bot = new _Bot();       //tạo Bot
	bool fistMove = true;

	while (isContinue()) {
		waitKeyboard();
		if (getCommand() == 27) exitGame(0);
		else {
			switch (getCommand()) {
			case 'A': moveLeft(); break;
			case 'W': moveUp(); break;
			case 'D': moveRight(); break;
			case 'S': moveDown(); break;
			case 13:
				//danh dau ban co, sau do kiem tra va xu ly thang thua hoa tiep tuc
				if (processCheckBoard()) {
					if (fistMove) {               //Bước đi đầu tiên của máy sẽ là ngẫu nhiên
						bot->moveRandom(_b);
						fistMove = false;
						_Common::gotoXY(_x, _y);
					}
					else {
						switch (processAIGame(bot)) {
						case -1: case 1: case 0:
							if (askContinue() != 'Y') {
								getchar(); exitGame(0);
							}
							else startGame();
							break;
						}
					}
				}
			}
		}
	}
}
/*
HÀM HIỂN THỊ CÀI ĐẶT TRÒ CHƠI
*/
void _Game::settingGame() {
	system("cls");
	_b->drawFrame();
	_Common::ShowConsoleCursor(false);
	_Board *b1 = new _Board(2, _x, _y);
	b1->resetData();
	_Common::gotoXY(_x - 5, _y);
	cout << "-Change turn: ";
	_Common::gotoXY(_x + 15, _y - 1);
	cout << "-X First";
	int x1 = _x + 15, y1 = _y - 1;
	_Common::gotoXY(_x + 15, _y + 1);
	cout << "-O First";
	int x2 = _x + 15, y2 = _y + 1;
	int x = x1 - 2, y = y1;
	unsigned char arrow = 175;
	_Common::gotoXY(x, y);
	cout << arrow;
	while (1) {
		char ch = toupper(_getch());
		switch (ch) {
		case 'W':
			if (y > y1) {
				y -= 2;
				_Common::gotoXY(x, y + 2);
				cout << " ";
				_Common::gotoXY(x, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 'S':
			if (y < y2) {
				y += 2;
				_Common::gotoXY(x, y - 2);
				cout << " ";
				_Common::gotoXY(x, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 13: PlaySound(TEXT("enterrrr.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (x + 2 == x1 && y == y1) { _Common::ShowConsoleCursor(true);  delete b1; _defTurn = true; _turn = true; return; }
			if (x + 2 == x2 && y == y2) { _Common::ShowConsoleCursor(true);  delete b1; _defTurn = false; _turn = false; return; }
			break;
		}
	}
	getchar();
}
/*
HÀM HIỂN THỊ MENU GIAO DIỆN CHÍNH
*/
void _Game::mainMenu() {
_back:system("cls");
	_b->drawFrame();
	string s;
	//Trang trí giao diện menu chính
	ifstream file("CARO.TXT");
	int i = 0;
	while (!file.eof()) {
		getline(file, s);
		_Common::gotoXY(_x - 10, _y + i);
		i += 1;
		cout << s << endl;
	}
	file.close();
	i += 2;
	_Common::ShowConsoleCursor(false);
	_Board *b1 = new _Board(5, _x + i, _y + i);
	b1->resetData();
	_Common::gotoXY(_x + 16, _y + i);
	int x1 = _x + 15, y1 = _y + i;
	cout << "START NEW GAME" << endl;
	_Common::gotoXY(_x + 18, _y + i + 2);
	int x2 = _x + 18, y2 = _y + 2 + i;
	cout << "LOAD GAME" << endl;
	_Common::gotoXY(_x + 20, _y + 2 * 2 + i);
	int x3 = _x + 20, y3 = _y + 2 * 2 + i;
	cout << "GUIDE" << endl;
	_Common::gotoXY(_x + 19, _y + 2 * 3 + i);
	int x4 = _x + 19, y4 = _y + 2 * 3 + i;
	cout << "SETTING" << endl;
	_Common::gotoXY(_x + 20, _y + 2 * 4 + i);
	int x5 = _x + 20, y5 = _y + 2 * 4 + i;
	cout << "EXIT" << endl;
	//Dịch chuyển lên xuống lựa chọn chức năng
	int x = x1, y = y1;
	unsigned char arrow = 175;
	_Common::gotoXY(x - 4, y);
	cout << arrow;
	while (1) {
		char ch = toupper(_getch());
		switch (ch) {
		case 'W':
			if (y > y1) {
				y -= 2;
				_Common::gotoXY(x - 4, y + 2);
				cout << " ";
				_Common::gotoXY(x - 4, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 'S':
			if (y < b1->getYAt(b1->getSize() - 1, b1->getSize() - 1)) {
				y += 2;
				_Common::gotoXY(x - 4, y - 2);
				cout << " ";
				_Common::gotoXY(x - 4, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 13: PlaySound(TEXT("enterrrr.wav"), NULL, SND_FILENAME | SND_ASYNC);
			//Khi nhấn Enter chọn
			if (x == x1 && y == y1) { _Common::ShowConsoleCursor(true);  delete b1; newGame(); return; }
			if (x == x2 - 3 && y == y2) { _Common::ShowConsoleCursor(true);  delete b1; loadGame(); return; }
			if (x == x3 - 5 && y == y3) { _Common::ShowConsoleCursor(true);  delete b1; guideGame(); goto _back; }
			if (x == x4 - 4 && y == y4) { _Common::ShowConsoleCursor(true);  delete b1; settingGame(); goto _back; return; }
			if (x == x5 - 5 && y == y5) { delete b1; exit(0); }
			break;
		}
	}
}
/*
HÀM BẮT ĐẦU TRÒ CHƠI
*/
void _Game::startGame() {
	system("cls");
	_turn = _defTurn;
	_x = _b->getLeft();
	_y = _b->getTop();
	mainMenu();
}
/*
HÀM LƯU LẠI TRẬN ĐẤU
-Đầu vào: Chế độ chơi (1 - PlayervPlayer, 0 - PlayervCom.)
*/
void _Game::saveGame(int mode) {
	_back:system("cls");
	_b->drawFrame();
	ofstream file;
	string filename;
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
	_Common::ShowConsoleCursor(false);
	getchar();
	_Common::gotoXY(_x, _y);
	_Common::gotoXY(_x + 5, _y + 4);
	_Common::ShowConsoleCursor(true);
	cout << "Enter filename: ";  getline(cin, filename);
	if (filename == "") { _Common::gotoXY(_x + 5, _y + 6); cout << "Filename isn't empty"; goto _back; }
	ofstream nameFile("FILENAMESAVED.TXT", ios::out | ios::app);
	nameFile << filename << endl;
	nameFile.close();
	file.open(filename);
	file << mode << endl;
	if (mode) { file << _countWinA1 << " " << _countWinA2 << endl; }     //Ghi số trận thắng của Player1 và Player2
	else { file << _countWinA1 << " " << _countWinB << endl; }          //Ghi số trận thắng của Player1 và Com.
	file << _turn << " " << _loop << endl;                    //Ghi lượt hiện tại, điều kiện tiếp tục
	_b->saveBoard(filename);                       //lưu bàn cờ
	file.close();
}
/*
HÀM THOÁT KHỎI TRẬN ĐẤU
-Đầu vào: Chế độ chơi (1 - PlayervPlayer, 0 - PlayervCom.)
*/
void _Game::exitGame(int mode) {
	_b->drawFrame();
	system("cls");
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
	_Common::gotoXY(_x, _y);
	_Common::ShowConsoleCursor(false);
	//co the luu game truoc khi exit
	_Common::gotoXY(_x + 11, _y + 4);
	cout << "Would you like to save it?";
	_Board *b1 = new _Board(2, _x, _y);
	b1->resetData();
	_Common::gotoXY(_x + 17, _y + 7);
	int x1 = _x + 17, y1 = _y + 7;
	cout << "Save" << endl;
	_Common::gotoXY(_x + 27, _y + 7);
	int x2 = _x + 27, y2 = _y + 7;
	cout << "Cancel" << endl;
	_Common::gotoXY(_x + 17, _y + 7);
	int break_loop = 1;
	int x = _x + 15, y = _y + 7;
	unsigned char arrow = 175;
	_Common::gotoXY(x, y);
	cout << arrow;
	while (break_loop) {
		char ch = toupper(_getch());
		switch (ch) {
		case 'A':
			if (x > x1) {
				x -= 10;
				_Common::gotoXY(x + 10, y);
				cout << " ";
				_Common::gotoXY(x, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 'D':
			if (x < x2) {
				x += 10;
				_Common::gotoXY(x - 10, y);
				cout << " ";
				_Common::gotoXY(x, y);
				cout << arrow;
				PlaySound(TEXT("applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 13:
			PlaySound(TEXT("enterrrr.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (x + 2 == x1 && y == y1) { delete b1; _Common::ShowConsoleCursor(true); saveGame(mode); break_loop = 0; startGame();
			}    //Luu game
			if (x + 2 == x2 && y == y2) { delete b1; startGame(); }          //Khong luu
		}
	}
	_loop = false;
}
/*
HÀM XỬ LÝ ĐÁNH DẤU BÀN CỜ
*/
bool _Game::processCheckBoard() {
	switch (_b->checkBoard(_x, _y, _turn)) {
	case -1:_Common::SetColor(249); cout << "X"; PlaySound(TEXT("bat+hit+ball.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case 1:_Common::SetColor(252); cout << "O"; PlaySound(TEXT("bat+hit+ball.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case 0: return false;   //khi danh vao o da danh roi
	}
	return true;
}
/*
HÀM XỬ LÝ TRẬN ĐẤU GIỮA PLAYER & PLAYER
-Đầu vào: đối tượng Bot
-Đầu ra:
*/
int _Game::processFinish() {
	//nhay toi vi tri thich hop de in chuoi thang/thua/hoa
	_Common::gotoXY(37, 3);
	int pWhoWin = _b->testBoard(_x, _y);
	switch (pWhoWin) {
	case -1: _Game::_countWinA1++;
		_Common::gotoXY(19, 10); _Common::SetColor(245);
		cout << _Game::_countWinA1;
		_Common::gotoXY(45, 3); _Common::SetColor(245);
		PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 240; i <= 255; i++)
		{
			_Common::ShowConsoleCursor(false);
			_Common::gotoXY(45, 2);
			_Common::SetColor(i);
			cout << "PLAYER 1 WINS, PLAYER 2 LOSES" << endl;
			_Common::gotoXY(19, 2); printf("%c", 201);
			_Common::gotoXY(19, 3); printf("%c", 200);
			_Common::gotoXY(102, 2); printf("%c", 187);
			_Common::gotoXY(102, 3); printf("%c", 188);

			for (int i = 20; i <= 43; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 75; i <= 101; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 20; i <= 101; i++)
			{
				_Common::gotoXY(i, 3); printf("%c", 205);
			}
			Sleep(250);
		}
		_Common::ShowConsoleCursor(true);
		break;
	case 1: _Game::_countWinA2++;
		_Common::gotoXY(105, 10); _Common::SetColor(245);
		cout << _Game::_countWinA2;
		_Common::gotoXY(45, 2);
		PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 240; i <= 255; i++)
		{
			_Common::ShowConsoleCursor(false);
			_Common::gotoXY(45, 2);
			_Common::SetColor(i);
			cout << "PLAYER 2 WINS, PLAYER 1 LOSES." << endl;
			_Common::gotoXY(19, 2); printf("%c", 201);
			_Common::gotoXY(19, 3); printf("%c", 200);
			_Common::gotoXY(102, 2); printf("%c", 187);
			_Common::gotoXY(102, 3); printf("%c", 188);

			for (int i = 20; i <= 43; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 75; i <= 101; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 20; i <= 101; i++)
			{
				_Common::gotoXY(i, 3); printf("%c", 205);
			}
			Sleep(250);
		}
		_Common::ShowConsoleCursor(true);
		break;
	case 0:
		_Common::gotoXY(45, 2);
		_Common::SetColor(245);
		PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 240; i <= 255; i++)
		{
			_Common::ShowConsoleCursor(false);
			_Common::gotoXY(45, 3);
			_Common::SetColor(i);
			cout << "PLAYER 1 and PLAYER 2 ARE DRAW" << endl;
			_Common::gotoXY(19, 2); printf("%c", 201);
			_Common::gotoXY(19, 3); printf("%c", 200);
			_Common::gotoXY(102, 2); printf("%c", 187);
			_Common::gotoXY(102, 3); printf("%c", 188);

			for (int i = 20; i <= 43; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 75; i <= 101; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 20; i <= 101; i++)
			{
				_Common::gotoXY(i, 3); printf("%c", 205);
			}
			Sleep(250);
		}
		_Common::ShowConsoleCursor(true);
		break;
	case 2: _turn = !_turn; //đổi lượt nếu không có gì xảy ra	
		if (_turn) {
			_Common::gotoXY(93, 8);
			cout << " ";
			_Common::gotoXY(23, 8);
			_Common::SetColor(252);
			unsigned char arrow = '<';
			cout << arrow;
		}
		else {
			_Common::gotoXY(23, 8);
			cout << " ";
			_Common::gotoXY(93, 8);
			_Common::SetColor(252);
			unsigned char arrow = '>';
			cout << arrow;
		}
	}
	_Common::gotoXY(_x, _y);   //Tra ve vi tri hien hanh cua con tro man hinh ban co
	return pWhoWin;
}
/*
HÀM XỬ LÝ TRẬN ĐẤU GIỮA PLAYER & MÁY
-Đầu vào: đối tượng Bot
-Đầu ra:
*/
int _Game::processAIGame(_Bot *&bot) {
	//nhay toi vi tri thich hop de in chuoi thang/thua/hoa
	_Common::gotoXY(37, 3);
	int pWhoWin = _b->testBoard(_x, _y);

	switch (pWhoWin) {
	case -1: _Game::_countWinA1++;
		_Common::gotoXY(19, 10); _Common::SetColor(245); cout << _Game::_countWinA1;
		_Common::gotoXY(45, 3);
		PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 240; i <= 255; i++)
		{
			_Common::ShowConsoleCursor(false);
			_Common::gotoXY(45, 2);
			_Common::SetColor(i);
			cout << "PLAYER WINS, COM. LOSES!" << endl;
			_Common::gotoXY(19, 2); printf("%c", 201);
			_Common::gotoXY(19, 3); printf("%c", 200);
			_Common::gotoXY(102, 2); printf("%c", 187);
			_Common::gotoXY(102, 3); printf("%c", 188);

			for (int i = 20; i <= 43; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 68; i <= 101; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 20; i <= 101; i++)
			{
				_Common::gotoXY(i, 3); printf("%c", 205);
			}
			Sleep(250);
		}
		_Common::ShowConsoleCursor(true);
		break;
	case 1: _Game::_countWinB++;
		_Common::gotoXY(105, 10); _Common::SetColor(245); cout << _Game::_countWinB;
		_Common::gotoXY(45, 3);
		PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 240; i <= 255; i++)
		{
			_Common::ShowConsoleCursor(false);
			_Common::gotoXY(45, 2);
			_Common::SetColor(i);
			cout << "PLAYER LOSES, COM. WINS!" << endl;
			_Common::gotoXY(19, 2); printf("%c", 201);
			_Common::gotoXY(19, 3); printf("%c", 200);
			_Common::gotoXY(102, 2); printf("%c", 187);
			_Common::gotoXY(102, 3); printf("%c", 188);

			for (int i = 20; i <= 43; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 68; i <= 101; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 20; i <= 101; i++)
			{
				_Common::gotoXY(i, 3); printf("%c", 205);
			}
			Sleep(250);
		}
		_Common::ShowConsoleCursor(true);
		break;
	case 0:
		_Common::SetColor(245);
		_Common::gotoXY(45, 3);
		PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 240; i <= 255; i++)
		{
			_Common::ShowConsoleCursor(false);
			_Common::gotoXY(45, 2);
			_Common::SetColor(i);
			cout << "PLAYER and COM. ARE DRAW!" << endl;
			_Common::gotoXY(19, 2); printf("%c", 201);
			_Common::gotoXY(19, 3); printf("%c", 200);
			_Common::gotoXY(102, 2); printf("%c", 187);
			_Common::gotoXY(102, 3); printf("%c", 188);

			for (int i = 20; i <= 43; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 68; i <= 101; i++)
			{
				_Common::gotoXY(i, 2); printf("%c", 205);
			}
			for (int i = 20; i <= 101; i++)
			{
				_Common::gotoXY(i, 3); printf("%c", 205);
			}
			Sleep(250);
		}
		_Common::ShowConsoleCursor(true);
		break;
	case 2:
		//Tìm bước đi cho BOT
		bot->alphaBeta(!_turn, _b, INT_MIN, INT_MAX, 2);
		int xBot = bot->getX();
		int yBot = bot->getY();
		_b->checkBoard(bot->getX(), bot->getY(), false);           //đánh dấu vị trí BOT đi
		_Common::gotoXY(bot->getX(), bot->getY());
		_Common::SetColor(252);
		cout << "O";
		//Xử lí thắng thua sau khi BOT đánh
		pWhoWin = _b->testBoard(bot->getX(), bot->getY());
		_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
		switch (pWhoWin) {
		case 1: _Game::_countWinB++;
			_Common::gotoXY(105, 10); _Common::SetColor(245); cout << _Game::_countWinB;
			_Common::gotoXY(45, 3);
			_Common::SetColor(245);
			PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
			for (int i = 240; i <= 255; i++)
			{
				_Common::ShowConsoleCursor(false);
				_Common::gotoXY(45, 2);
				_Common::SetColor(i);
				cout << "COM. WINS, PLAYER LOSES!" << endl;
				_Common::gotoXY(19, 2); printf("%c", 201);
				_Common::gotoXY(19, 3); printf("%c", 200);
				_Common::gotoXY(102, 2); printf("%c", 187);
				_Common::gotoXY(102, 3); printf("%c", 188);

				for (int i = 20; i <= 43; i++)
				{
					_Common::gotoXY(i, 2); printf("%c", 205);
				}
				for (int i = 68; i <= 101; i++)
				{
					_Common::gotoXY(i, 2); printf("%c", 205);
				}
				for (int i = 20; i <= 101; i++)
				{
					_Common::gotoXY(i, 3); printf("%c", 205);
				}
				Sleep(250);
			}
			_Common::ShowConsoleCursor(true);
			break;
		case 0:
			_Common::SetColor(245);
			_Common::gotoXY(45, 3);
			_Common::SetColor(245);
			PlaySound(TEXT("cheers.wav"), NULL, SND_FILENAME | SND_ASYNC);
			for (int i = 240; i <= 255; i++)
			{
				_Common::ShowConsoleCursor(false);
				_Common::gotoXY(45, 2);
				_Common::SetColor(i);
				cout << "PLAYER and COM. ARE DRAW!" << endl;
				_Common::gotoXY(19, 2); printf("%c", 201);
				_Common::gotoXY(19, 3); printf("%c", 200);
				_Common::gotoXY(102, 2); printf("%c", 187);
				_Common::gotoXY(102, 3); printf("%c", 188);

				for (int i = 20; i <= 43; i++)
				{
					_Common::gotoXY(i, 2); printf("%c", 205);
				}
				for (int i = 68; i <= 101; i++)
				{
					_Common::gotoXY(i, 2); printf("%c", 205);
				}
				for (int i = 20; i <= 101; i++)
				{
					_Common::gotoXY(i, 3); printf("%c", 205);
				}
				Sleep(250);
			}
			_Common::ShowConsoleCursor(true);
			break;
		}
	}
	_Common::gotoXY(_x, _y);   //Tra ve vi tri hien hanh cua con tro man hinh ban co
	return pWhoWin;
}
/*
HÀM DI CHUYỂN SANG PHẢI
*/
void _Game::moveRight() {
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_x += 4;
		_Common::gotoXY(_x, _y);
	}
}
/*
HÀM DI CHUYỂN SANG TRÁI
*/
void _Game::moveLeft() {
	if (_x > _b->getXAt(0, 0)) {
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}
}
/*
HÀM DI CHUYỂN XUỐNG DƯỚI
*/
void _Game::moveDown() {
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}
/*
HÀM DI CHUYỂN LÊN TRÊN
*/
void _Game::moveUp() {
	if (_y > _b->getYAt(0, 0)) {
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}