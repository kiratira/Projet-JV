#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platforme.h"
#include "Player.h"
#include "Caisse.h"




class MapGenerator
{
public:
	static void MapGen(std::vector<Platforme*>* platformes);
	static void MapRand(std::vector<Platforme*>* plateformes);
	//static MapGenerator* Instance() { return sInstance; }
	static void PlayerGen(int nbreEquipes, int nbrePersonnages,std::vector<Player*>* players, std::vector<Equipe*>& equipes, std::vector<sf::Vector2f*>& spawnPoints);
	static void SPGen(int nbEquipes, int nbJoueurs, std::vector<sf::Vector2f*>* spawnPoints);
	static void CaisseGen(std::vector<Caisse*>* caisses);

private:
	static const int largeurMap = 1000;
	static std::map<int, std::string> m_type;
	static int tailleType;
};

