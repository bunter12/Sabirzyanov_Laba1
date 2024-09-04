#pragma once
#include <string>
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

