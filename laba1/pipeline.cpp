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
		cout << "Enter 0 or 1"<<endl;
		getline(cin, s);
	}
	return stoi(s);
}


void ShowAllPipe(std::unordered_map<int, pipeline> all_pipe)
{
	for (pair<int, pipeline> i : all_pipe)
		cout << i.first <<" pipeline"<<endl<<i.second;
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
	cout << "Name: " << pipe.GetName() << endl;
	cout << "Length: " << pipe.GetLenght() << endl;
	cout << "Diameter: " << pipe.GetDiametr() << endl;
	if (pipe.GetRepair() == 1)
		cout << "Under repair" << endl;
	else
		cout << "Not under repair" << endl;
	return out;
}

istream& operator>>(std::istream& in, pipeline& pipe)
{
	cout << "Enter pipeline name:" << endl;
	string input;
	getline(in, input);
	pipe.SetName(input);
	cout << "Enter the length:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) == 0) {
		cout << "Enter number" << endl;
		getline(in, input);
	}
	pipe.SetLenght(stoi(input));
	cout << "Choose diameter (only 500, 700, 1000 and 1400):" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) == 0 or stoi(input) != 500 and stoi(input) != 700 and stoi(input) != 1000 and stoi(input) != 1400) {
		cout << "Enter only 500, 700, 1000 or 1400" << endl;
		getline(in, input);
	}
	pipe.SetDiametr(stoi(input));
	cout << "Under repair (1-yes, 0-no):" << endl;
	getline(in, input);
	while (input != "0" and input != "1") {
		cout << "Enter 1 or 0" << endl;
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
	cout << "Enter id of pipeline to select" << endl;
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
	cout << "Enter 0 to select pipeline by name or 1 to select by id" << endl;
	cout << "Enter 0 to edit pipeline or 1 to delete" << endl;
	int in = getBinNumber();
	set<int> selectId;
	if (in)
		selectId = selectPipeById(all_pipe);
	else
		selectId = selectPipeByFilter(all_pipe);
	if (!selectId.empty()) {
		cout << "Selected pipelines with id ";
		for (auto i : selectId)
			cout << i << " ";
		cout << endl<<"Enter 0 to edit pipeline or 1 to delete" << endl;
		in = getBinNumber();
		if (in) {
			for (auto i : selectId)
				editRepairStatus(all_pipe[i]);
		}
		else {
			for (auto i : selectId)
				all_pipe.erase(i);
		}
		cout << "Pipeline edited";
	}
	else {
		cout << "No pipelines selected";
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
	cout << "Enter 0 to select pipeline by name or 1 to select by repair status" << endl;
	int choose = getBinNumber();
	if (!choose) {
		system("cls");
		cout << "Enter name to select pipeline" << endl;
		getline(cin, input);
		selectPipes = filterPipeByParametr(all_pipe, input);
	}
	else {
		system("cls");
		cout << "Enter 0 to select pipeline under repair or 1 to select not under repair" << endl;
		choose = getBinNumber();
		selectPipes = filterPipeByParametr(all_pipe, choose);
	}
	return selectPipes;
}
