#pragma once
#include <iostream>
#include <map>

class inventory
{
public:
	inventory();
	~inventory();

	void AddMunition(std::string type, int nbre);

	bool UseMunition(std::string type);
	int GetMunition(std::string type);
	std::map<std::string, int> GetAllMunitions() { return m_munitions; }


private:
	std::map<std::string, int> m_munitions;

};

