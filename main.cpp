#include "_Board.h"
#include "_Common.h"
#include "_Game.h"
#include "_Point.h"
int _Game::_countTurn = 0;
int _Game::_countWinA1 = 0;
int _Game::_countWinA2 = 0;
int _Game::_countWinB = 0;
int main() {
	SetConsoleCP(437);
	_Common::SetColor(245);
	SetConsoleOutputCP(437);
	_Common::fixConsoleWindow();
	SetConsoleTitle("Game: CARO - NHOM 22");
	_Game g(10, 40, 5);
	g.startGame();
	return 0;
}