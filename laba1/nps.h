#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include "Network.h"


class Network;

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
	friend std::ostream& operator << (std::ostream& out, nps nps);
	friend std::istream& operator >> (std::istream& in, nps& nps);
	friend std::ofstream& operator << (std::ofstream& out, nps nps);
	friend std::ifstream& operator >> (std::ifstream& in, nps& nps);
private:
	std::string name;
	int all_ceh;
	int active_ceh;
	float effictivity;
};

void ShowAllNPS(std::unordered_map<int, nps>  all_nps);
std::set<int> selectNPSByID(std::unordered_map<int, nps> all_nps);
void editNPSByCeh(nps& p);
void EditNPS(std::unordered_map<int, nps>& all_nps, Network& network);
void NPSToFile(std::unordered_map<int, nps>  all_nps, std::ofstream& file);
std::unordered_map<int, nps>  NPSFromFile(std::ifstream& file);
bool checkByParametr(nps p, std::string par);
std::set<int> selectNPSByFilter(std::unordered_map<int, nps> all_nps);
