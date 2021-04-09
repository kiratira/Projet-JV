#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platforme.h"
#include "Player.h"




class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	static void MapGen(std::vector<Platforme*>* platformes);
	static void MapRand(std::vector<Platforme*>* plateformes);
	//static MapGenerator* Instance() { return sInstance; }
	static void PlayerGen(int nbreEquipes, int nbrePersonnages,std::vector<Player*>* players, std::vector<Equipe*>& equipes, std::vector<sf::Vector2f*>& spawnPoints);
	static void SPGen(std::vector<sf::Vector2f*>* spawnPoints);


};

