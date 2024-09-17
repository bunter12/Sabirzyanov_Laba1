#pragma once
#include <string>
#include <unordered_map>
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
void ShowAllNPS(std::unordered_map<int, nps>  all_nps);
void EditNPS(std::unordered_map<int, nps>& all_nps);
void NPSToFile(std::unordered_map<int, nps>  all_nps, std::ofstream& file);
std::unordered_map<int, nps>  NPSFromFile(std:: ifstream& file);