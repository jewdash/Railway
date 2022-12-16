#include <iostream>
#include <iomanip>
#include <memory>
#include "history.h"

int History::history_size;
vector<SmartPointer<History>> History::hist;

void History::set_history(History his) {
	buy_date = his.buy_date;
	bought = his.bought;
	sold_num = his.sold_num;
	sum = his.sum;
}

void History::set_buy_date(DateTime dt) {
	buy_date = dt;
}

void History::set_bought(Ticket tk) {
	bought.id_ticket = tk.id_ticket;
	bought.dep_station = tk.dep_station;
	bought.dep_dt = tk.dep_dt;
	bought.arr_station = tk.arr_station;
	bought.arr_dt = tk.arr_dt;
	bought.amount = tk.amount;
	bought.price = tk.price;
}

void History::set_sold(int sold) {
	sold_num = sold;
}

void History::set_sum(int s) {
	sum = s;
}

SmartPointer<History> History::get_history() {
	return hist[history_size];
}

DateTime History::get_buy_date() { return buy_date; }

Ticket History::get_bought() { return bought; }

int History::get_sold() { return sold_num; }

int History::get_sum() { return sum; }

vector<SmartPointer<History>> History::append_hist(History hs) {
	hist[history_size++] = &hs;
	return hist;
}

void History::display_hist() {
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout.fill('=');
	cout << setw(100) << " " << endl;

	cout.fill(' ');
	cout << endl;
	cout << " Дата покупки: " << this->buy_date << endl;
	cout << " ID: " << this->bought.id_ticket << endl;
	cout << " Маршрут: " << this->bought.dep_station.name_station << " ---> " << this->bought.arr_station.name_station << endl;
	cout << " Билет приобретён в количестве (шт): " << this->sold_num << endl;
	cout << " С баланса списаны денежные средства в количестве: " << this->sum << endl;
	cout << endl;

	cout.fill('=');
	cout << setw(100) << " " << endl << endl;
}

void History::read_hist() {
	try {
		ifstream fin("hist.txt");
		if (!fin) throw "Ошибка открытия файла";
		history_size = 0;
		while (!fin.eof()) {
			History buffer;
			fin >> buffer.buy_date
				>> buffer.bought.id_ticket
				>> buffer.bought.dep_station.name_station
				>> buffer.bought.arr_station.name_station
				>> buffer.sold_num;
			/*hist[history_size] = new History;*/
			hist[history_size]->set_history(buffer);
			history_size++;
		}
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return;
	}
}

void History::write_hist() {
	try {
		ofstream fout("hist.txt");
		if (!fout) throw "Ошибка открытия файла";

		fout << hist[history_size]->buy_date << "\t"
			<< hist[history_size]->bought.id_ticket << "\t"
			<< hist[history_size]->bought.dep_station.name_station << "\t"
			<< hist[history_size]->bought.arr_station.name_station << "\t"
			<< hist[history_size]->sold_num << "\t" << endl;

	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return;
	}
}

