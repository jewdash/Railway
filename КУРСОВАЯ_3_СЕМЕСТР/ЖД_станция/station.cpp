#include "station.h"
#include "console_settings.h"
#include "checkings.h"

bool Station::writeStation() {
	try {
		ofstream fout("stations.txt", ios::app);
		if (!fout) throw "Ошибка открытия файла";

		fout << id_station << "\t"
			<< name_station << "\t"
			<< dep.code_department << "\t"
			<< dep.title << "\t"
			<< region.code_region << "\t"
			<< region.region << "\t"
			<< region.district << "\t" << endl;

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

bool Station::readStation() {
	try { 
		ifstream fin("stations.txt"); 
		if (!fin) throw "Ошибка открытия файла";

		fin >> id_station
			>> name_station
			>> dep.code_department
			>> dep.title
			>> region.code_region
			>> region.region
			>> region.district;

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