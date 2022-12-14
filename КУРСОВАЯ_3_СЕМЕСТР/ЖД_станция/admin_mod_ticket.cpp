#include "accounts.h"
#include "console_settings.h"
#include "checkings.h"
#include <queue>
#include "ticket.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"

vector<Ticket> ticket_vec;
DateTime today = {14, 12, 2022, 23, 0};
using namespace std;
using namespace additional_funcs;

void AdminAcc::create_ticket() {
	vector<Station> station_vec;
	Station st;
	Ticket tk;
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " ДОБАВЛЕНИЕ ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << endl;
	station_vec.clear();
	if (!st.readStation(station_vec)) return;
	
	tk.id_ticket = (1000 + rand() % 10000) - 1000;

	while (1) {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " Введите название станции ОТПРАВЛЕНИЯ: ";
		ConsoleCursorVisible(true, 100);
		SetConsoleTextAttribute(hStdOut, 14);
		rewind(stdin); getline(cin, tk.dep_station.name_station);
		ConsoleCursorVisible(false, 100);
		if (tk.dep_station.name_station.empty()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;

	int i;
	bool found_1 = false;
	for (i = 0; i < station_vec.size(); i++) {
		if (station_vec[i].name_station == tk.dep_station.name_station) {
			station_vec[i].id_station = tk.dep_station.id_station;
			station_vec[i].dep.code_department = tk.dep_station.dep.code_department;
			station_vec[i].dep.title = tk.dep_station.dep.title;
			station_vec[i].region.code_region = tk.dep_station.region.code_region;
			station_vec[i].region.region = tk.dep_station.region.region;
			station_vec[i].region.district = tk.dep_station.region.district;
			found_1 = true;
			break;
		}
	}

	if (!found_1) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Станции с таким названием не существует в базе данных";
		cout << endl << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}

	while (1) {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " Введите название станции ПРИБЫТИЯ: ";
		ConsoleCursorVisible(true, 100);
		SetConsoleTextAttribute(hStdOut, 14);
		rewind(stdin); getline(cin, tk.arr_station.name_station);
		ConsoleCursorVisible(false, 100);
		if (tk.arr_station.name_station.empty()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;

	int j;
	bool found_2 = false;
	for (j = 0; j < station_vec.size(); j++) {
		if (station_vec[j].name_station == tk.arr_station.name_station) {
			station_vec[j].id_station = tk.arr_station.id_station;
			station_vec[j].dep.code_department = tk.arr_station.dep.code_department;
			station_vec[j].dep.title = tk.arr_station.dep.title;
			station_vec[j].region.code_region = tk.arr_station.region.code_region;
			station_vec[j].region.region = tk.arr_station.region.region;
			station_vec[j].region.district = tk.arr_station.region.district;
			found_2 = true;
			break;
		}
	}

	if (!found_2) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Станции с таким названием не существует в базе данных";
		cout << endl << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}

	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 15);
	while (1) {
		cout << "Введите дату ОТПРАВЛЕНИЯ: " << endl;
		cin >> tk.dep_dt;
		cout << endl << endl;
		if (tk.dep_dt < today) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << "Введено прошедшее значение. Повторите ввод.";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 15);
	while (1) {
		cout << "Введите дату ПРИБЫТИЯ: " << endl;
		cin >> tk.arr_dt;
		cout << endl << endl;
		if ((tk.arr_dt < tk.dep_dt) || (tk.arr_dt == tk.dep_dt)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << "Введено неверное значение. Повторите ввод.";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	cout << endl << endl;
	while (1) {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << "Установите количество билетов в продаже: ";
		cin >> tk.amount;
		if (cin.fail() || tk.amount < 0) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	cout << endl << endl;
	while (1) {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << "Установите цену одного билета: ";
		cin >> tk.price;
		if (cin.fail() || tk.price < 0) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	if (tk.writeTicket()) {
		SetConsoleTextAttribute(hStdOut, 10);
		cout << endl << endl << " Данные успешно записаны в файл." << endl;
		SetConsoleTextAttribute(hStdOut, 2);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
}

void AdminAcc::delete_ticket() {
	Ticket tk;
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " УДАЛЕНИЕ ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << endl;
	ticket_vec.clear();
	if (!tk.readTicket(ticket_vec)) return;

	int deleting;

	while (1) {
		cout << " Введите ID удаляемой станции: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		cin >> deleting;
		ConsoleCursorVisible(false, 100);
		if (cin.fail() || deleting < 0) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	int i;
	bool found = false;
	for (i = 0; i < ticket_vec.size(); i++) {
		if (ticket_vec[i].id_ticket == deleting) {
			found = true;
			break;
		}
	}

	if (!found) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Билета с таким ID не существует в базе данных";
		cout << endl << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
	else {
		ofstream fout("tickets.txt");
		if (!fout) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка при открытии файла";
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 4);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		else {
			ticket_vec.erase(ticket_vec.begin() + i);
			for (int k = 0; k < ticket_vec.size(); k++) {
				fout << ticket_vec[k].id_ticket << "\t"
					<< ticket_vec[k].dep_dt.dd << "\t"
					<< ticket_vec[k].dep_dt.mm << "\t"
					<< ticket_vec[k].dep_dt.yyyy << "\t"
					<< ticket_vec[k].dep_dt.hh << "\t"
					<< ticket_vec[k].dep_dt.mt << "\t"
					<< ticket_vec[k].dep_station.name_station << "\t"
					<< ticket_vec[k].arr_dt.dd << "\t"
					<< ticket_vec[k].arr_dt.mm << "\t"
					<< ticket_vec[k].arr_dt.yyyy << "\t"
					<< ticket_vec[k].arr_dt.hh << "\t"
					<< ticket_vec[k].arr_dt.mt << "\t"
					<< ticket_vec[k].arr_station.name_station << "\t"
					<< ticket_vec[k].amount << "\t"
					<< ticket_vec[k].price << "\t" << endl;
			}
			fout.close();
		}

		SetConsoleTextAttribute(hStdOut, 10);
		ConsoleCursorVisible(false, 100);
		cout << endl << endl << " База данных переформирована" << endl;
		SetConsoleTextAttribute(hStdOut, 2);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
}

void AdminAcc::edit_ticket() {
	vector<Station> station_vec;
	Station st;
	Ticket tk;
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " РЕДАКТИРОВАНИЕ ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << " (Необходимо заново ввести все данные)" << endl << endl;
	station_vec.clear();
	if (!st.readStation(station_vec)) return;
	ticket_vec.clear();
	if (!tk.readTicket(ticket_vec)) return;

	int editing;

	while (1) {
		cout << " Введите ID редактируемой станции: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		cin >> editing;
		ConsoleCursorVisible(false, 100);
		if (cin.fail() || editing < 0) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	cout << endl << endl;
	int i;
	bool found = false;
	for (i = 0; i < ticket_vec.size(); i++) {
		if (ticket_vec[i].id_ticket == editing) {
			found = true;
			break;
		}
	}

	if (!found) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Билета с таким ID не существует в базе данных";
		cout << endl << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
	else {
		ofstream fout("tickets.txt");
		if (!fout) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка при открытии файла";
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 4);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		else {
			for (int k = 0; k < ticket_vec.size(); k++) {
				if (k != i) {
					fout << ticket_vec[k].id_ticket << "\t"
						<< ticket_vec[k].dep_dt.dd << "\t"
						<< ticket_vec[k].dep_dt.mm << "\t"
						<< ticket_vec[k].dep_dt.yyyy << "\t"
						<< ticket_vec[k].dep_dt.hh << "\t"
						<< ticket_vec[k].dep_dt.mt << "\t"
						/*<< dep_station.id_station << "\t" */
						<< ticket_vec[k].dep_station.name_station << "\t"
						/*<< dep_station.dep.code_department << "\t"
						<< dep_station.dep.title << "\t"
						<< dep_station.region.code_region << "\t"
						<< dep_station.region.region << "\t"
						<< dep_station.region.district << "\t"*/
						<< ticket_vec[k].arr_dt.dd << "\t"
						<< ticket_vec[k].arr_dt.mm << "\t"
						<< ticket_vec[k].arr_dt.yyyy << "\t"
						<< ticket_vec[k].arr_dt.hh << "\t"
						<< ticket_vec[k].arr_dt.mt << "\t"
						/*<< arr_station.id_station << "\t"*/
						<< ticket_vec[k].arr_station.name_station << "\t"
						/*<< arr_station.dep.code_department << "\t"
						<< arr_station.dep.title << "\t"
						<< arr_station.region.code_region << "\t"
						<< arr_station.region.region << "\t"
						<< arr_station.region.district << "\t"*/
						<< ticket_vec[k].amount << "\t"
						<< ticket_vec[k].price << "\t" << endl;
				}
				else {
					tk.id_ticket = ticket_vec[k].id_ticket;
					ConsoleCursorVisible(false, 100);
					SetConsoleTextAttribute(hStdOut, 15);

					while (1) {
						bool compare = false;
						while (1) {
							SetConsoleTextAttribute(hStdOut, 15);
							cout << " Введите название станции ОТПРАВЛЕНИЯ: ";
							ConsoleCursorVisible(true, 100);
							SetConsoleTextAttribute(hStdOut, 14);
							rewind(stdin); getline(cin, st.name_station);
							ConsoleCursorVisible(false, 100);
							if (st.name_station.empty()) {
								SetConsoleTextAttribute(hStdOut, 12);
								cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
								cout << endl << endl;
								continue;
							}
							else break;
						}
						cout << endl << endl;

						for (int i = 0; i < station_vec.size(); i++) {
							if (getUppercaseString(st.name_station) == getUppercaseString(station_vec[i].name_station)) {
								compare = true;
								ticket_vec[k].dep_station.name_station = st.name_station;
								ticket_vec[k].dep_station.id_station = st.id_station;
								ticket_vec[k].dep_station.dep.code_department = st.dep.code_department;
								ticket_vec[k].dep_station.dep.title = st.dep.title;
								ticket_vec[k].dep_station.region.code_region = st.region.code_region;
								ticket_vec[k].dep_station.region.region = st.region.region;
								ticket_vec[k].dep_station.region.district = st.region.district;
								break;
							}
						}

						if (!compare) {
							SetConsoleTextAttribute(hStdOut, 12);
							cout << endl << endl << " Введен несуществующее название станции. Повторите поптыку...";
							cout << endl << endl;
							continue;
						}
						else break;
					}
					cout << endl << endl;

					while (1) {
						bool compare = false;
						while (1) {
							SetConsoleTextAttribute(hStdOut, 15);
							cout << " Введите название станции ПРИБЫТИЯ: ";
							ConsoleCursorVisible(true, 100);
							SetConsoleTextAttribute(hStdOut, 14);
							rewind(stdin); getline(cin, st.name_station);
							ConsoleCursorVisible(false, 100);
							if (st.name_station.empty()) {
								SetConsoleTextAttribute(hStdOut, 12);
								cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
								cout << endl << endl;
								continue;
							}
							else break;
						}
						cout << endl << endl;

						for (int i = 0; i < station_vec.size(); i++) {
							if (getUppercaseString(st.name_station) == getUppercaseString(station_vec[i].name_station)) {
								compare = true;
								ticket_vec[k].arr_station.name_station = st.name_station;
								ticket_vec[k].arr_station.id_station = st.id_station;
								ticket_vec[k].arr_station.dep.code_department = st.dep.code_department;
								ticket_vec[k].arr_station.dep.title = st.dep.title;
								ticket_vec[k].arr_station.region.code_region = st.region.code_region;
								ticket_vec[k].arr_station.region.region = st.region.region;
								ticket_vec[k].arr_station.region.district = st.region.district;
								break;
							}
						}

						if (!compare) {
							SetConsoleTextAttribute(hStdOut, 12);
							cout << endl << endl << " Введен несуществующее название станции. Повторите поптыку...";
							cout << endl << endl;
							continue;
						}
						else break;
					}
					cout << endl << endl;

					SetConsoleTextAttribute(hStdOut, 15);
					while (1) {
						cout << "Введите дату ОТПРАВЛЕНИЯ: " << endl;
						cin >> ticket_vec[k].dep_dt;
						cout << endl << endl;
						if (ticket_vec[k].dep_dt < today) {
							SetConsoleTextAttribute(hStdOut, 12);
							cout << "Введено прошедшее значение. Повторите ввод.";
							cout << endl << endl;
							continue;
						}
						else break;
					}

					cout << endl << endl;
					SetConsoleTextAttribute(hStdOut, 15);
					while (1) {
						cout << "Введите дату ПРИБЫТИЯ: " << endl;
						cin >> ticket_vec[k].arr_dt;
						cout << endl << endl;
						if ((ticket_vec[k].arr_dt < ticket_vec[k].dep_dt) || (ticket_vec[k].arr_dt == ticket_vec[k].dep_dt)) {
							SetConsoleTextAttribute(hStdOut, 12);
							cout << "Введено неверное значение. Повторите ввод.";
							cout << endl << endl;
							continue;
						}
						else break;
					}

					cout << endl << endl;

					while (1) {
						SetConsoleTextAttribute(hStdOut, 15);
						cout << " Введите количество билетов на продаже: ";
						ConsoleCursorVisible(true, 100);
						SetConsoleTextAttribute(hStdOut, 14);
						cin >> ticket_vec[k].amount;
						ConsoleCursorVisible(false, 100);

						if (cin.fail() || ticket_vec[k].amount < 0) {
							SetConsoleTextAttribute(hStdOut, 12);
							cout << endl << endl << " Введено некорректное значение. Повторите поптыку...";
							cout << endl << endl;
							continue;
						}
						else break;
					}
					cout << endl << endl;

					while (1) {
						SetConsoleTextAttribute(hStdOut, 15);
						cout << " Введите стоимость билета: ";
						ConsoleCursorVisible(true, 100);
						SetConsoleTextAttribute(hStdOut, 14);
						cin >> ticket_vec[k].price;
						ConsoleCursorVisible(false, 100);

						if (cin.fail() || ticket_vec[k].price < 0) {
							SetConsoleTextAttribute(hStdOut, 12);
							cout << endl << endl << " Введено некорректное значение. Повторите поптыку...";
							cout << endl << endl;
							continue;
						}
						else break;
					}
					cout << endl << endl;

					fout << ticket_vec[k].id_ticket << "\t"
						<< ticket_vec[k].dep_dt.dd << "\t"
						<< ticket_vec[k].dep_dt.mm << "\t"
						<< ticket_vec[k].dep_dt.yyyy << "\t"
						<< ticket_vec[k].dep_dt.hh << "\t"
						<< ticket_vec[k].dep_dt.mt << "\t"
						/*<< dep_station.id_station << "\t" */
						<< ticket_vec[k].dep_station.name_station << "\t"
						/*<< dep_station.dep.code_department << "\t"
						<< dep_station.dep.title << "\t"
						<< dep_station.region.code_region << "\t"
						<< dep_station.region.region << "\t"
						<< dep_station.region.district << "\t"*/
						<< ticket_vec[k].arr_dt.dd << "\t"
						<< ticket_vec[k].arr_dt.mm << "\t"
						<< ticket_vec[k].arr_dt.yyyy << "\t"
						<< ticket_vec[k].arr_dt.hh << "\t"
						<< ticket_vec[k].arr_dt.mt << "\t"
						/*<< arr_station.id_station << "\t"*/
						<< ticket_vec[k].arr_station.name_station << "\t"
						/*<< arr_station.dep.code_department << "\t"
						<< arr_station.dep.title << "\t"
						<< arr_station.region.code_region << "\t"
						<< arr_station.region.region << "\t"
						<< arr_station.region.district << "\t"*/
						<< ticket_vec[k].amount << "\t"
						<< ticket_vec[k].price << "\t" << endl;
				}
			}
			fout.close();
		}

		SetConsoleTextAttribute(hStdOut, 10);
		cout << endl << endl << " База данных переформирована" << endl;
		SetConsoleTextAttribute(hStdOut, 2);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
}

void AdminAcc::display_tickets() {
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	system("cls");
	cout << endl << " СПИСОК ЖЕЛЕЗНОДОРОЖНЫХ БИЛЕТОВ " << endl << endl;
	Ticket tk;
	ticket_vec.clear();
	if (!tk.readTicket(ticket_vec)) return;

	cout.fill('-');
	cout << "+"
		<< setw(7) << "+"
		<< setw(33) << "+"
		<< setw(24) << "+"
		<< setw(33) << "+"
		<< setw(24) << "+"
		<< setw(7) << "+"
		<< setw(7) << "+" << endl;

	cout.fill(' ');
	cout << "|"
		<< setw(4) << "ID" << setw(3) << "|"
		<< setw(22) << "Ст. отправл." << setw(11) << "|"
		<< setw(19) << "Дата отправл." << setw(5) << "|"
		<< setw(22) << "Ст. прибытия" << setw(11) << "|"
		<< setw(19) << "Дата прибытия" << setw(5) << "|"
		<< setw(5) << "Кол." << setw(2) << "|"
		<< setw(5) << "Цена" << setw(2) << "|" << endl;

	cout.fill('-');
	cout << "+"
		<< setw(7) << "+"
		<< setw(33) << "+"
		<< setw(24) << "+"
		<< setw(33) << "+"
		<< setw(24) << "+"
		<< setw(7) << "+"
		<< setw(7) << "+" << endl;

	for (int i = 0; i < ticket_vec.size(); i++) {
		cout.fill(' ');

		cout << "|";
		SetConsoleTextAttribute(hStdOut, 10);
		cout << setw(5) << ticket_vec[i].id_ticket;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(30) << getUppercaseString(ticket_vec[i].dep_station.name_station);
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(19) << ticket_vec[i].dep_dt;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(6) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(30) << getUppercaseString(ticket_vec[i].arr_station.name_station);
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(19) << ticket_vec[i].arr_dt;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(6) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(5) << ticket_vec[i].amount;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(5) << ticket_vec[i].price;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|" << endl;

		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(7) << "+"
			<< setw(7) << "+" << endl;

		Sleep(100);
	}

	cout.fill(' ');
	ConsoleCursorVisible(false, 100);
	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 8);
	Sleep(2000);
	cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
	if (_getch()) {}
	system("cls");
	return;
}

void AdminAcc::sort_tickets() {
	Ticket tk;
	char request;

	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		ConsoleCursorVisible(false, 100);
		ticket_vec.clear();
		if (!tk.readTicket(ticket_vec)) return;

		cout << endl << " СОРТИРОВКА ЖЕЛЕЗНОДОРОЖНЫХ БИЛЕТОВ" << endl << endl;
		SetConsoleTextAttribute(hStdOut, 11);
		cout << "\t\tВЫБЕРИТЕ ПАРАМЕТР, ПО КОТОРОМУ НЕОБХОДИМО СОРТИРОВАТЬ ДАННЫЕ: " << endl << endl;
		SetConsoleTextAttribute(hStdOut, 3);
		cout << "\t\t[1] ~ По ДАТЕ ОТПРАВЛЕНИЯ, отображённой на билете\n";
		cout << "\t\t[2] ~ По СТАНЦИИ ПРИБЫТИЯ, отображённой на билете\n";
		cout << "\t\t[3] ~ По ИДЕНТИФИКАЦИОННОМУ НОМЕРУ железнодорожного билета\n";
		cout << "\t\t[Escape] ~ Для выхода в главное меню\n";

		cout << endl << endl;

		request = _getch();
		switch (request) {
		case 49: case 97: {
			priority_queue<Ticket, vector<Ticket>, CompareDate> ticket_pqueue;

			for (int i = 0; i < ticket_vec.size(); i++) {
				ticket_pqueue.push(ticket_vec[i]);
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(22) << "Ст. отправл." << setw(11) << "|"
				<< setw(19) << "Дата отправл." << setw(5) << "|"
				<< setw(22) << "Ст. прибытия" << setw(11) << "|"
				<< setw(19) << "Дата прибытия" << setw(5) << "|"
				<< setw(5) << "Кол." << setw(2) << "|"
				<< setw(5) << "Цена" << setw(2) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			while (!ticket_pqueue.empty()) {
				cout.fill(' ');

				cout << "|";
				SetConsoleTextAttribute(hStdOut, 10);
				cout << setw(5) << ticket_pqueue.top().id_ticket;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(30) << getUppercaseString(ticket_pqueue.top().dep_station.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout.fill('0');
				cout << setw(2) << ticket_pqueue.top().dep_dt.dd << "."
					<< setw(2) << ticket_pqueue.top().dep_dt.mm << "."
					<< setw(4) << ticket_pqueue.top().dep_dt.yyyy;
				cout.fill(' '); cout << "   ";
				cout.fill('0');
				cout << setw(2) << ticket_pqueue.top().dep_dt.hh << ":"
					<< setw(2) << ticket_pqueue.top().dep_dt.mt;
				cout.fill(' ');
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(6) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(30) << getUppercaseString(ticket_pqueue.top().arr_station.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout.fill('0');
				cout << setw(2) << ticket_pqueue.top().arr_dt.dd << "."
					<< setw(2) << ticket_pqueue.top().arr_dt.mm << "."
					<< setw(4) << ticket_pqueue.top().arr_dt.yyyy;
				cout.fill(' '); cout << "   ";
				cout.fill('0');
				cout << setw(2) << ticket_pqueue.top().arr_dt.hh << ":"
					<< setw(2) << ticket_pqueue.top().arr_dt.mt;
				cout.fill(' ');
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(6) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(5) << ticket_pqueue.top().amount;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(5) << ticket_pqueue.top().price;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|" << endl;

				cout.fill('-');
				cout << "+"
					<< setw(7) << "+"
					<< setw(33) << "+"
					<< setw(24) << "+"
					<< setw(33) << "+"
					<< setw(24) << "+"
					<< setw(7) << "+"
					<< setw(7) << "+" << endl;

				Sleep(100);
				ticket_pqueue.pop();
			}

			cout.fill(' ');
			ConsoleCursorVisible(false, 100);
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 8);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		case 50: case 98: {
			map<string, Ticket> sorted;

			for (int i = 0; i < ticket_vec.size(); i++) {
				pair<string, Ticket> pr = make_pair(ticket_vec[i].arr_station.name_station, ticket_vec[i]);
				sorted.insert(pr);
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(22) << "Ст. отправл." << setw(11) << "|"
				<< setw(19) << "Дата отправл." << setw(5) << "|"
				<< setw(22) << "Ст. прибытия" << setw(11) << "|"
				<< setw(19) << "Дата прибытия" << setw(5) << "|"
				<< setw(5) << "Кол." << setw(2) << "|"
				<< setw(5) << "Цена" << setw(2) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			for (auto iter : sorted) {
				cout.fill(' ');

				cout << "|";
				SetConsoleTextAttribute(hStdOut, 10);
				cout << setw(5) << iter.second.id_ticket;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(30) << getUppercaseString(iter.second.dep_station.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(19) << iter.second.dep_dt;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(6) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(30) << getUppercaseString(iter.first);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(19) << iter.second.arr_dt;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(6) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(5) << iter.second.amount;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(5) << iter.second.price;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|" << endl;

				cout.fill('-');
				cout << "+"
					<< setw(7) << "+"
					<< setw(33) << "+"
					<< setw(24) << "+"
					<< setw(33) << "+"
					<< setw(24) << "+"
					<< setw(7) << "+"
					<< setw(7) << "+" << endl;

				Sleep(100);
			}

			cout.fill(' ');
			ConsoleCursorVisible(false, 100);
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 8);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		case 51: case 99: {
			map<int, Ticket> sorted;

			for (int i = 0; i < ticket_vec.size(); i++) {
				pair<int, Ticket> pr = make_pair(ticket_vec[i].id_ticket, ticket_vec[i]);
				sorted.insert(pr);
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(22) << "Ст. отправл." << setw(11) << "|"
				<< setw(19) << "Дата отправл." << setw(5) << "|"
				<< setw(22) << "Ст. прибытия" << setw(11) << "|"
				<< setw(19) << "Дата прибытия" << setw(5) << "|"
				<< setw(5) << "Кол." << setw(2) << "|"
				<< setw(5) << "Цена" << setw(2) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			for (auto iter : sorted) {
				cout.fill(' ');

				cout << "|";
				SetConsoleTextAttribute(hStdOut, 10);
				cout << setw(5) << iter.first;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(30) << getUppercaseString(iter.second.dep_station.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(19) << iter.second.dep_dt;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(6) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(30) << getUppercaseString(iter.second.arr_station.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(19) << iter.second.arr_dt;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(6) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(5) << iter.second.amount;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(5) << iter.second.price;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|" << endl;

				cout.fill('-');
				cout << "+"
					<< setw(7) << "+"
					<< setw(33) << "+"
					<< setw(24) << "+"
					<< setw(33) << "+"
					<< setw(24) << "+"
					<< setw(7) << "+"
					<< setw(7) << "+" << endl;

				Sleep(100);
			}

			cout.fill(' ');
			ConsoleCursorVisible(false, 100);
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 8);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		case 27: system("cls"); return;
		default: continue;
		}
	}
}

void AdminAcc::filter_tickets() {
	Ticket tk;
	string filtering;
	char request;

	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		ConsoleCursorVisible(false, 100);
		ticket_vec.clear();
		if (!tk.readTicket(ticket_vec)) return;

		cout << endl << " ФИЛЬТР ЖЕЛЕЗНОДОРОЖНЫХ БИЛЕТОВ" << endl << endl;
		SetConsoleTextAttribute(hStdOut, 11);
		cout << "\t\tВЫБЕРИТЕ ПАРАМЕТР, ПО КОТОРОМУ НЕОБХОДИМО ФИЛЬТРОВАТЬ ДАННЫЕ: " << endl << endl;
		SetConsoleTextAttribute(hStdOut, 3);
		cout << "\t\t[1] ~ По СТАНЦИИ ПРИБЫТИЯ, указанной в билете\n";
		cout << "\t\t[2] ~ По ЦЕНЕ билета\n";
		cout << "\t\t[Escape] ~ Для выхода в главное меню\n";

		request = _getch();
		switch (request) {
		case 49: case 97: {
			system("cls");
			SetConsoleTextAttribute(hStdOut, 15);
			ConsoleCursorVisible(false, 100);
			cout << endl << " ФИЛЬТР ЖЕЛЕЗНОДОРОЖНЫХ БИЛЕТОВ (ПО СТАНЦИИ ПРИБЫТИЯ)" << endl << endl;

			while (1) {
				SetConsoleTextAttribute(hStdOut, 15);
				cout << " Введите название станции прибытия: ";
				ConsoleCursorVisible(true, 100);
				SetConsoleTextAttribute(hStdOut, 14);
				rewind(stdin); getline(cin, filtering);
				ConsoleCursorVisible(false, 100);
				if (filtering.empty()) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
					cout << endl << endl;
					continue;
				}
				else break;
			}
			cout << endl << endl;

			bool found = false;
			for (int i = 0; i < ticket_vec.size(); i++) {
				if (getUppercaseString(filtering) == getUppercaseString(ticket_vec[i].arr_station.name_station)) {
					found = true;
					break;
				}
			}

			if (!found) {
				SetConsoleTextAttribute(hStdOut, 12);
				cout << endl << endl << " Ничего не найдено . . . " << endl;
				SetConsoleTextAttribute(hStdOut, 4);
				cout << endl;
				Sleep(2000);
				cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
				if (_getch()) {}
				system("cls");
				return;
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(22) << "Ст. отправл." << setw(11) << "|"
				<< setw(19) << "Дата отправл." << setw(5) << "|"
				<< setw(22) << "Ст. прибытия" << setw(11) << "|"
				<< setw(19) << "Дата прибытия" << setw(5) << "|"
				<< setw(5) << "Кол." << setw(2) << "|"
				<< setw(5) << "Цена" << setw(2) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			for (int i = 0; i < ticket_vec.size(); i++) {
				if (getUppercaseString(filtering) == getUppercaseString(ticket_vec[i].arr_station.name_station)) {
					cout.fill(' ');

					cout << "|";
					SetConsoleTextAttribute(hStdOut, 10);
					cout << setw(5) << ticket_vec[i].id_ticket;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(30) << getUppercaseString(ticket_vec[i].dep_station.name_station);
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(19) << ticket_vec[i].dep_dt;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(6) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(30) << getUppercaseString(ticket_vec[i].arr_station.name_station);
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(19) << ticket_vec[i].arr_dt;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(6) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(5) << ticket_vec[i].amount;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(5) << ticket_vec[i].price;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|" << endl;

					cout.fill('-');
					cout << "+"
						<< setw(7) << "+"
						<< setw(33) << "+"
						<< setw(24) << "+"
						<< setw(33) << "+"
						<< setw(24) << "+"
						<< setw(7) << "+"
						<< setw(7) << "+" << endl;

					Sleep(100);
				}
			}
			
			cout.fill(' ');
			ConsoleCursorVisible(false, 100);
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 8);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		case 50: case 98: {
			system("cls");
			SetConsoleTextAttribute(hStdOut, 15);
			ConsoleCursorVisible(false, 100);
			cout << endl << " ФИЛЬТР ЖЕЛЕЗНОДОРОЖНЫХ БИЛЕТОВ (ПО ЦЕНЕ)" << endl << endl;
			int filtering_left, filtering_right;

			while (1) {
				SetConsoleTextAttribute(hStdOut, 15);
				cout << " Введите ЛЕВУЮ границу: ";
				ConsoleCursorVisible(true, 100);
				SetConsoleTextAttribute(hStdOut, 14);
				cin >> filtering_left;
				ConsoleCursorVisible(false, 100);
				if (cin.fail() || filtering_left < 0) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Введены некорректные данные. Повторите поптыку...";
					cout << endl << endl;
					continue;
				}

				SetConsoleTextAttribute(hStdOut, 15);
				cout << " Введите ПРАВУЮ границу: ";
				ConsoleCursorVisible(true, 100);
				SetConsoleTextAttribute(hStdOut, 14);
				cin >> filtering_right;
				ConsoleCursorVisible(false, 100);
				if (cin.fail() || filtering_right < 0 || filtering_right <= filtering_left) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Введены некорректные данные. Повторите поптыку...";
					cout << endl << endl;
					continue;
				}

				else break;
			}

			cout << endl << endl;

			bool found = false;
			for (int i = 0; i < ticket_vec.size(); i++) {
				if (ticket_vec[i].price >= filtering_left && ticket_vec[i].price <= filtering_right) {
					found = true;
					break;
				}
			}

			if (!found) {
				SetConsoleTextAttribute(hStdOut, 12);
				cout << endl << endl << " Ничего не найдено . . . " << endl;
				SetConsoleTextAttribute(hStdOut, 4);
				cout << endl;
				Sleep(2000);
				cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
				if (_getch()) {}
				system("cls");
				return;
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(22) << "Ст. отправл." << setw(11) << "|"
				<< setw(19) << "Дата отправл." << setw(5) << "|"
				<< setw(22) << "Ст. прибытия" << setw(11) << "|"
				<< setw(19) << "Дата прибытия" << setw(5) << "|"
				<< setw(5) << "Кол." << setw(2) << "|"
				<< setw(5) << "Цена" << setw(2) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(33) << "+"
				<< setw(24) << "+"
				<< setw(7) << "+"
				<< setw(7) << "+" << endl;

			for (int i = 0; i < ticket_vec.size(); i++) {
				if (ticket_vec[i].price >= filtering_left && ticket_vec[i].price <= filtering_right) {
					cout.fill(' ');

					cout << "|";
					SetConsoleTextAttribute(hStdOut, 10);
					cout << setw(5) << ticket_vec[i].id_ticket;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(30) << getUppercaseString(ticket_vec[i].dep_station.name_station);
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(19) << ticket_vec[i].dep_dt;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(6) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(30) << getUppercaseString(ticket_vec[i].arr_station.name_station);
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(19) << ticket_vec[i].arr_dt;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(6) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(5) << ticket_vec[i].amount;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(5) << ticket_vec[i].price;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|" << endl;

					cout.fill('-');
					cout << "+"
						<< setw(7) << "+"
						<< setw(33) << "+"
						<< setw(24) << "+"
						<< setw(33) << "+"
						<< setw(24) << "+"
						<< setw(7) << "+"
						<< setw(7) << "+" << endl;

					Sleep(100);
				}
			}
				
			cout.fill(' ');
			ConsoleCursorVisible(false, 100);
			cout << endl << endl;
			SetConsoleTextAttribute(hStdOut, 8);
			Sleep(2000);
			cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
			if (_getch()) {}
			system("cls");
			return;
		}
		case 27: system("cls"); return;
		default: continue;
		}
	}
}

void AdminAcc::find_ticket() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " ПОИСК ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << endl;
	Ticket tk;
	int finding;
	ticket_vec.clear();
	if (!tk.readTicket(ticket_vec)) return;

	while (1) {
		cout << " Введите ID искомого билета: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		cin >> finding;
		ConsoleCursorVisible(false, 100);
		if (cin.fail() || finding <= 0) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl;

	cout << endl << endl;
	int i;
	bool found = false;
	for (i = 0; i < ticket_vec.size(); i++) {
		if (ticket_vec[i].id_ticket == finding) {
			found = true;
			break;
		}
	}

	if (!found) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Билета с таким ID не существует в базе данных";
		cout << endl << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		Sleep(2000);
		cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
	else {
		SetConsoleTextAttribute(hStdOut, 15);
		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(7) << "+"
			<< setw(7) << "+" << endl;

		cout.fill(' ');
		cout << "|"
			<< setw(4) << "ID" << setw(3) << "|"
			<< setw(22) << "Ст. отправл." << setw(11) << "|"
			<< setw(19) << "Дата отправл." << setw(5) << "|"
			<< setw(22) << "Ст. прибытия" << setw(11) << "|"
			<< setw(19) << "Дата прибытия" << setw(5) << "|"
			<< setw(5) << "Кол." << setw(2) << "|"
			<< setw(5) << "Цена" << setw(2) << "|" << endl;

		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(7) << "+"
			<< setw(7) << "+" << endl;

		cout.fill(' ');

		cout << "|";
		SetConsoleTextAttribute(hStdOut, 10);
		cout << setw(5) << ticket_vec[i].id_ticket;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(30) << getUppercaseString(ticket_vec[i].dep_station.name_station);
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(19) << ticket_vec[i].dep_dt;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(6) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(30) << getUppercaseString(ticket_vec[i].arr_station.name_station);
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(19) << ticket_vec[i].arr_dt;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(6) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(5) << ticket_vec[i].amount;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(5) << ticket_vec[i].price;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|" << endl;

		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(33) << "+"
			<< setw(24) << "+"
			<< setw(7) << "+"
			<< setw(7) << "+" << endl;

		Sleep(100);
	}

	cout.fill(' ');
	ConsoleCursorVisible(false, 100);
	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 8);
	Sleep(2000);
	cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
	if (_getch()) {}
	system("cls");
	return;
}
