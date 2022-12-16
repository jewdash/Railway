#include "ticket.h"
#include "console_settings.h"
#include "checkings.h"

bool CompareDate::operator()(Ticket& td1, Ticket& td2) {
	if (td1.getDepDate() > td2.getDepDate()) return true;
	else return false;
}

bool Ticket::writeTicket() {
	try {
		ofstream fout("tickets.txt", ios::app);
		if (!fout) throw "Ошибка открытия файла";

		fout << id_ticket << "\t"
			<< dep_dt.dd << "\t"
			<< dep_dt.mm << "\t"
			<< dep_dt.yyyy << "\t"
			<< dep_dt.hh << "\t"
			<< dep_dt.mt << "\t"
			/*<< dep_station.id_station << "\t" */
			<< dep_station.name_station << "\t" 
			/*<< dep_station.dep.code_department << "\t" 
			<< dep_station.dep.title << "\t" 
			<< dep_station.region.code_region << "\t" 
			<< dep_station.region.region << "\t" 
			<< dep_station.region.district << "\t"*/
			<< arr_dt.dd << "\t"
			<< arr_dt.mm << "\t"
			<< arr_dt.yyyy << "\t"
			<< arr_dt.hh << "\t"
			<< arr_dt.mt << "\t"
			/*<< arr_station.id_station << "\t"*/
			<< arr_station.name_station << "\t"
			/*<< arr_station.dep.code_department << "\t"
			<< arr_station.dep.title << "\t"
			<< arr_station.region.code_region << "\t"
			<< arr_station.region.region << "\t"
			<< arr_station.region.district << "\t"*/
			<< amount << "\t"
			<< price << "\t" << endl;

		fout.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return false;
	}
}

bool Ticket::readTicket(vector<Ticket>& tkv) {
	try {
		ifstream fin("tickets.txt");
		if (!fin) throw "Ошибка открытия файла";

		Ticket tk;
		while (!fin.eof()) {
			fin >> tk.id_ticket
				>> tk.dep_dt.dd
				>> tk.dep_dt.mm
				>> tk.dep_dt.yyyy
				>> tk.dep_dt.hh
				>> tk.dep_dt.mt
				//>> dep_station.id_station
				>> tk.dep_station.name_station
				/*>> dep_station.dep.code_department
				>> dep_station.dep.title
				>> dep_station.region.code_region
				>> dep_station.region.region
				>> dep_station.region.district*/
				>> tk.arr_dt.dd
				>> tk.arr_dt.mm
				>> tk.arr_dt.yyyy
				>> tk.arr_dt.hh
				>> tk.arr_dt.mt
				/*>> arr_station.id_station*/
				>> tk.arr_station.name_station
				/*>> arr_station.dep.code_department
				>> arr_station.dep.title
				>> arr_station.region.code_region
				>> arr_station.region.region
				>> arr_station.region.district*/
				>> tk.amount
				>> tk.price;
			tkv.push_back(tk);
		}

		tkv.pop_back();
		fin.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return false;
	}
}

int Ticket::getID() { return id_ticket; }
DateTime Ticket::getDepDate() { return dep_dt; }
DateTime Ticket::getArrDate() { return arr_dt; }
string Ticket::getDepStation() { return dep_station.name_station; }
string Ticket::getArrStation() { return arr_station.name_station; }