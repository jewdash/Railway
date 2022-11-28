#include "accounts.h"
#include "State.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"
#include "console_settings.h"
#include "checkings.h"
#include "station.h"
#include "ticket.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>

#define ENTER 13
#define BACKSPACE 8
#define ESC 27
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

using namespace std;

AdminAcc admin_account;
UserAcc user_account;
int state = State::logged_out;
extern vector<Station> station_vec;
extern vector<Ticket> ticket_vec;

void menu();
void admins_menu();
void users_menu();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"Белорусская железная дорога");
	srand(time(NULL));
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
		/*system("cls");*/
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
				cout << actions[i] << "   " << endl;
			}
			setCursorToXY(5, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		cout << "Enter - подтвердить выбор, Esc - выход из программы";
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
			case 0: {
				admin_account.sign_up();
				string confirm;
				string admin_key;
				try {
					ifstream fin;
					fin.open("admin_key.txt", ios::in);
					if (!fin) throw "Ошибка открытия файла";

					fin >> admin_key;
					fin.close();

					SetConsoleTextAttribute(hStdOut, 7);
					cout << "\n Введите ключ администратора: ";
					SetConsoleTextAttribute(hStdOut, 14);
					ConsoleCursorVisible(true, 100);
					getline(cin, confirm);
					ConsoleCursorVisible(false, 100);

					if (confirm != admin_key) throw "Неверный ключ администратора";

					if (admin_account.writeInfo()) {
						SetConsoleTextAttribute(hStdOut, 10);
						cout << endl << endl;
						cout << " ВЫ УСПЕШНО ЗАРЕГИСТРИРОВАЛИСЬ.\n";
						cout << " Данные о вашем аккаунте теперь хранятся в файле\n При повторной регистрации данные будут утеряны и на их месте будут записаны новые\n";
						SetConsoleTextAttribute(hStdOut, 2);
						cout << endl;
						Sleep(2000);
						cout << " Нажмите на любую клавишу если вам всё понятно и желаете продолжить . . .";
						if (_getch()) {}
						state = State::admin;
					}
					else state = State::logged_out;
				}
				catch (const char* exc) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Произошла ошибка: " << exc << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
					if (_getch()) {}
				}
				break; //reg as admin
			}
			case 1: {
				string confirm;
				string admin_key;
				try {
					AdminAcc acc;
					if (!admin_account.readInfo()) throw "Ошибка считывания из файла";
					acc.sign_in();

					ifstream fin;
					fin.open("admin_key.txt", ios::in);
					if (!fin) throw "Ошибка открытия файла";

					fin >> admin_key;
					fin.close();

					SetConsoleTextAttribute(hStdOut, 7);
					cout << "\n Введите ключ администратора: ";
					SetConsoleTextAttribute(hStdOut, 14);
					ConsoleCursorVisible(true, 100);
					getline(cin, confirm);
					ConsoleCursorVisible(false, 100);

					if (confirm != admin_key) throw "Неверный ключ администратора";

					if (!admin_account.loginCorrect(acc)) throw "Неверный логин или пароль";

					SetConsoleTextAttribute(hStdOut, 10);
					cout << endl << endl;
					cout << " ВЫ УСПЕШНО ВОШЛИ В АККАУНТ.\n";
					cout << " Для выхода из аккаунта нажмите Backspace\n Для смены данных аккаунта зарегистрируйте новый. При этом старые данные будут утеряны\n";
					SetConsoleTextAttribute(hStdOut, 2);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и желаете продолжить . . .";
					if (_getch()) {}
					state = State::admin;
				}
				catch (const char* exc) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Произошла ошибка: " << exc << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
					if (_getch()) {}
				}
				break; //enter as admin
			}
			case 2: {
				user_account.sign_up();
				if (user_account.writeInfo()) {
					SetConsoleTextAttribute(hStdOut, 10);
					cout << endl << endl;
					cout << " ВЫ УСПЕШНО ЗАРЕГИСТРИРОВАЛИСЬ.\n";
					cout << " Данные о вашем аккаунте теперь хранятся в файле\n При повторной регистрации данные будут утеряны и на их месте будут записаны новые\n";
					SetConsoleTextAttribute(hStdOut, 2);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и желаете продолжить . . .";
					if (_getch()) {}
					state = State::user;
				}
				else state = State::logged_out;
				break; //reg as user
			}
			case 3: {
				try {
					UserAcc acc;
					if (!user_account.readInfo()) throw "Ошибка считывания из файла";
					acc.sign_in();

					if (!user_account.loginCorrect(acc)) throw "Неверный логин или пароль";

					SetConsoleTextAttribute(hStdOut, 10);
					cout << endl << endl;
					cout << " ВЫ УСПЕШНО ВОШЛИ В АККАУНТ.\n";
					cout << " Для выхода из аккаунта нажмите Backspace\n Для смены данных аккаунта зарегистрируйте новый. При этом старые данные будут утеряны\n";
					SetConsoleTextAttribute(hStdOut, 2);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и желаете продолжить . . .";
					if (_getch()) {}
					state = State::user;
				}
				catch (const char* exc) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Произошла ошибка: " << exc << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
					if (_getch()) {}
				}
				break; //enter as user
			}
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
		/*system("cls");*/
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
				cout << actions[i] << "     " << endl;
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
				cout << actions[i] << "    " << endl;
			}
			setCursorToXY(40, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		setCursorToXY(5, y + 1);
		cout << "Enter - подтвердить выбор, Esc - выход из программы, Backspace - выход из аккаунта";
		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch) {
		case BACKSPACE:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "ВЫ ВЫШЛИ ИЗ АККАУНТА! СПАСИБО ЗА РАБОТУ!";
			Sleep(3000);
			setCursorToXY(5, 25);
			SetConsoleTextAttribute(hStdOut, 8);
			ConsoleCursorVisible(false, 100);
			cout << "Нажмите любую клавишу, чтобы продолжить . . .";
			if (_getch()) {}
			state = State::logged_out;
			system("cls");
			return;
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
			case 0: admin_account.create_ticket(); break;		//добавить билет
			case 1: admin_account.delete_ticket(); break;		//удалить билеты
			case 2: admin_account.display_tickets(); break;		//просмотреть билеты
			case 3: admin_account.edit_ticket(); break;			//редактировать билет
			case 4: admin_account.find_ticket(); break;			//поиск билетов
			case 5: admin_account.sort_tickets(); break;		//сортировка билетов
			case 6: admin_account.filter_tickets(); break;		//фильтрация билетов

			case 7: admin_account.add_station(); break;			//добавить станцию
			case 8: admin_account.remove_station(); break;		//удалить станцию
			case 9: admin_account.display_stations(); break;	//просмотреть станцию
			case 10: admin_account.edit_station(); break;		//редактировать станцию
			case 11: admin_account.find_station(); break;		//поиск станции
			case 12: admin_account.sort_stations(); break;		//сортировка станций
			case 13: admin_account.filter_stations(); break;	//фильтрация станций
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
		/*system("cls");*/
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
				cout << actions[i] << "    " << endl;
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
				cout << actions[i] << "    " << endl;
			}
			setCursorToXY(40, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		setCursorToXY(5, y + 1);
		cout << "Enter - подтвердить выбор, Esc - выход из программы, Backspace - выход из аккаунта";
		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch) {
		case BACKSPACE:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "ВЫ ВЫШЛИ ИЗ АККАУНТА! СПАСИБО ЗА РАБОТУ!";
			Sleep(3000);
			setCursorToXY(5, 25);
			SetConsoleTextAttribute(hStdOut, 8);
			ConsoleCursorVisible(false, 100);
			cout << "Нажмите любую клавишу, чтобы продолжить . . .";
			if (_getch()) {}
			state = State::logged_out;
			system("cls");
			return;
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
			case 0: user_account.display_tickets(); break;	//Просмотреть билеты
			case 1: user_account.find_ticket(); break;		//Найти билет
			case 2: user_account.sort_tickets(); break;		//Сортировать билеты
			case 3: user_account.filter_tickets(); break;	//Фильтровать билеты

			case 4: user_account.fill_balance(); break;		//Пополнить баланс
			case 5: user_account.see_balance(); break;		//Просмотреть баланс
			case 6: user_account.buy_ticket(); break;		//Купить билет
			case 7: user_account.check_history(); break;	//История покупок
			}
			break;
		default: continue;
		}
	}
}
