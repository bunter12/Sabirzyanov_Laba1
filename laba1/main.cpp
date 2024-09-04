#include <iostream>
#include <string>
#include "pipeline.h"
#include "nps.h"
#include <vector>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string input;
	vector<nps> all_nps;
	int a;
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
		catch (std::invalid_argument e) {
			cout << "Введите корректное число" << endl;
			continue;
		}
		switch (a)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Введите корректное число" << endl;
		}
	}
}