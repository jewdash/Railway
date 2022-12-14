#include "accounts.h"
#include "console_settings.h"
#include "checkings.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"

vector<Station> station_vec;
using namespace std;
using namespace additional_funcs;

void AdminAcc::add_station() {
	Station st;
	Department depart[7];
	Region reg[83];
	system("cls");
	st.id_station = (1000 + rand() % 10000) - 1000;
	ConsoleCursorVisible(false, 100);
	SetConsoleTextAttribute(hStdOut, 15);
	cout << endl << " ДОБАВЛЕНИЕ В БАЗУ ДАННЫХ БЕЛОРУССКОЙ ЖЕЛЕЗНОЙ ДОРОГИ СТАНЦИИ " << endl << endl;

	try {
		ifstream fin_d("departaments.txt"), fin_r("regions.txt");
		if (!fin_d || !fin_r) throw "Ошибка открытия файлов системы";

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
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return;
	}
	
	while (1) {
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " Введите название станции: ";
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

	while (1) {
		bool compare = false;
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " ***\n";
		cout << " Перечень отделений ж/д можно просмотреть в файле departaments.txt\n";
		cout << " ***\n";
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " Введите код отделения ж/д: ";
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
			cout << endl << endl << " Введен несуществующий код отделения ж/д. Повторите поптыку...";
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
		cout << " Перечень регионов можно просмотреть в файле regions.txt\n";
		cout << " ***\n";
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " Введите код региона, где находится ж/д станция: ";
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
			cout << endl << endl << " Введен несуществующий код региона. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl << endl;

	if (st.writeStation()) {
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

void AdminAcc::remove_station() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " УДАЛЕНИЕ СТАНЦИИ ИЗ БАЗЫ ДАННЫХ БЕЛОРУССКОЙ ЖЕЛЕЗНОЙ ДОРОГИ" << endl << endl;
	Station st;
	string deleting;
	station_vec.clear();
	if (!st.readStation(station_vec)) return;
	
	while (1) {
		cout << " Введите название удаляемой станции: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		rewind(stdin); getline(cin, deleting);
		ConsoleCursorVisible(false, 100);
		if (deleting.empty()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}

	int i;
	bool found = false;
	for (i = 0; i < station_vec.size(); i++) {
		if (station_vec[i].name_station == deleting) {
			found = true;
			break;
		}
	}

	if (!found) {
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
	else {
		ofstream fout("stations.txt");
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
			station_vec.erase(station_vec.begin() + i);
			for (int k = 0; k < station_vec.size(); k++) {
				fout << station_vec[k].id_station << "\t"
					<< station_vec[k].name_station << "\t"
					<< station_vec[k].dep.code_department << "\t"
					<< station_vec[k].dep.title << "\t"
					<< station_vec[k].region.code_region << "\t"
					<< station_vec[k].region.region << "\t"
					<< station_vec[k].region.district << "\t" << endl;
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

void AdminAcc::edit_station() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " РЕДАКТИРОВАНИЕ ДАННЫЕ О СТАНЦИИ БЕЛОРУССКОЙ ЖЕЛЕЗНОЙ ДОРОГИ" << endl << " (для редактирования необходимо будет заново ввести все данные)" << endl << endl;
	Station st;
	string editing;
	station_vec.clear();
	if (!st.readStation(station_vec)) return;

	while (1) {
		cout << " Введите название редактируемой станции: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		rewind(stdin); getline(cin, editing);
		ConsoleCursorVisible(false, 100);
		if (editing.empty()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl;

	int i;
	bool found = false;
	for (i = 0; i < station_vec.size(); i++) {
		if (station_vec[i].name_station == editing) {
			found = true;
			break;
		}
	}

	if (!found) {
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
	else {
		ofstream fout("stations.txt");
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
			for (int k = 0; k < station_vec.size(); k++) {
				if (k != i) {
					fout << station_vec[k].id_station << "\t"
						<< station_vec[k].name_station << "\t"
						<< station_vec[k].dep.code_department << "\t"
						<< station_vec[k].dep.title << "\t"
						<< station_vec[k].region.code_region << "\t"
						<< station_vec[k].region.region << "\t"
						<< station_vec[k].region.district << "\t" << endl;
				}
				else {
					Region reg[83];
					Department depart[7];
					st.id_station = station_vec[i].id_station;
					ConsoleCursorVisible(false, 100);
					SetConsoleTextAttribute(hStdOut, 15);

					try {
						ifstream fin_d("departaments.txt"), fin_r("regions.txt");
						if (!fin_d || !fin_r) throw "Ошибка открытия файлов системы";

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
						cout << endl << endl << " Произошла ошибка: " << exc << endl;
						SetConsoleTextAttribute(hStdOut, 4);
						cout << endl;
						Sleep(2000);
						cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
						if (_getch()) {}
						return;
					}

					while (1) {
						SetConsoleTextAttribute(hStdOut, 15);
						cout << " Введите название станции: ";
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

					while (1) {
						bool compare = false;
						SetConsoleTextAttribute(hStdOut, 7);
						cout << " ***\n";
						cout << " Перечень отделений ж/д можно просмотреть в файле departaments.txt\n";
						cout << " ***\n";
						SetConsoleTextAttribute(hStdOut, 15);
						cout << " Введите код отделения ж/д: ";
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
							cout << endl << endl << " Введен несуществующий код отделения ж/д. Повторите поптыку...";
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
						cout << " Перечень регионов можно просмотреть в файле regions.txt\n";
						cout << " ***\n";
						SetConsoleTextAttribute(hStdOut, 15);
						cout << " Введите код региона, где находится ж/д станция: ";
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
							cout << endl << endl << " Введен несуществующий код региона. Повторите поптыку...";
							cout << endl << endl;
							continue;
						}
						else break;
					}
					cout << endl << endl;

					fout << st.id_station << "\t"
						<< st.name_station << "\t"
						<< st.dep.code_department << "\t"
						<< st.dep.title << "\t"
						<< st.region.code_region << "\t"
						<< st.region.region << "\t"
						<< st.region.district << "\t" << endl;
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

void AdminAcc::display_stations() {
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	system("cls");
	cout << endl << " СПИСОК ЖЕЛЕЗНОДОРОЖНЫХ СТАНЦИЙ " << endl << endl;
	Station st;
	station_vec.clear();
	if (!st.readStation(station_vec)) return;

	cout.fill('-');
	cout << "+"
		<< setw(7) << "+"
		<< setw(41) << "+"
		<< setw(25) << "+"
		<< setw(23) << "+"
		<< setw(21) << "+" << endl;

	cout.fill(' ');
	cout << "|"
		<< setw(4) << "ID" << setw(3) << "|"
		<< setw(26) << "Наименование" << setw(15) << "|"
		<< setw(17) << "Отделение БЖД" << setw(8) << "|"
		<< setw(15) << "Область" << setw(8) << "|"
		<< setw(13) << "Район" << setw(8) << "|" << endl;

	cout.fill('-');
	cout << "+"
		<< setw(7) << "+"
		<< setw(41) << "+"
		<< setw(25) << "+"
		<< setw(23) << "+"
		<< setw(21) << "+" << endl;

	for (int i = 0; i < station_vec.size(); i++) {
		cout.fill(' ');

		cout << "|";
		SetConsoleTextAttribute(hStdOut, 10);
		cout << setw(5) << station_vec[i].id_station;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(38) << getUppercaseString(station_vec[i].name_station); 
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(22) << station_vec[i].dep.title;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(20) << station_vec[i].region.region;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(18) << station_vec[i].region.district;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|" << endl;

		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(41) << "+"
			<< setw(25) << "+"
			<< setw(23) << "+"
			<< setw(21) << "+" << endl;

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

void AdminAcc::find_station() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	ConsoleCursorVisible(false, 100);
	cout << endl << " ПОИСК ЖЕЛЕЗНОДОРОЖНОЙ СТАНЦИИ" << endl << endl;
	Station st;
	string finding;
	station_vec.clear();
	if (!st.readStation(station_vec)) return;

	while (1) {
		cout << " Введите название искомой станции: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		rewind(stdin); getline(cin, finding);
		ConsoleCursorVisible(false, 100);
		if (finding.empty()) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl << " Произошла ошибка из-за некорректного ввода. Повторите поптыку...";
			cout << endl << endl;
			continue;
		}
		else break;
	}
	cout << endl;

	int i;
	bool found = false;
	for (i = 0; i < station_vec.size(); i++) {
		if (getUppercaseString(station_vec[i].name_station) == getUppercaseString(finding)) {
			found = true;
			break;
		}
	}

	if (!found) {
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
	else {
		SetConsoleTextAttribute(hStdOut, 15);
		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(41) << "+"
			<< setw(25) << "+"
			<< setw(23) << "+"
			<< setw(21) << "+" << endl;

		cout.fill(' ');
		cout << "|"
			<< setw(4) << "ID" << setw(3) << "|"
			<< setw(26) << "Наименование" << setw(15) << "|"
			<< setw(17) << "Отделение БЖД" << setw(8) << "|"
			<< setw(15) << "Область" << setw(8) << "|"
			<< setw(13) << "Район" << setw(8) << "|" << endl;

		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(41) << "+"
			<< setw(25) << "+"
			<< setw(23) << "+"
			<< setw(21) << "+" << endl;

		cout.fill(' ');

		cout << "|";
		SetConsoleTextAttribute(hStdOut, 10);
		cout << setw(5) << station_vec[i].id_station;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(2) << "|";

		SetConsoleTextAttribute(hStdOut, 14);
		cout << setw(38) << getUppercaseString(station_vec[i].name_station);
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(22) << station_vec[i].dep.title;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(20) << station_vec[i].region.region;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|";

		SetConsoleTextAttribute(hStdOut, 6);
		cout << setw(18) << station_vec[i].region.district;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << setw(3) << "|" << endl;

		cout.fill('-');
		cout << "+"
			<< setw(7) << "+"
			<< setw(41) << "+"
			<< setw(25) << "+"
			<< setw(23) << "+"
			<< setw(21) << "+" << endl;
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

void AdminAcc::sort_stations() {
	Station st;
	char request;

	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		ConsoleCursorVisible(false, 100);
		station_vec.clear();
		if (!st.readStation(station_vec)) return;

		cout << endl << " СОРТИРОВКА ЖЕЛЕЗНОДОРОЖНЫХ СТАНЦИЙ" << endl << endl;
		SetConsoleTextAttribute(hStdOut, 11);
		cout << "\t\tВЫБЕРИТЕ ПАРАМЕТР, ПО КОТОРОМУ НЕОБХОДИМО СОРТИРОВАТЬ ДАННЫЕ: " << endl << endl;
		SetConsoleTextAttribute(hStdOut, 3);
		cout << "\t\t[1] ~ По НАЗВАНИЮ железнодорожной станции\n";
		cout << "\t\t[2] ~ По РЕГИОНУ, в которой нахоятся железнодорожные станции\n";
		cout << "\t\t[3] ~ По ИДЕНТИФИКАЦИОННОМУ НОМЕРУ железнодорожной станции\n";
		cout << "\t\t[Escape] ~ Для выхода в главное меню\n";

		cout << endl << endl;

		request = _getch();
		switch (request) {
		case 49: case 97: {
			map<string, Station> sorted;

			for (int i = 0; i < station_vec.size(); i++) {
				pair<string, Station> pr = make_pair(station_vec[i].name_station, station_vec[i]);
				sorted.insert(pr);
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(26) << "Наименование" << setw(15) << "|"
				<< setw(17) << "Отделение БЖД" << setw(8) << "|"
				<< setw(15) << "Область" << setw(8) << "|"
				<< setw(13) << "Район" << setw(8) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			for (auto iter : sorted) {
				cout.fill(' ');

				cout << "|";
				SetConsoleTextAttribute(hStdOut, 10);
				cout << setw(5) << iter.second.id_station;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(38) << getUppercaseString(iter.first);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(22) << iter.second.dep.title;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(20) << iter.second.region.region;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(18) << iter.second.region.district;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|" << endl;

				cout.fill('-');
				cout << "+"
					<< setw(7) << "+"
					<< setw(41) << "+"
					<< setw(25) << "+"
					<< setw(23) << "+"
					<< setw(21) << "+" << endl;

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
		case 50: case 98: {
			map<int, Station> sorted;

			for (int i = 0; i < station_vec.size(); i++) {
				pair<int, Station> pr = make_pair(station_vec[i].region.code_region, station_vec[i]);
				sorted.insert(pr);
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(26) << "Наименование" << setw(15) << "|"
				<< setw(17) << "Отделение БЖД" << setw(8) << "|"
				<< setw(15) << "Область" << setw(8) << "|"
				<< setw(13) << "Район" << setw(8) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			for (auto iter : sorted) {
				cout.fill(' ');

				cout << "|";
				SetConsoleTextAttribute(hStdOut, 10);
				cout << setw(5) << iter.second.id_station;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(38) << getUppercaseString(iter.second.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(22) << iter.second.dep.title;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(20) << iter.second.region.region;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(18) << iter.second.region.district;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|" << endl;

				cout.fill('-');
				cout << "+"
					<< setw(7) << "+"
					<< setw(41) << "+"
					<< setw(25) << "+"
					<< setw(23) << "+"
					<< setw(21) << "+" << endl;

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
			map<int, Station> sorted;

			for (int i = 0; i < station_vec.size(); i++) {
				pair<int, Station> pr = make_pair(station_vec[i].id_station, station_vec[i]);
				sorted.insert(pr);
			}

			SetConsoleTextAttribute(hStdOut, 15);
			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(26) << "Наименование" << setw(15) << "|"
				<< setw(17) << "Отделение БЖД" << setw(8) << "|"
				<< setw(15) << "Область" << setw(8) << "|"
				<< setw(13) << "Район" << setw(8) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			for (auto iter : sorted) {
				cout.fill(' ');

				cout << "|";
				SetConsoleTextAttribute(hStdOut, 10);
				cout << setw(5) << iter.first;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(2) << "|";

				SetConsoleTextAttribute(hStdOut, 14);
				cout << setw(38) << getUppercaseString(iter.second.name_station);
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(22) << iter.second.dep.title;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(20) << iter.second.region.region;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|";

				SetConsoleTextAttribute(hStdOut, 6);
				cout << setw(18) << iter.second.region.district;
				SetConsoleTextAttribute(hStdOut, 15);
				cout << setw(3) << "|" << endl;

				cout.fill('-');
				cout << "+"
					<< setw(7) << "+"
					<< setw(41) << "+"
					<< setw(25) << "+"
					<< setw(23) << "+"
					<< setw(21) << "+" << endl;

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

void AdminAcc::filter_stations() {
	Station st;
	char request;

	while (1) {
		system("cls");
		SetConsoleTextAttribute(hStdOut, 15);
		ConsoleCursorVisible(false, 100);
		station_vec.clear();
		if (!st.readStation(station_vec)) return;
		Department depart[7];
		Region reg[83];

		try {
			ifstream fin_d("departaments.txt"), fin_r("regions.txt");
			if (!fin_d || !fin_r) throw "Ошибка открытия файлов системы";

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
			cout << endl << endl << " Произошла ошибка: " << exc << endl;
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
			if (_getch()) {}
			return;
		}

		cout << endl << " ФИЛЬТР ЖЕЛЕЗНОДОРОЖНЫХ СТАНЦИЙ" << endl << endl;
		SetConsoleTextAttribute(hStdOut, 11);
		cout << "\t\tВЫБЕРИТЕ ПАРАМЕТР, ПО КОТОРОМУ НЕОБХОДИМО ФИЛЬТРОВАТЬ ДАННЫЕ: " << endl << endl;
		SetConsoleTextAttribute(hStdOut, 3);
		cout << "\t\t[1] ~ По ОТДЕЛЕНИЮ железной дороги\n";
		cout << "\t\t[2] ~ По ОБЛАСТИ, в которой нахоятся железнодорожные станции\n";
		cout << "\t\t[Escape] ~ Для выхода в главное меню\n";

		request = _getch();
		switch (request) {
		case 49: case 97: {
			system("cls");
			SetConsoleTextAttribute(hStdOut, 15);
			ConsoleCursorVisible(false, 100);
			cout << endl << " ФИЛЬТР ЖЕЛЕЗНОДОРОЖНЫХ СТАНЦИЙ (ПО ОТДЕЛЕНИЮ)" << endl << endl;

			while (1) {
				bool compare = false;
				SetConsoleTextAttribute(hStdOut, 7);
				cout << " ***\n";
				cout << " Перечень отделений ж/д можно просмотреть в файле departaments.txt\n";
				cout << " ***\n";
				SetConsoleTextAttribute(hStdOut, 15);
				cout << " Введите код отделения ж/д: ";
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
					cout << endl << endl << " Введен несуществующий код отделения ж/д. Повторите поптыку...";
					cout << endl << endl;
					continue;
				}
				else break;
			}
			cout << endl << endl;

			bool found = false;
			for (int i = 0; i < station_vec.size(); i++) {
				if (station_vec[i].dep.code_department == st.dep.code_department) {
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
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(26) << "Наименование" << setw(15) << "|"
				<< setw(17) << "Отделение БЖД" << setw(8) << "|"
				<< setw(15) << "Область" << setw(8) << "|"
				<< setw(13) << "Район" << setw(8) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			for (int i = 0; i < station_vec.size(); i++) {
				if (station_vec[i].dep.code_department == st.dep.code_department) {
					cout.fill(' ');

					cout << "|";
					SetConsoleTextAttribute(hStdOut, 10);
					cout << setw(5) << station_vec[i].id_station;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(38) << getUppercaseString(station_vec[i].name_station);
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(22) << station_vec[i].dep.title;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(20) << station_vec[i].region.region;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(18) << station_vec[i].region.district;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|" << endl;

					cout.fill('-');
					cout << "+"
						<< setw(7) << "+"
						<< setw(41) << "+"
						<< setw(25) << "+"
						<< setw(23) << "+"
						<< setw(21) << "+" << endl;

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
			cout << endl << " ФИЛЬТР ЖЕЛЕЗНОДОРОЖНЫХ СТАНЦИЙ (ПО ОБЛАСТИ)" << endl << endl;

			while (1) {
				int finding;
				bool compare = false;
				SetConsoleTextAttribute(hStdOut, 7);
				cout << " ***\n";
				cout << " Перечень регионов можно просмотреть в файле regions.txt\n";
				cout << " ***\n";
				SetConsoleTextAttribute(hStdOut, 15);
				cout << " Введите ПЕРВУЮ ЦИФРУ кода региона: ";
				ConsoleCursorVisible(true, 100);
				SetConsoleTextAttribute(hStdOut, 14);
				cin >> finding;
				st.region.code_region = finding * 100;
				ConsoleCursorVisible(false, 100);

				for (int i = 0; i < 83; i++) {
					if (st.region.code_region == reg[i].code_region) {
						compare = true;
						st.region.region = reg[i].region;
						st.region.district = reg[i].district;
						break;
					}
				}

				if (finding < 1 || finding > 7) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Введены некорректные данные. Повторите поптыку...";
					cout << endl << endl;
					continue;
				}
				if (!compare) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " Введен несуществующий код региона. Повторите поптыку...";
					cout << endl << endl;
					continue;
				}
				else break;
			}
			cout << endl << endl;

			bool found = false;
			for (int i = 0; i < station_vec.size(); i++) {
				if (station_vec[i].region.region == st.region.region) {
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
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			cout.fill(' ');
			cout << "|"
				<< setw(4) << "ID" << setw(3) << "|"
				<< setw(26) << "Наименование" << setw(15) << "|"
				<< setw(17) << "Отделение БЖД" << setw(8) << "|"
				<< setw(15) << "Область" << setw(8) << "|"
				<< setw(13) << "Район" << setw(8) << "|" << endl;

			cout.fill('-');
			cout << "+"
				<< setw(7) << "+"
				<< setw(41) << "+"
				<< setw(25) << "+"
				<< setw(23) << "+"
				<< setw(21) << "+" << endl;

			for (int i = 0; i < station_vec.size(); i++) {
				if (station_vec[i].region.region == st.region.region) {
					cout.fill(' ');

					cout << "|";
					SetConsoleTextAttribute(hStdOut, 10);
					cout << setw(5) << station_vec[i].id_station;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(2) << "|";

					SetConsoleTextAttribute(hStdOut, 14);
					cout << setw(38) << getUppercaseString(station_vec[i].name_station);
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(22) << station_vec[i].dep.title;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(20) << station_vec[i].region.region;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|";

					SetConsoleTextAttribute(hStdOut, 6);
					cout << setw(18) << station_vec[i].region.district;
					SetConsoleTextAttribute(hStdOut, 15);
					cout << setw(3) << "|" << endl;

					cout.fill('-');
					cout << "+"
						<< setw(7) << "+"
						<< setw(41) << "+"
						<< setw(25) << "+"
						<< setw(23) << "+"
						<< setw(21) << "+" << endl;

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

