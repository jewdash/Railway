#include "accounts.h"
#include "console_settings.h"
#include "checkings.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"

void AdminAcc::add_station() {
	Station st;
	Department depart[7];
	Region reg[83];
	system("cls");
	st.id_station = (1000 + rand() % 10000) - 1000;
	ConsoleCursorVisible(false, 100);
	SetConsoleTextAttribute(hStdOut, 15);
	cout << " ���������� � ���� ������ ��������������� ������� " << endl << endl;

	try {
		ifstream fin_d("departaments.txt"), fin_r("regions.txt");
		if (!fin_d || !fin_r) throw "������ �������� ������ �������";

		int i = 0;
		while (!fin_d.eof() && i < 7) {
			fin_d >> depart[i].code_department
				>> depart[i].title;
			i++;
		}

		i = 0;
		while (!fin_r.eof() && i < 83) {
			fin_r >> reg[i].code_region
				>> reg[i].region
				>> reg[i].district;
			i++;
		}
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return;
	}
	
	while (1) {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " ������� �������� �������: ";
		ConsoleCursorVisible(true, 100);
		SetConsoleTextAttribute(hStdOut, 14);
		getchar(); getline(cin, st.name_station);
		ConsoleCursorVisible(false, 100);
		if (st.name_station.empty()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " ��������� ������ ��-�� ������������� �����. ��������� �������...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;

	while (1) {
		bool compare = false;
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " ***\n";
		cout << " �������� ��������� �/� ����� ����������� � ����� departaments.txt\n";
		cout << " ***\n";
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " ������� ��� ��������� �/�: ";
		ConsoleCursorVisible(true, 100);
		SetConsoleTextAttribute(hStdOut, 14);
		cin >> st.dep.code_department;
		ConsoleCursorVisible(false, 100);

		for (int i = 0; i < 7; i++) {
			if (st.dep.code_department == depart[i].code_department) {
				compare = true;
				st.dep.title = depart[i].title;
				break;
			}
		}

		if (!compare) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " ������ �������������� ��� ��������� �/�. ��������� �������...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;

	while (1) {
		bool compare = false;
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " ***\n";
		cout << " �������� �������� ����� ����������� � ����� regions.txt\n";
		cout << " ***\n";
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " ������� ��� �������, ��� ��������� �/� �������: ";
		ConsoleCursorVisible(true, 100);
		SetConsoleTextAttribute(hStdOut, 14);
		cin >> st.region.code_region;
		ConsoleCursorVisible(false, 100);

		for (int i = 0; i < 83; i++) {
			if (st.region.code_region == reg[i].code_region) {
				compare = true;
				st.region.region = reg[i].region;
				st.region.district = reg[i].district;
				break;
			}
		}

		if (!compare) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " ������ �������������� ��� �������. ��������� �������...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;

	if (st.writeStation()) {
		SetConsoleTextAttribute(hStdOut, 10);
		cout << endl << endl << " ������ ������� �������� � ����." << endl;
		SetConsoleTextAttribute(hStdOut, 2);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� �������, ����� ���������� . . .";
		if (_getch()) {}
		system("cls");
		return;
	}
}

void AdminAcc::remove_station() {

}

void AdminAcc::edit_station() {

}


void AdminAcc::display_stations() {}
void AdminAcc::find_station() {}
void AdminAcc::sort_stations() {}
void AdminAcc::filter_stations() {}
