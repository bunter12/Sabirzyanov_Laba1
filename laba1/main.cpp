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
		cout << "�������� ��������:" << endl;
		cout << "1. �������� �����" << endl;
		cout << "2. �������� ���(��)" << endl;
		cout << "3. �������� ���� ��������" << endl;
		cout << "4. ������������� �����" << endl;
		cout << "5. ������������� ���(��)" << endl;
		cout << "6. ��������� � ����" << endl;
		cout << "7. ��������� �� �����" << endl;
		cout << "0. ��������� ������" << endl;
		cin >> input;
		try {
			a = stoi(input);
		}
		catch (std::invalid_argument e) {
			cout << "������� ���������� �����" << endl;
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
			cout << "������� ���������� �����" << endl;
		}
	}
}