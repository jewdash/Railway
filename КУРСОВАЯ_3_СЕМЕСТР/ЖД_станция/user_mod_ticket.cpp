#include "accounts.h"
#include "console_settings.h"
#include "checkings.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"

void UserAcc::display_tickets() {
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	system("cls");
	cout << endl << " СПИСОК ЖЕЛЕЗНОДОРОЖНЫХ БИЛЕТОВ " << endl << endl;
	Ticket tk;
	vector<Ticket> ticket_vec;
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

void UserAcc::sort_tickets() {
	Ticket tk;
	vector<Ticket> ticket_vec;
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

void UserAcc::filter_tickets() {
	Ticket tk;
	vector<Ticket> ticket_vec;
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

void UserAcc::find_ticket() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " ПОИСК ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << endl;
	Ticket tk;
	vector<Ticket> ticket_vec;
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
