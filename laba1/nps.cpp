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

std::ostream& operator<<(std::ostream& out, nps nps)
{
	cout << "Название: " << nps.GetName() << endl;
	cout << "Общее количество цехов: " << nps.GetAll_ceh() << endl;
	cout << "Количство цехов в работе: " << nps.GetActive_ceh() << endl;
	cout << "Эффективность НПС: " << nps.GetEffictivity() << endl;
	return out;
}

std::istream& operator>>(std::istream& in, nps& nps)
{
	cout << "Введите название НПС(КС):" << endl;
	string input;
	getline(in, input);
	nps.SetName(input);
	cout << "Введите общее количество цехов:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) == 0) {
		cout << "Введите число" << endl;
		getline(in, input);
	}
	nps.SetAll_ceh(stoi(input));
	cout << "Введите количество работающих цехов:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) > nps.GetAll_ceh()) {
		cout << "Введите число меньшее общего количества цехов" << endl;
		getline(in, input);
	}
	nps.SetActive_ceh(stoi(input));
	cout << "Укажите эффективность станции:" << endl;
	getline(cin, input);
	while (!is_number(input)) {
		cout << "Введите число" << endl;
		getline(in, input);
	}
	nps.SetEffictivity(stof(input));
	return in;
}

void ShowAllNPS(unordered_map<int, nps> all_nps)
{
	for (pair<int, nps> i : all_nps)
		cout << i.first << " НПС" << endl << i.second;
	
}

void EditNPS(std::unordered_map<int, nps>& all_nps)
{
	ShowAllNPS(all_nps);
	string n;
	cout << "Какую НПС изменить?" << endl;
	getline(cin, n);
	while (!is_number(n) or all_nps.size() < stoi(n) or stoi(n) < 0 or stoi(n)==0) {
		cout << "Введите корректное число" << endl;
		getline(cin, n);
	}
	int i = stoi(n)-1;
	cout << "Введите число 1, чтобы включить цехи" << endl << "0, чтобы выключить"<<endl;
	getline(cin, n);
	while(n!="0" and n!="1"){
		cout << "Введите 1 или 0:"<<endl;
		getline(cin, n);
	}
	if (n == "1") {
		cout << "Сколько цехов:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (all_nps[i].GetAll_ceh() - all_nps[i].GetActive_ceh())) {
			cout << "Введите число меньшее невключенных цехов" << endl;
			getline(cin, n);
		}
		all_nps[i].SetActive_ceh(all_nps[i].GetActive_ceh() + stoi(n));
	}
	else {
		cout << "Сколько цехов:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (all_nps[i].GetActive_ceh())) {
			cout << "Введите число меньшее включенных цехов" << endl;
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
