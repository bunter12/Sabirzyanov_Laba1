#include "nps.h"
#include "pipeline.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>;

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

std::ofstream& operator<<(std::ofstream& out, nps nps)
{
	out << nps.GetName() << endl;
	out << nps.GetAll_ceh() << endl;
	out << nps.GetActive_ceh() << endl;
	out << nps.GetEffictivity();
	return out;
}

std::ifstream& operator>>(std::ifstream& in, nps& nps)
{
	string n;
	getline(in, n);
	nps.SetName(n);
	getline(in, n);
	nps.SetAll_ceh(stoi(n));
	getline(in, n);
	nps.SetActive_ceh(stoi(n));
	getline(in, n);
	nps.SetEffictivity(stoi(n));
	return in;
}

void ShowAllNPS(unordered_map<int, nps> all_nps)
{
	for (pair<int, nps> i : all_nps)
		cout << i.first << " НПС" << endl << i.second;
	
}

set<int> selectNPSByID(unordered_map<int, nps> all_nps) {
	cout << "Введите id через пробел" << endl;
	string input;
	getline(cin, input);
	auto lastPair = all_nps.end();
	set<int>selectId;
	lastPair--;
	int id;
	regex num{ "[+\\-]{0,1}\\d+" };
	vector<int> numbers;
	transform(std::sregex_token_iterator{ input.cbegin(), input.cend(), num }, {}, back_inserter(numbers), [](const auto& val) { return std::stoi(val.str()); });
	for (auto i : numbers) {
		if (i > 0 and (i <= lastPair->first)) {
			if (selectId.count(i) == 0)
				selectId.insert(i);
		}
	}
	return selectId;
}

void editNPSByCeh(nps& p) {
	system("cls");
	cout << p;
	string n;
	cout << "Введите число 1, чтобы включить цехи" << endl << "0, чтобы выключить" << endl;
	getline(cin, n);
	while (n != "0" and n != "1") {
		cout << "Введите 1 или 0:" << endl;
		getline(cin, n);
	}
	if (n == "1") {
		cout << "Сколько цехов:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (p.GetAll_ceh() - p.GetActive_ceh())) {
			cout << "Введите число меньшее невключенных цехов" << endl;
			getline(cin, n);
		}
		p.SetActive_ceh(p.GetActive_ceh() + stoi(n));
	}
	else {
		cout << "Сколько цехов:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (p.GetActive_ceh())) {
			cout << "Введите число меньшее включенных цехов" << endl;
			getline(cin, n);
		}
		p.SetActive_ceh(p.GetActive_ceh() - stoi(n));
	}
}

void EditNPS(unordered_map<int, nps>& all_nps)
{
	string n;
	cout << "Если хотите найти НПС по фильтру введите 0" << endl;
	cout << "Если хотите выбрать НПС по id введите 1" << endl;
	int in = getBinNumber();
	set<int> selectId;
	if (in)
		selectId = selectNPSByID(all_nps);
	else
		selectId = selectNPSByFilter(all_nps);
	if (!selectId.empty()) {
		cout << "Выбраны НПС с id ";
		for (auto i : selectId)
			cout << i << " ";
		cout << endl << "Если хотите удалить выбранные НПС введите 0" << endl;
		cout << "Если хотите изменить количество работающих цехов НПС введите 1" << endl;
		in = getBinNumber();
		if (in) {
			for (auto i : selectId)
				editNPSByCeh(all_nps[i]);
		}
		else {
			for (auto i : selectId)
				all_nps.erase(i);
		}
		cout << "Успешно изменено";
	}
	else {
		cout << "Не найденны трубы";
	}
}

void NPSToFile(std::unordered_map<int, nps> all_nps, std::ofstream& file)
{
	file << all_nps.size()<<endl;
	for (auto i:all_nps) {
		file << i.first<<endl;
		file << i.second<<endl;
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
		int idnps;
		getline(file, n);
		idnps = stoi(n);
		file >> new_nps;
		all_nps[idnps] = new_nps ;
	}
	return all_nps;
}


bool checkByParametr(nps p, string par)
{
	return p.GetName().find(par) != std::string::npos;
}



set<int> selectNPSByFilter(unordered_map<int, nps> all_nps) {
	set<int> selectId;
	cout << "Введите 0 если хотите найти НПС по названию" << endl;
	cout << "Введите 1 если хотите найти НПС по проценту незадейственных цехов" << endl;
	int in = getBinNumber();
	string input;
	if (!in) {
		system("cls");
		cout << "Введите строку по которой будем искать НПС" << endl;
		getline(cin, input);
		for (auto i : all_nps) {
			if (checkByParametr(i.second, input))
				selectId.insert(i.first);
		}
	}
	else {
		system("cls");
		cout << "Введите процент незадейственных цехов" << endl;
		getline(cin,input);
		while (!is_number(input)) {
			cout << "Введите число" << endl;
			getline(cin, input);
		}
		cout << "Введите 0 если хотите найти НПС с меньним процентом незадейственных цехов" << endl;
		cout << "Введите 1 если хотите найти НПС с большим процентом незадейственных цехов" << endl;
		in = getBinNumber();
		for (auto i : all_nps) {
			if (in) {
				if (((double)i.second.GetActive_ceh() / (double)i.second.GetAll_ceh())*100 >= stoi(input))
					selectId.insert(i.first);
			}
			else {
				if (((double)i.second.GetActive_ceh() / (double)i.second.GetAll_ceh())*100 <= stoi(input))
					selectId.insert(i.first);
			}
		}
	}
	return selectId;
}