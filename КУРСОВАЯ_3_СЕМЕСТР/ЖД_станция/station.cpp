#include "station.h"
#include "console_settings.h"
#include "checkings.h"

bool Station::writeStation() {
	try {
		ofstream fout("stations.txt", ios::app);
		if (!fout) throw "������ �������� �����";

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
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return false;
	}
}

bool Station::readStation() {
	try { 
		ifstream fin("stations.txt"); 
		if (!fin) throw "������ �������� �����";

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
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return false;
	}
}