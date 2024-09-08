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
		catch (invalid_argument e) {
			cout << "������� ���������� �����" << endl;
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
			cout <<endl<<endl<< "������� 0 ����� ��������� � ����" << endl;
			cin >> k;
			while (k != "0") {
				cout << "������� 0 ����� ��������� � ����" << endl;
				cin >> k;
			}
			break;
		case 4:
			system("cls");
			EditPipe(all_pipeline);
			cout << endl << endl << "������� 0 ����� ��������� � ����" << endl;
			cin >> k;
			while (k != "0") {
				cout << "������� 0 ����� ��������� � ����" << endl;
				cin >> k;
			}
			break;
		case 5:
			system("cls");
			EditNPS(all_nps);
			cout << endl << endl << "������� 0 ����� ��������� � ����" << endl;
			cin >> k;
			while (k != "0") {
				cout << "������� 0 ����� ��������� � ����" << endl;
				cin >> k;
			}
			break;
		case 6: {
			system("cls");
			ofstream file("text.txt");
			PipeToFile(all_pipeline, file);
			NPSToFile(all_nps, file);
			file.close();
			cout << "������� �������� � ����"<<endl;
			cout << "������� 0 ����� ��������� � ����" << endl;
			cin >> k;
			while (k != "0") {
				cout << "������� 0 ����� ��������� � ����" << endl;
				cin >> k;
			}
		}
			break;
		case 7:
		{
			system("cls");
			ifstream file("text.txt");
			if (!file.is_open()) {
				cout << "��� ����� ��� ������ ������" << endl;
				cout << "������� 0 ����� ��������� � ����" << endl;
				cin >> k;
				while (k != "0") {
					cout << "������� 0 ����� ��������� � ����" << endl;
					cin >> k;
				}
				continue;
			}
			all_pipeline = PipeFromFile(file);
			all_nps = NPSFromFile(file);
			file.close();
			cout << "������� �������� ������ �� �����" << endl;
			cout << "������� 0 ����� ��������� � ����" << endl;
			cin >> k;
			while (k != "0") {
				cout << "������� 0 ����� ��������� � ����" << endl;
				cin >> k;
			}
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