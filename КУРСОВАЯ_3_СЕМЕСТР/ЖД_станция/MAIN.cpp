#pragma warning(disable: 4996)
#include "accounts.h"
#include "State.h"
#include "SmartPtr.h"
#include "console_settings.h"
#include "checkings.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>

#define ENTER 13
#define ESC 27
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

using namespace std;

AdminAcc admin_account;
UserAcc user_account;
int state = State::logged_out;

void menu();
void admins_menu();
void users_menu();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"Белорусская железная дорога");
	ConsoleCursorVisible(false, 100);

	setCursorToXY(35, 13);
	cout << "ВАС ПРИВЕТСТВУЮТ БЕЛОРУССКИЕ ЖЕЛЕЗНЫЕ ДОРОГИ!!!";

	Sleep(3000);
	setCursorToXY(5, 25);
	SetConsoleTextAttribute(hStdOut, 8);
	ConsoleCursorVisible(false, 100);
	cout << "Нажмите любую клавишу, чтобы продолжить . . .";
	if (_getch()) {}
	system("cls");

	while (1) {
		switch (state) {
		case State::logged_out: menu(); break;
		case State::admin: admins_menu(); break;
		case State::user: users_menu(); break;
		default: cout << "\nНеизвестное состояние\n";
			exit(-1);
		}
	}
	return 0;
}

void menu() {
	system("cls");

	string actions[] = { "Регистрация (Админ)", "Вход (Админ)", "Регистрация (Пользователь)", "Вход (Пользователь)"};
	int activated = 0;
	ConsoleCursorVisible(false, 100);
	char ch;
	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		setCursorToXY(5, 1);
		cout << "ДЛЯ НАЧАЛА ЗАРЕГИСТРИРУЙТЕСЬ ИЛИ ВОЙДИТЕ В СИСТЕМУ";
		setCursorToXY(5, 5);
		int y = 5;
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = 0; i < size(actions); i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << endl;
			}
			setCursorToXY(5, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		cout << "Enter - подтвердить выбор, Esc - выход";
		ch = _getch();
		if (ch == -32) ch = _getch();
		
		switch (ch) {
		case ESC: 
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "СПАСИБО ЗА ВЫБОР БЕЛОРУССКИХ ЖЕЛЕЗНЫХ ДОРОГ!";
			Sleep(3000);
			SetConsoleTextAttribute(hStdOut, 0); exit(0);
		case ARROW_UP:
			--activated;
			if (activated < 0)
				activated = size(actions) - 1;
			break;
		case ARROW_DOWN:
			++activated;
			if (activated == size(actions))
				activated = 0;
			break;
		case ENTER:
			switch (activated) 
			{
			case 0: admin_account.sign_up() ? state = State::admin : state = State::logged_out; break; //reg as admin
			case 1: admin_account.sign_in() ? state = State::admin : state = State::logged_out; break; //enter as admin
			case 2: user_account.sign_up() ? state = State::user : state = State::logged_out; break; //reg as user
			case 3: user_account.sign_in() ? state = State::user : state = State::logged_out; break; //enter as user
			}
			return;
		default: continue;
		}
	}
}

void admins_menu() {
	system("cls");

	string actions[] = { "Добавить билет",
		"Удалить билет",
		"Просмотреть билеты",
		"Редактировать билет",
		"Поиск билета",
		"Сортировка билетов",
		"Фильтрация билетов",
	//////////////////////////////////
		"Добавить станцию",
		"Удалить станцию",
		"Просмотреть станции",
		"Редактировать станцию",
		"Поиск станции",
		"Сортировка станций",
		"Фильтрация станций"
	};

	int activated = 0;
	ConsoleCursorVisible(false, 100);
	char ch;
	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		setCursorToXY(5, 1);
		cout << "МОДУЛЬ АДМИНИСТРАТОРА. ВЫБЕРИТЕ ДЕЙСТВИЕ";
		setCursorToXY(5, 5);
		int y = 5;
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = 0; i < size(actions) / 2; i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << endl;
			}
			setCursorToXY(5, y += 2);
		}

		y = 5;
		setCursorToXY(40, y);
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = size(actions) / 2; i < size(actions); i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << endl;
			}
			setCursorToXY(40, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		setCursorToXY(5, y + 1);
		cout << "Enter - подтвердить выбор, Esc - выход";
		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch) {
		case ESC:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "СПАСИБО ЗА ВЫБОР БЕЛОРУССКИХ ЖЕЛЕЗНЫХ ДОРОГ!";
			Sleep(3000);
			SetConsoleTextAttribute(hStdOut, 0); exit(0);
		case ARROW_UP:
			--activated;
			if (activated < 0)
				activated = size(actions) - 1;
			break;
		case ARROW_DOWN:
			++activated;
			if (activated == size(actions))
				activated = 0;
			break;
		case ARROW_LEFT:
			if (activated >= (size(actions) / 2) && activated < size(actions))
				activated -= (size(actions) / 2);
			else activated += (size(actions) / 2);
			break;
		case ARROW_RIGHT:
			if (activated >= 0 && activated < (size(actions) / 2))
				activated += (size(actions) / 2);
			else activated -= (size(actions) / 2);
			break;
		case ENTER:
			switch (activated)
			{
			case 0: break; 
			case 1: break; 
			case 2: break; 
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;

			case 7: break;
			case 8: break;
			case 9: break;
			case 10: break;
			case 11: break;
			case 12: break;
			case 13: break;
			}
			break;
		default: continue;
		}
	}
}

void users_menu() {
	system("cls");

	string actions[] = {
		"Просмотреть билеты",
		"Поиск билета",
		"Сортировка билетов",
		"Фильтрация билетов",
		//////////////////////////////////
		"Пополнить баланс",
		"Просмотреть баланс",
		"Купить билет",
		"История покупок"
	};

	int activated = 0;
	ConsoleCursorVisible(false, 100);
	char ch;
	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		setCursorToXY(5, 1);
		cout << "МОДУЛЬ ПОЛЬЗОВАТЕЛЯ. ВЫБЕРИТЕ ДЕЙСТВИЕ";
		setCursorToXY(5, 5);
		int y = 5;
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = 0; i < size(actions) / 2; i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << endl;
			}
			setCursorToXY(5, y += 2);
		}

		y = 5;
		setCursorToXY(40, y);
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = size(actions) / 2; i < size(actions); i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << endl;
			}
			setCursorToXY(40, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		setCursorToXY(5, y + 1);
		cout << "Enter - подтвердить выбор, Esc - выход";
		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch) {
		case ESC:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "СПАСИБО ЗА ВЫБОР БЕЛОРУССКИХ ЖЕЛЕЗНЫХ ДОРОГ!";
			Sleep(3000);
			SetConsoleTextAttribute(hStdOut, 0); exit(0);
		case ARROW_UP:
			--activated;
			if (activated < 0)
				activated = size(actions) - 1;
			break;
		case ARROW_DOWN:
			++activated;
			if (activated == size(actions))
				activated = 0;
			break;
		case ARROW_LEFT:
			if (activated >= (size(actions) / 2) && activated < size(actions))
				activated -= (size(actions) / 2);
			else activated += (size(actions) / 2);
			break;
		case ARROW_RIGHT:
			if (activated >= 0 && activated < (size(actions) / 2))
				activated += (size(actions) / 2);
			else activated -= (size(actions) / 2);
			break;
		case ENTER:
			switch (activated)
			{
			case 0: break;
			case 1: break;
			case 2: break;
			case 3: break;

			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			}
			break;
		default: continue;
		}
	}
}