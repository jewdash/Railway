#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

extern HANDLE hStdOut;
void setCursorToXY(short x, short y);
void ConsoleCursorVisible(bool, short);