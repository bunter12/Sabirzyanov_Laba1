#pragma once
#include <string>
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
private:
	std::string name;
	int lenght;
	int diametr;
	bool repair;
};