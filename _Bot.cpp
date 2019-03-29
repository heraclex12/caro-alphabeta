#include "_Bot.h"
#include <climits>
int _Bot::getX() {
	return _x;
}
int _Bot::getY() {
	return _y;
}
_Bot::_Bot() {
	_x = 0;
	_y = 0;
	root = new _Point();
}
/*
HÀM TẠO BƯỚC ĐI NGẪU NHIÊN CHO MÁY
Đầu vào: Bàn cờ hiện tại
Đầu ra: Không có
*/
void _Bot::moveRandom(_Board* b) {
	srand(time(NULL));
	int i = rand() % (b->getSize() - 3) + 1;
	int j = rand() % (b->getSize() - 3) + 1;
	if (b->getCheckAt(i, j) == 0) {
		b->makeMove(i, j, false);
		_Common::gotoXY(b->getXAt(i, j), b->getYAt(i, j));
		_Common::SetColor(252);
		cout << "O";
	}
}
/*
HÀM THUẬT TOÁN CẮT TỈA ALPHA-BETA
Đầu vào: Lượt chơi, bảng trạng thái hiện tại, giá trị điểm alpha, giá trị điểm beta, số bước đi dự đoán
Đầu ra: Điểm tốt nhất của bước đi hiện tại
*/
int _Bot::alphaBeta(bool player, _Board *b, int alpha, int beta, int depth) {
	int result = b->testBoard(root->getX(), root->getY());
	if (depth == 0 || result != 2) {         //nếu hết bước đi dự đoán hoặc trận đấu có người thắng hoặc hòa
		return b->evaluate(root);         //tính điểm trên bàn cờ
	}
	if (player == true) //PLAYER = MAX
	{
		return maxValue(player, b, alpha, beta, depth);
	}
	else //BOT = MIN
	{
		return minValue(player, b, alpha, beta, depth);
	}
}
/*
HÀM TÌM BƯỚC ĐI TỐT NHẤT CHO MAX (NGƯỜI CHƠI)
Đầu vào: Lượt chơi (max == true), bảng trạng thái hiện tại, giá trị điểm alpha, giá trị điểm beta, số bước đi dự đoán
Đầu ra: Điểm tốt nhất của người chơi MAX
*/
int _Bot::maxValue(bool turn, _Board *b, int alpha, int beta, int depth) {
	int size = b->getSize();
	//Vòng lặp mô phòng các bước đi
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (b->getCheckAt(i, j) == 0) {
				b->makeMove(i, j, turn);                    //đánh dấu bước đi của MAX
				int score = alphaBeta(!turn, b, alpha, beta, depth - 1);            //dự đoán lượt đi tiếp theo của MIN
				b->unMove(i, j);                            //bỏ đánh dấu bước đi MAX
				if (score > alpha) {                        //Nếu bước đi tốt hơn
					alpha = score;
				}
				if (alpha >= (-1)*beta) {        //cắt tỉa
					return alpha;
				}
			}
		}
	}
	return alpha;
}
/*
HÀM TÌM BƯỚC ĐI TỐT NHẤT CHO MIN (MÁY)
Đầu vào: Lượt chơi (min == false), bảng trạng thái hiện tại, giá trị điểm alpha, giá trị điểm beta, số bước đi dự đoán
Đầu ra: Điểm tốt nhất của máy MIN
*/
int _Bot::minValue(bool turn, _Board *b, int alpha, int beta, int depth) {
	int size = b->getSize();
	//Vòng lặp mô phòng các bước đi
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (b->getCheckAt(i, j) == 0) {
				b->makeMove(i, j, turn);                 //đánh dấu bước đi của MIN
				root->setX(i);
				root->setY(j);
				int score = (-1)*alphaBeta(!turn, b, alpha, beta, depth - 1);      //dự đoán lượt đi tiếp theo của MAX
				b->unMove(i, j);                         //bỏ đánh dấu bước đi MIN
				if (score < beta) {                      //Nếu bước đi tốt hơn thì lưu lại vị trí
					beta = score;
					_x = b->getXAt(i,j);
					_y = b->getYAt(i,j);
				}
				if ((-1)*alpha >= beta) {           //cắt tỉa
					return (-1)*beta;
				}
			}
		}
	}
	return (-1)*beta;
}