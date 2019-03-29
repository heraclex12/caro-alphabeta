#include "_Common.h"
/*
HÀM CỐ ĐỊNH KÍCH THƯỚC CỬA SỔ CONSOLE
*/
void _Common::fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
/*
HÀM DỊCH CHUYỂN CON TRỎ CHUỘT TỚI VỊ TRÍ CHỈ ĐỊNH
-Đầu vào: Vị trí pX trên trục Ox, vị trí pY trên trục Oy
-Đầu ra: Không có
*/
void _Common::gotoXY(int pX, int pY) {
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*
HÀM THAY ĐỔI MÀU THUỘC TÍNH
-Đầu vào: Mã mầu cần đổi
-Đầu ra: Không có
*/
void _Common::SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/*
HÀM BẬT/TẮT HIỂN THỊ DẤU NHÁY CHUỘT TRÊN MÀN HÌNH (TRUE = BẬT, FALSE = TẮT)
*/
void _Common::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}