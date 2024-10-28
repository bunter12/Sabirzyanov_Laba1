#include "pipeline.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

bool is_number(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i]))
			return 0;
	}
	return 1;
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


void EditPipe(unordered_map<int, pipeline>& all_pipe) {
	ShowAllPipe(all_pipe);
	string n;
	cout << "Какую трубу изменить?" << endl;
	getline(cin, n);
	while (!is_number(n) or all_pipe.size() < stoi(n) or stoi(n) < 0 or stoi(n) == 0) {
		cout << "Введите корректное число" << endl;
		getline(cin, n);
	}
	all_pipe[stoi(n) - 1].SetRepair(1 - all_pipe[stoi(n)-1].GetRepair());
	cout << "Успешно изменено";
}

void PipeToFile(std::unordered_map<int, pipeline> all_pipe, std::ofstream& file)
{
	file << all_pipe.size()<<endl;
	for (int i = 0; i < all_pipe.size(); i++) {
		file << all_pipe[i].GetName()<<endl;
		file << all_pipe[i].GetLenght()<<endl;
		file << all_pipe[i].GetDiametr() << endl;
		file << all_pipe[i].GetRepair() << endl;
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
		new_pipe.SetName(n);
		getline(file, n);
		new_pipe.SetLenght(stoi(n));
		getline(file, n);
		new_pipe.SetDiametr(stoi(n));
		getline(file, n);
		new_pipe.SetRepair(stoi(n));
		all_pipe[i] = new_pipe;
	}
	return all_pipe;
}
