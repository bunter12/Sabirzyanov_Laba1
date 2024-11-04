#include "pipeline.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;

bool is_number(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i]))
			return 0;
	}
	return 1;
}

bool is_binNumber(string s)
{
	return (s == "0" or s == "1");
}

int getBinNumber() {
	string s;
	int i;
	getline(cin, s);
	while (!is_binNumber(s)) {
		cout << "Введите 0 или 1"<<endl;
		getline(cin, s);
	}
	return stoi(s);
}


void ShowAllPipe(std::unordered_map<int, pipeline> all_pipe)
{
	for (pair<int, pipeline> i : all_pipe)
		cout << i.first <<" труба"<<endl<<i.second;
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

ostream& operator<<(std::ostream& out, pipeline pipe)
{
	cout << "Название: " << pipe.GetName() << endl;
	cout << "Длина трубы: " << pipe.GetLenght() << endl;
	cout << "Диаметр трубы: " << pipe.GetDiametr() << endl;
	if (pipe.GetRepair() == 1)
		cout << "Требуется ремонт" << endl;
	else
		cout << "Ремонт не требуется" << endl;
	return out;
}

istream& operator>>(std::istream& in, pipeline& pipe)
{
	cout << "Введите название трубы:" << endl;
	string input;
	getline(in, input);
	pipe.SetName(input);
	cout << "Введите длину трубы:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) == 0) {
		cout << "Введите число" << endl;
		getline(in, input);
	}
	pipe.SetLenght(stoi(input));
	cout << "Введите диаметр трубы:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) == 0) {
		cout << "Введите число" << endl;
		getline(in, input);
	}
	pipe.SetDiametr(stoi(input));
	cout << "Нужно ли её починить(1-да,0-нет):" << endl;
	getline(in, input);
	while (input != "0" and input != "1") {
		cout << "Введите 1 или 0" << endl;
		getline(in, input);
	}
	return in;
}

std::ofstream& operator<<(std::ofstream& out, pipeline& x)
{
	out << x.GetName() << endl;
	out << x.GetLenght() << endl;
	out << x.GetDiametr() << endl;
	out << x.GetRepair();
	return out;
}

std::ifstream& operator>>(std::ifstream& in, pipeline& x)
{
	string n;
	getline(in, n);
	x.SetName(n);
	getline(in, n);
	x.SetLenght(stoi(n));
	getline(in, n);
	x.SetDiametr(stoi(n));
	getline(in, n);
	x.SetRepair(stoi(n));
	return in;
}

void editRepairStatus(pipeline& p) {
	p.SetRepair(1 - p.GetRepair());
}

set<int> selectPipeById(unordered_map<int, pipeline>& all_pipe) {
	cout << "Введите id через пробел" << endl;
	string input;
	getline(cin, input);
	auto lastPair = all_pipe.end();
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
void EditPipe(unordered_map<int, pipeline>& all_pipe) {
	ShowAllPipe(all_pipe);
	string n;
	cout << "Если хотите найти трубы по фильтру введите 0" << endl;
	cout << "Если хотите выбрать трубы по id введите 1" << endl;
	int in = getBinNumber();
	set<int> selectId;
	if (in)
		selectId = selectPipeById(all_pipe);
	else
		selectId = selectPipeByFilter(all_pipe);
	if (!selectId.empty()) {
		cout << "Выбраны трубы с id ";
		for (auto i : selectId)
			cout << i << " ";
		cout << endl<<"Если хотите удалить выбранные трубы введите 0" << endl;
		cout << "Если хотите изменить статус ремонта выбранных труб введите 1" << endl;
		in = getBinNumber();
		if (in) {
			for (auto i : selectId)
				editRepairStatus(all_pipe[i]);
		}
		else {
			for (auto i : selectId)
				all_pipe.erase(i);
		}
		cout << "Успешно изменено";
	}
	else {
		cout << "Не найденны трубы";
	}
}

void PipeToFile(std::unordered_map<int, pipeline> all_pipe, std::ofstream& file)
{
	file << all_pipe.size()<<endl;
	for (auto i:all_pipe) {
		file << i.first << endl;
		file << i.second<<endl;
	}
}

unordered_map<int, pipeline> PipeFromFile(ifstream& file)
{
	unordered_map<int, pipeline> all_pipe;
	string n;
	getline(file, n);
	int len = stoi(n);
	for (int i = 0; i < len; i++) {
		pipeline new_pipe;
		getline(file, n);
		int idpipe = stoi(n);
		file >> new_pipe;
		all_pipe[idpipe] = new_pipe;
	}
	return all_pipe;
}

bool checkByParametr(pipeline p, string par)
{
	return p.GetName().find(par) != std::string::npos;
}

bool checkByParametr(pipeline p, bool par)
{
	return p.GetRepair() == par;
}


template<typename type>
std::set<int> filterPipeByParametr(std::unordered_map<int, pipeline> all_pipe, type par)
{
	std::set<int> pipes;
	for (auto i : all_pipe) {
		if(checkByParametr(i.second,par))
			pipes.insert(i.first);
	}
	return pipes;
}


set<int> selectPipeByFilter(std::unordered_map<int, pipeline>& all_pipe)
{
	string input;
	set<int> selectPipes;
	cout << "Введите 0 если хотите найти трубы по названию" << endl;
	cout << "Введите 1 если хотите найти трубы по их состоянию" << endl;
	int choose = getBinNumber();
	if (!choose) {
		system("cls");
		cout << "Введите строку по которой будем искать трубы" << endl;
		getline(cin, input);
		selectPipes = filterPipeByParametr(all_pipe, input);
	}
	else {
		system("cls");
		cout << "Введите 0 если хотите найти трубы, которым не нужен ремонт" << endl;
		cout << "Введите 1 если хотите найти трубы, которым нужен ремонт" << endl;
		choose = getBinNumber();
		selectPipes = filterPipeByParametr(all_pipe, choose);
	}
	return selectPipes;
}
