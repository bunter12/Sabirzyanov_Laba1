#include <iostream>
#include <string>
#include "pipeline.h"
#include "nps.h"
#include <fstream>

using namespace std;

void backToMenu() {
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
			cin >> pipe;
			all_pipeline[all_pipeline.size()+1] = pipe;
			break;
		case 2:
			system("cls");
			cin >> nps;
			all_nps[all_nps.size()+1] = nps;
			break;
		case 3:
			system("cls");
			if (all_nps.size() == 0 and all_pipeline.size() == 0)
				NoOneObject();
			else {
				ShowAllPipe(all_pipeline);
				ShowAllNPS(all_nps);
			}
			backToMenu();
			break;
		case 4:
			system("cls");
			if (all_pipeline.size() == 0)
				NoOneObject();
			else
				EditPipe(all_pipeline);
			backToMenu();
			break;
		case 5:
			system("cls");
			if (all_nps.size() == 0)
				NoOneObject();
			else
				EditNPS(all_nps);
			backToMenu();
			break;
		case 6: {
			system("cls");
			cout << "Введите название файла:"<<endl;
			string filename;
			getline(cin, filename);
			ofstream file(filename+".txt");
			PipeToFile(all_pipeline, file);
			NPSToFile(all_nps, file);
			file.close();
			cout << "Успешно записано в файл"<<endl;
			backToMenu();
		}
			break;
		case 7:
		{
			system("cls");
			cout << "Введите название файла:" << endl;
			string filename;
			getline(cin, filename);
			ifstream file(filename+".txt");
			if (!file.is_open()) {
				cout << "Нет файла для записи данных" << endl;
				backToMenu();
				continue;
			}
			all_pipeline = PipeFromFile(file);
			all_nps = NPSFromFile(file);
			file.close();
			cout << "Успешно записаны данные из файла" << endl;
			backToMenu();
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