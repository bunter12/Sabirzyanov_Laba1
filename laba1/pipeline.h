#pragma once
#include <string>
#include <unordered_map>
class pipeline {
public:
	void SetName(std::string n);
	void SetLenght(int len);
	void SetDiametr(int d);
	void SetRepair(bool r);
	std::string GetName();
	int GetLenght();
	int GetDiametr();
	bool GetRepair();
	friend std::ostream& operator << (std::ostream& out, pipeline pipe);
	friend std::istream& operator >> (std::istream& in, pipeline& pipe);
private:
	std::string name;
	int lenght;
	int diametr;
	bool repair;
};

bool is_number(std::string s);
void ShowAllPipe(std::unordered_map<int,pipeline> all_pipe);
void EditPipe(std::unordered_map<int, pipeline>&all_pipe);
void PipeToFile(std::unordered_map<int, pipeline>  all_pipe, std::ofstream& file);
std::unordered_map<int, pipeline>  PipeFromFile(std::ifstream &file);