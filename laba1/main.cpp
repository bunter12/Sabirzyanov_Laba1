#include <iostream>
#include <string>
#include "pipeline.h"
#include "nps.h"
#include <fstream>

using namespace std;

void comeback() {
	string k;
	cout << endl << "������� 0 ����� ��������� � ����" << endl;
	getline(cin, k);
	while (k != "0") {
		cout << "������� 0 ����� ��������� � ����" << endl;
		getline(cin, k);
	}
}
void NoOneObject() {
	cout << "��� ��������"<<endl;
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
		cout << "�������� ��������:" << endl;
		cout << "1. �������� �����" << endl;
		cout << "2. �������� ���(��)" << endl;
		cout << "3. �������� ���� ��������" << endl;
		cout << "4. ������������� �����" << endl;
		cout << "5. ������������� ���(��)" << endl;
		cout << "6. ��������� � ����" << endl;
		cout << "7. ��������� �� �����" << endl;
		cout << "0. ��������� ������" << endl;
		getline(cin, input);
		try {
			a = stoi(input);
		}
		catch (invalid_argument e) {
			cout << "������� ���������� �����" << endl;
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
			cout << "������� �������� � ����"<<endl;
			comeback();
		}
			break;
		case 7:
		{
			system("cls");
			ifstream file("text.txt");
			if (!file.is_open()) {
				cout << "��� ����� ��� ������ ������" << endl;
				comeback();
				continue;
			}
			all_pipeline = PipeFromFile(file);
			all_nps = NPSFromFile(file);
			file.close();
			cout << "������� �������� ������ �� �����" << endl;
			comeback();
		}
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "������� ���������� �����" << endl;
		}
	}
}