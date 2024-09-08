#pragma once
#include <string>
#include <vector>
class nps
{
public:
	void SetName(std::string n);
	void SetAll_ceh(int count);
	void SetActive_ceh(int count);
	void SetEffictivity(float n);
	std::string GetName();
	int GetAll_ceh();
	int GetActive_ceh();
	float GetEffictivity();
private:
	std::string name;
	int all_ceh;
	int active_ceh;
	float effictivity;
};


nps AddNewNPS();
void ShowAllNPS(std::vector<nps> all_nps);
void EditNPS(std::vector<nps>& all_nps);
void NPSToFile(std::vector<nps> all_nps, std::ofstream& file);
std::vector<nps> NPSFromFile(std:: ifstream& file);