#include <iostream>
#include <string>
#include "pipeline.h"
#include "nps.h"
#include <fstream>

using namespace std;

void comeback() {
	string k;
	cout << endl << "Введите 0 чтобы вернуться в меню" << endl;
	getline(cin, k);
	while (k != "0") {
		cout << "Введите 0 чтобы вернуться в меню" << endl;
		getline(cin, k);
	}
}
void NoOneObject() {
	cout << "Нет объектов"<<endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	string input;
	unordered_map<int,nps> all_nps;
	int a;
	pipeline pipe;
	string k;
	nps nps;
	unordered_map<int,pipeline> all_pipeline;
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
		getline(cin, input);
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
			all_pipeline[all_pipeline.size()] = pipe;
			break;
		case 2:
			system("cls");
			nps = AddNewNPS();
			all_nps[all_nps.size()] = nps;
			break;
		case 3:
			system("cls");
			if (all_nps.size() == 0 and all_pipeline.size() == 0)
				NoOneObject();
			else {
				ShowAllPipe(all_pipeline);
				ShowAllNPS(all_nps);
			}
			comeback();
			break;
		case 4:
			system("cls");
			if (all_pipeline.size() == 0)
				NoOneObject();
			else
				EditPipe(all_pipeline);
			comeback();
			break;
		case 5:
			system("cls");
			if (all_nps.size() == 0)
				NoOneObject();
			else
				EditNPS(all_nps);
			comeback();
			break;
		case 6: {
			system("cls");
			ofstream file("text.txt");
			PipeToFile(all_pipeline, file);
			NPSToFile(all_nps, file);
			file.close();
			cout << "Успешно записано в файл"<<endl;
			comeback();
		}
			break;
		case 7:
		{
			system("cls");
			ifstream file("text.txt");
			if (!file.is_open()) {
				cout << "Нет файла для записи данных" << endl;
				comeback();
				continue;
			}
			all_pipeline = PipeFromFile(file);
			all_nps = NPSFromFile(file);
			file.close();
			cout << "Успешно записаны данные из файла" << endl;
			comeback();
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