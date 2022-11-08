#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

HANDLE hStdOut;
void setCursorToXY(short, short);
void ConsoleCursorVisible(bool, short);