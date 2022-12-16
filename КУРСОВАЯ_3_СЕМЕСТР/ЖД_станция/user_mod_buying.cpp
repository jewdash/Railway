#include "accounts.h"
#include "console_settings.h"
#include "checkings.h"
#include "SmartPtr.h"
#include "history.h"
#include "ticket.h"

vector<SmartPointer<History>> p_hist_vec;

void UserAcc::fill_balance() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " ПОПОЛНЕНИЕ БАЛАНСА ПОЛЬЗОВАТЕЛЯ" << endl << endl;
	
	int to_add;
	while (1) {
		cout << " Введите сумму, которую необходимо положить на баланс (отрицаительное число - списание средств с баланса): ";
		ConsoleCursorVisible(true, 100);
		SetConsoleTextAttribute(hStdOut, 14);
		cin >> to_add;
		ConsoleCursorVisible(false, 100);

		if (cin.fail()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;
	balance += to_add;
	if (!writeInfo()) return;

	SetConsoleTextAttribute(hStdOut, 10);
	cout << endl << endl << " Количество средств на Вашем балансе успешно изменено!";
	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 2);
	Sleep(2000);
	cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
	if (_getch()) {}
	system("cls");
	return;
}

void UserAcc::see_balance() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " БАЛАНС ПОЛЬЗОВАТЕЛЯ" << endl << endl;

	cout << " Количество денежных средств на Вашем балансе: ";
	SetConsoleTextAttribute(hStdOut, 10);
	cout << balance;
	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 2);
	Sleep(2000);
	cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
	if (_getch()) {}
	system("cls");
	return;
}

void UserAcc::buy_ticket() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " ПОКУПКА ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << endl;

	vector<Ticket> ticket_vec;
	Ticket tk;
	int finding;
	ticket_vec.clear();
	if (!tk.readTicket(ticket_vec)) return;

	while (1) {
		cout << " Введите ID покупаемого билета: ";
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

	int to_buy, sum_for_pay;
	try {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << endl << endl << " В каком количестве необходимо приобрести билет: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		cin >> to_buy;
		ConsoleCursorVisible(false, 100);

		if (cin.fail()) throw 0;
		if (!to_buy) throw 1;
		if (to_buy < 0) throw 2;
		if (to_buy > ticket_vec[i].amount) throw 3;
		sum_for_pay = ticket_vec[i].price * to_buy;
		if (sum_for_pay > balance) throw 4;
		
		while (1) {
			system("cls");
			SetConsoleTextAttribute(hStdOut, 15);
			ConsoleCursorVisible(false, 100);
			cout << endl << " ПОКУПКА ЖЕЛЕЗНОДОРОЖНОГО БИЛЕТА" << endl << endl;

			char ch;
			SetConsoleTextAttribute(hStdOut, 11);
			cout << "\t\tС вас " << sum_for_pay << " денежных единиц, вы точно хотите купить билеты?" << endl;
			SetConsoleTextAttribute(hStdOut, 3);
			cout << "\t\t[Enter] ~ Да, покупаю!" << endl;
			cout << "\t\t[Esc] ~ Нет, я передумал..." << endl;

			cout << endl << endl;

			ch = _getch();
			switch (ch) {
			case 13: {
				SmartPointer<History> note(new History);
				note->set_buy_date(date_today());
				note->set_bought(ticket_vec[i]);
				note->set_sold(to_buy);
				note->set_sum(sum_for_pay);
				balance -= sum_for_pay;
				ticket_vec[i].amount -= to_buy;

				ofstream fout("tickets.txt");
				if (!fout) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Ошибка открытия файла: " << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
					if (_getch()) {}
					return;
				}
				else {
					for (int k = 0; k < ticket_vec.size(); k++) {
						if (k == i) {
							fout << ticket_vec[i].id_ticket << "\t"
								<< ticket_vec[i].dep_dt.dd << "\t"
								<< ticket_vec[i].dep_dt.mm << "\t"
								<< ticket_vec[i].dep_dt.yyyy << "\t"
								<< ticket_vec[i].dep_dt.hh << "\t"
								<< ticket_vec[i].dep_dt.mt << "\t"
								/*<< dep_station.id_station << "\t" */
								<< ticket_vec[i].dep_station.name_station << "\t"
								/*<< dep_station.dep.code_department << "\t"
								<< dep_station.dep.title << "\t"
								<< dep_station.region.code_region << "\t"
								<< dep_station.region.region << "\t"
								<< dep_station.region.district << "\t"*/
								<< ticket_vec[i].arr_dt.dd << "\t"
								<< ticket_vec[i].arr_dt.mm << "\t"
								<< ticket_vec[i].arr_dt.yyyy << "\t"
								<< ticket_vec[i].arr_dt.hh << "\t"
								<< ticket_vec[i].arr_dt.mt << "\t"
								/*<< arr_station.id_station << "\t"*/
								<< ticket_vec[i].arr_station.name_station << "\t"
								/*<< arr_station.dep.code_department << "\t"
								<< arr_station.dep.title << "\t"
								<< arr_station.region.code_region << "\t"
								<< arr_station.region.region << "\t"
								<< arr_station.region.district << "\t"*/
								<< ticket_vec[i].amount << "\t"
								<< ticket_vec[i].price << "\t" << endl;
						}
						else {
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
				}

				if (!writeInfo()) return;
				/*note.write_hist();*/

				SetConsoleTextAttribute(hStdOut, 15);
				ConsoleCursorVisible(false, 100);
				cout << endl << endl << " ЧЕК" << endl;
				note->display_hist();
				p_hist_vec.push_back(note);

				SetConsoleTextAttribute(hStdOut, 10);
				cout << endl << endl << " Покупка успешно осуществлена! " << endl;
				cout << " (Просмотреть чек можно в истории покупок)" << endl;
				SetConsoleTextAttribute(hStdOut, 2);
				cout << endl;
				Sleep(2000);
				cout << " Нажмите на любую клавишу, чтобы продолжить . . .";
				if (_getch()) {}
				system("cls");
				return;
			}
			case 27: system("cls"); return;
			default: continue;
			}
		}
	}
	catch (int exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка - код: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
}

void UserAcc::check_history() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " НЕДАВНИЕ ПОКУПКИ" << endl << endl;

	if (p_hist_vec.empty()) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " История покупок пуста " << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		system("cls");
		return;
	}

	for (int i = 0; i < p_hist_vec.size(); i++) {
		p_hist_vec[i]->display_hist();
		cout << endl;
	}

	ConsoleCursorVisible(false, 100);
	cout << endl << endl;
	SetConsoleTextAttribute(hStdOut, 8);
	Sleep(2000);
	cout << " Нажмите на любую клавишу, чтобы выйти в меню . . .";
	if (_getch()) {}
	system("cls");
	return;
}
