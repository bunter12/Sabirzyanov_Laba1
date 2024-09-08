#include <iostream>
#include <string>
#include "pipeline.h"
#include "nps.h"
#include <vector>
#include <fstream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string input;
	vector<nps> all_nps;
	int a;
	pipeline pipe;
	string k;
	nps nps;
	vector<pipeline> all_pipeline;
	while(true){
		system("cls");
		cout << "Выберите действие:" << endl;
		cout << "1. Добавить трубу" << endl;
		cout << "2. Добавить НПС(КС)" << endl;
		cout << "3. Просморт всех объектов" << endl;
		cout << "4. Редактировать трубу" << endl;
		cout << "5. Редактировать НПС(КС)" << endl;
		cout << "6. Сохранить в файл" << endl;
		cout << "7. Загрузить из файла" << endl;
		cout << "0. Закончить работу" << endl;
		cin >> input;
		try {
			a = stoi(input);
		}
		catch (invalid_argument e) {
			cout << "Введите корректное число" << endl;
			continue;
		}
		switch (a)
		{
		case 1:
			system("cls");
			pipe = AddNewPipe();
			all_pipeline.push_back(pipe);
			break;
		case 2:
			system("cls");
			nps = AddNewNPS();
			all_nps.push_back(nps);
			break;
		case 3:
			system("cls");
			ShowAllPipe(all_pipeline);
			cout << endl << endl;
			ShowAllNPS(all_nps);
			cout <<endl<<endl<< "Введите 0 чтобы вернуться в меню" << endl;
			cin >> k;
			while (k != "0") {
				cout << "Введите 0 чтобы вернуться в меню" << endl;
				cin >> k;
			}
			break;
		case 4:
			system("cls");
			EditPipe(all_pipeline);
			cout << endl << endl << "Введите 0 чтобы вернуться в меню" << endl;
			cin >> k;
			while (k != "0") {
				cout << "Введите 0 чтобы вернуться в меню" << endl;
				cin >> k;
			}
			break;
		case 5:
			system("cls");
			EditNPS(all_nps);
			cout << endl << endl << "Введите 0 чтобы вернуться в меню" << endl;
			cin >> k;
			while (k != "0") {
				cout << "Введите 0 чтобы вернуться в меню" << endl;
				cin >> k;
			}
			break;
		case 6: {
			system("cls");
			ofstream file("text.txt");
			PipeToFile(all_pipeline, file);
			NPSToFile(all_nps, file);
			file.close();
			cout << "Успешно записано в файл"<<endl;
			cout << "Введите 0 чтобы вернуться в меню" << endl;
			cin >> k;
			while (k != "0") {
				cout << "Введите 0 чтобы вернуться в меню" << endl;
				cin >> k;
			}
		}
			break;
		case 7:
		{
			system("cls");
			ifstream file("text.txt");
			if (!file.is_open()) {
				cout << "Нет файла для записи данных" << endl;
				cout << "Введите 0 чтобы вернуться в меню" << endl;
				cin >> k;
				while (k != "0") {
					cout << "Введите 0 чтобы вернуться в меню" << endl;
					cin >> k;
				}
				continue;
			}
			all_pipeline = PipeFromFile(file);
			all_nps = NPSFromFile(file);
			file.close();
			cout << "Успешно записаны данные из файла" << endl;
			cout << "Введите 0 чтобы вернуться в меню" << endl;
			cin >> k;
			while (k != "0") {
				cout << "Введите 0 чтобы вернуться в меню" << endl;
				cin >> k;
			}
		}
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Введите корректное число" << endl;
		}
	}
}