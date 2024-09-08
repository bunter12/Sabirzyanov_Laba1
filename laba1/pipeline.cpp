#include "pipeline.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool is_number(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i]))
			return 0;
	}
	return 1;
}


void pipeline::SetName(string n)
{
	name = n;
}

void pipeline::SetLenght(int len)
{
	lenght = len;
}

void pipeline::SetDiametr(int d)
{
	diametr = d;
}

void pipeline::SetRepair(bool r)
{
	repair = r;
}

string pipeline::GetName()
{
	return name;
}

int pipeline::GetLenght()
{
	return lenght;
}

int pipeline::GetDiametr()
{
	return diametr;
}

bool pipeline::GetRepair()
{
	return repair;
}

pipeline AddNewPipe() {
	cout<<"������� �������� �����:"<<endl;
	std::string n;
	cin >> n;
	pipeline newPipe;
	newPipe.SetName(n);
	cout << "������� ����� �����:" << endl;
	string len;
	cin >> len;
	while (!is_number(len)) {
		cout << "������� �����" << endl;
		cin >> len;
	}
	newPipe.SetLenght(stoi(len));
	cout << "������� ������� �����:" << endl;
	cin >> len;
	while (!is_number(len)) {
		cout << "������� �����" << endl;
		cin >> len;
	}
	newPipe.SetDiametr(stoi(len));
	cout << "����� �� � ��������(1-��,0-���):" << endl;
	cin >> len;
	while (len != "0" and len != "1") {
		cout << "������� 1 ��� 0" << endl;
		cin >> len;
	}
	return newPipe;
}

void ShowAllPipe(vector<pipeline> all_pipe)
{
	for (int i = 0; i < all_pipe.size(); i++) {
		cout << i + 1 << " �����"<<endl;
		cout << "��������: " << all_pipe[i].GetName() << endl;
		cout << "����� �����: " << all_pipe[i].GetLenght() << endl;
		cout << "������� �����: " << all_pipe[i].GetDiametr() << endl;
		if (all_pipe[i].GetRepair() == 1)
			cout << "��������� ������" << endl;
		else
			cout << "������ �� ���������" << endl;
	}
}

void EditPipe(vector<pipeline> &all_pipe) {
	ShowAllPipe(all_pipe);
	string n;
	cout << "����� ����� ��������?" << endl;
	cin >> n;
	while (!is_number(n) or all_pipe.size() < stoi(n) or stoi(n) < 0) {
		cout << "������� ���������� �����" << endl;
		cin >> n;
	}
	all_pipe[stoi(n) - 1].SetRepair(1 - all_pipe[stoi(n)-1].GetRepair());
	cout << "������� ��������";
}

void PipeToFile(std::vector<pipeline> all_pipe, std::ofstream& file)
{
	file << all_pipe.size()<<endl;
	for (int i = 0; i < all_pipe.size(); i++) {
		file << all_pipe[i].GetName()<<endl;
		file << all_pipe[i].GetLenght()<<endl;
		file << all_pipe[i].GetDiametr() << endl;
		file << all_pipe[i].GetRepair() << endl;
	}
}

vector<pipeline> PipeFromFile(ifstream& file)
{
	vector<pipeline> all_pipe;
	string n;
	file>>n;
	int len = stoi(n);
	for (int i = 0; i < len; i++) {
		pipeline new_pipe;
		file >> n;
		new_pipe.SetName(n);
		file >> n;
		new_pipe.SetLenght(stoi(n));
		file >> n;
		new_pipe.SetDiametr(stoi(n));
		file >> n;
		new_pipe.SetRepair(stoi(n));
		all_pipe.push_back(new_pipe);
	}
	return all_pipe;
}
