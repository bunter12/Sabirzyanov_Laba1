#pragma once
#include <string>
#include <unordered_map>
#include <set>
class pipeline {
public:
	void SetName(std::string n);
	void SetLenght(int len);
	void SetDiametr(int d);
	void SetRepair(bool r);
	std::string GetName() const;
	int GetLenght() const;
	int GetDiametr() const;
	bool GetRepair() const;
	friend std::ostream& operator << (std::ostream& out, pipeline pipe);
	friend std::istream& operator >> (std::istream& in, pipeline& pipe);
	friend std::ofstream& operator << (std::ofstream& out, pipeline& x);
	friend std::ifstream& operator >> (std::ifstream& in, pipeline& x);
private:
	std::string name;
	int lenght;
	int diametr;
	bool repair;
};

bool is_number(std::string s);
int getBinNumber();
void ShowAllPipe(std::unordered_map<int,pipeline> all_pipe);
void EditPipe(std::unordered_map<int, pipeline>&all_pipe);
void PipeToFile(std::unordered_map<int, pipeline>  all_pipe, std::ofstream& file);
std::unordered_map<int, pipeline>  PipeFromFile(std::ifstream &file);
bool checkByParametr(pipeline p, std::string par);
bool checkByParametr(pipeline p, bool par);
std::set<int> selectPipeByFilter(std::unordered_map<int, pipeline>& all_pipe);
void editRepairStatus(pipeline& p);
template<typename type>
std::set<int> filterPipeByParametr(std::unordered_map<int, pipeline> all_pipe, type par);
