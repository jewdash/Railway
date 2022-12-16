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

bool Station::readStation(vector<Station>& stv) {
	try { 
		ifstream fin("stations.txt"); 
		if (!fin) throw "Ошибка открытия файла";

		Station st;
		while (!fin.eof()) {
			fin >> st.id_station
				>> st.name_station
				>> st.dep.code_department
				>> st.dep.title
				>> st.region.code_region
				>> st.region.region
				>> st.region.district;
			stv.push_back(st);
		}
		stv.pop_back();
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

int Station::getIDStation() { return id_station; }
string Station::getNameStation() { return name_station; }