#include "inventory.h"


inventory::inventory()
{
	m_munitions.insert({ "Bazooka", 10 });
	m_munitions.insert({ "Awp", 5 });
}

inventory::~inventory()
{
}

void inventory::AddMunition(std::string type, int nbre)
{
	if (m_munitions.find(type) != m_munitions.end())
	{
		std::cout << "J'ai "<< m_munitions[type] << std::endl;
		m_munitions[type] += nbre;
		std::cout << "J'ai ajouté " << nbre << " / J'ai maintenant " << m_munitions[type] << std::endl;
	}
	else m_munitions.insert({ type, nbre });
}

bool inventory::UseMunition(std::string type)
{
	if (m_munitions.find(type) != m_munitions.end())
	{
		m_munitions[type] -= 1;
		if (m_munitions[type] >= 0)return true;
		else {
			m_munitions[type] += 1;
			return false;
		}
	}
	else std::cout << "PAS TROUVE CE TYPE" << std::endl;
}

int inventory::GetMunition(std::string type)
{
	if (m_munitions.find(type) != m_munitions.end())
	{
		return m_munitions[type];
	}
	else std::cout << "PAS TROUVE CE TYPE" << std::endl;
	return 0;
}

