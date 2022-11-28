#include "ticket.h"
#include "console_settings.h"
#include "checkings.h"

bool Ticket::writeTicket() {
	try {
		ofstream fout("tickets.txt", ios::app);
		if (!fout) throw "Ошибка открытия файла";

		fout << id_ticket << "\t"
			<< dep_dt << "\t"
			<< dep_station.id_station << "\t" 
			<< dep_station.name_station << "\t" 
			<< dep_station.dep.code_department << "\t" 
			<< dep_station.dep.title << "\t" 
			<< dep_station.region.code_region << "\t" 
			<< dep_station.region.region << "\t" 
			<< dep_station.region.district << "\t"
			<< arr_dt << "\t"
			<< arr_station.id_station << "\t"
			<< arr_station.name_station << "\t"
			<< arr_station.dep.code_department << "\t"
			<< arr_station.dep.title << "\t"
			<< arr_station.region.code_region << "\t"
			<< arr_station.region.region << "\t"
			<< arr_station.region.district << "\t"
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

bool Ticket::readTicket() {
	try {
		ifstream fin("tickets.txt");
		if (!fin) throw "Ошибка открытия файла";

		fin >> id_ticket
			>> dep_dt
			>> dep_station.id_station
			>> dep_station.name_station
			>> dep_station.dep.code_department
			>> dep_station.dep.title
			>> dep_station.region.code_region
			>> dep_station.region.region
			>> dep_station.region.district
			>> arr_dt
			>> arr_station.id_station
			>> arr_station.name_station
			>> arr_station.dep.code_department
			>> arr_station.dep.title
			>> arr_station.region.code_region
			>> arr_station.region.region
			>> arr_station.region.district
			>> amount
			>> price;

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