#include "nps.h"
#include "pipeline.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void nps::SetName(string n)
{
	name = n;
}

void nps::SetAll_ceh(int count)
{
	all_ceh = count;
}

void nps::SetActive_ceh(int count)
{
	active_ceh = count;
}

void nps::SetEffictivity(float n)
{
	effictivity = n;
}

string nps::GetName()
{
	return name;
}

int nps::GetAll_ceh()
{
	return all_ceh;
}

int nps::GetActive_ceh()
{
	return active_ceh;
}

float nps::GetEffictivity()
{
	return effictivity;
}

nps AddNewNPS() {
	cout << "������� �������� ���(��):" << endl;
	string input;
	getline(cin, input);
	nps newNPS;
	newNPS.SetName(input);
	cout << "������� ����� ���������� �����:" << endl;
	getline(cin, input);
	while (!is_number(input) or stoi(input) == 0) {
		cout << "������� �����" << endl;
		getline(cin, input);
	}
	newNPS.SetAll_ceh(stoi(input));
	cout << "������� ���������� ���������� �����:" << endl;
	getline(cin, input);
	while (!is_number(input) or stoi(input)>newNPS.GetAll_ceh()) {
		cout << "������� ����� ������� ������ ���������� �����" << endl;
		getline(cin, input);
	}
	newNPS.SetActive_ceh(stoi(input));
	cout << "������� ������������� �������:" << endl;
	getline(cin, input);
	while (!is_number(input)) {
		cout << "������� �����" << endl;
		getline(cin, input);
	}
	newNPS.SetEffictivity(stof(input));
	return newNPS;
}

void ShowAllNPS(unordered_map<int, nps> all_nps)
{
	for (int i = 0; i < all_nps.size(); i++) {
		cout << i + 1 << " ���" << endl;
		cout << "��������: " << all_nps[i].GetName() << endl;
		cout << "����� ���������� �����: " << all_nps[i].GetAll_ceh() << endl;
		cout << "��������� ����� � ������: " << all_nps[i].GetActive_ceh() << endl;
		cout << "������������� ���: " << all_nps[i].GetEffictivity() << endl;
	}
}

void EditNPS(std::unordered_map<int, nps>& all_nps)
{
	ShowAllNPS(all_nps);
	string n;
	cout << "����� ��� ��������?" << endl;
	getline(cin, n);
	while (!is_number(n) or all_nps.size() < stoi(n) or stoi(n) < 0 or stoi(n)==0) {
		cout << "������� ���������� �����" << endl;
		getline(cin, n);
	}
	int i = stoi(n)-1;
	cout << "������� ����� 1, ����� �������� ����" << endl << "0, ����� ���������"<<endl;
	getline(cin, n);
	while(n!="0" and n!="1"){
		cout << "������� 1 ��� 0:"<<endl;
		getline(cin, n);
	}
	if (n == "1") {
		cout << "������� �����:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (all_nps[i].GetAll_ceh() - all_nps[i].GetActive_ceh())) {
			cout << "������� ����� ������� ������������ �����" << endl;
			getline(cin, n);
		}
		all_nps[i].SetActive_ceh(all_nps[i].GetActive_ceh() + stoi(n));
	}
	else {
		cout << "������� �����:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (all_nps[i].GetActive_ceh())) {
			cout << "������� ����� ������� ���������� �����" << endl;
			getline(cin, n);
		}
		all_nps[i].SetActive_ceh(all_nps[i].GetActive_ceh() - stoi(n));
	}
}

void NPSToFile(std::unordered_map<int, nps> all_nps, std::ofstream& file)
{
	file << all_nps.size()<<endl;
	for (int i = 0; i < all_nps.size(); i++) {
		file << all_nps[i].GetName() << endl;
		file << all_nps[i].GetAll_ceh() << endl;
		file << all_nps[i].GetActive_ceh() << endl;
		file << all_nps[i].GetEffictivity() << endl;
	}
}

unordered_map<int, nps> NPSFromFile(ifstream& file)
{
	unordered_map<int, nps> all_nps;
	string n;
	getline(file, n);
	int len = stoi(n);
	for (int i = 0; i <len; i++) {
		nps new_nps;
		getline(file, n);
		new_nps.SetName(n);
		getline(file, n);
		new_nps.SetActive_ceh(stoi(n));
		getline(file, n);
		new_nps.SetAll_ceh(stoi(n));
		getline(file, n);
		new_nps.SetEffictivity(stoi(n));
		all_nps[i] = new_nps ;
	}
	return all_nps;
}
