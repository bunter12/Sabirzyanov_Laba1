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
	cout << "Name: " << nps.GetName() << endl;
	cout << "Total workshops: " << nps.GetAll_ceh() << endl;
	cout << "Working workshops: " << nps.GetActive_ceh() << endl;
	cout << "Station efficiency: " << nps.GetEffictivity() << endl;
	return out;
}

std::istream& operator>>(std::istream& in, nps& nps)
{
	cout << "Enter station name:" << endl;
	string input;
	getline(in, input);
	nps.SetName(input);
	cout << "Enter total number of workshops:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) == 0) {
		cout << "Enter number" << endl;
		getline(in, input);
	}
	nps.SetAll_ceh(stoi(input));
	cout << "Enter number of working workshops:" << endl;
	getline(in, input);
	while (!is_number(input) or stoi(input) > nps.GetAll_ceh()) {
		cout << "Enter number less than total workshops" << endl;
		getline(in, input);
	}
	nps.SetActive_ceh(stoi(input));
	cout << "Enter station efficiency (0-100):" << endl;
	getline(cin, input);
	while (!is_number(input) or stoi(input) < 0 or stoi(input) > 100) {
		cout << "Enter number between 0 and 100" << endl;
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
		cout << i.first << " Station" << endl << i.second;

}

set<int> selectNPSByID(unordered_map<int, nps> all_nps) {
	cout << "Enter station ID to select:" << endl;
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
	cout << "Enter 1 to start workshop" << endl << "0 to stop workshop" << endl;
	getline(cin, n);
	while (n != "0" and n != "1") {
		cout << "Enter 1 or 0:" << endl;
		getline(cin, n);
	}
	if (n == "1") {
		cout << "Enter number:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (p.GetAll_ceh() - p.GetActive_ceh())) {
			cout << "Enter number less than available workshops" << endl;
			getline(cin, n);
		}
		p.SetActive_ceh(p.GetActive_ceh() + stoi(n));
	}
	else {
		cout << "Enter number:" << endl;
		getline(cin, n);
		while (stoi(n) < 0 or !is_number(n) or stoi(n) > (p.GetActive_ceh())) {
			cout << "Enter number less than working workshops" << endl;
			getline(cin, n);
		}
		p.SetActive_ceh(p.GetActive_ceh() - stoi(n));
	}
}

void EditNPS(unordered_map<int, nps>& all_nps)
{
	string n;
	cout << "Enter 0 to select station by name" << endl;
	cout << "Enter 1 to select station by ID" << endl;
	int in = getBinNumber();
	set<int> selectId;
	if (in)
		selectId = selectNPSByID(all_nps);
	else
		selectId = selectNPSByFilter(all_nps);
	if (!selectId.empty()) {
		cout << "Selected stations with ID ";
		for (auto i : selectId)
			cout << i << " ";
		cout << endl << "Enter 0 to delete selected stations" << endl;
		cout << "Enter 1 to edit number of working workshops" << endl;
		in = getBinNumber();
		if (in) {
			for (auto i : selectId)
				editNPSByCeh(all_nps[i]);
		}
		else {
			for (auto i : selectId)
				all_nps.erase(i);
		}
		cout << "Changes applied";
	}
	else {
		cout << "No stations selected";
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
	cout << "Enter 0 to select stations by name" << endl;
	cout << "Enter 1 to select stations by efficiency" << endl;
	int in = getBinNumber();
	string input;
	if (!in) {
		system("cls");
		cout << "Enter name to select stations:" << endl;
		getline(cin, input);
		for (auto i : all_nps) {
			if (checkByParametr(i.second, input))
				selectId.insert(i.first);
		}
	}
	else {
		system("cls");
		cout << "Enter efficiency to select stations:" << endl;
		getline(cin,input);
		while (!is_number(input)) {
			cout << "Enter number" << endl;
			getline(cin, input);
		}
		cout << "Enter 0 to select stations with efficiency less than or equal to" << endl;
		cout << "Enter 1 to select stations with efficiency greater than or equal to" << endl;
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