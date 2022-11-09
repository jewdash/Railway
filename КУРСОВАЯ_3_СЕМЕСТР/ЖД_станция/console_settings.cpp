#include "console_settings.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setCursorToXY(short x, short y) {
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // �������� ��������� �������
	structCursorInfo.dwSize = size; // �������� ������ �������
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}