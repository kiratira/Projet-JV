#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platforme.h"



class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	static void MapGen(std::vector<Platforme*> &platformes);
	static MapGenerator* Instance() { return sInstance; }

private:

	static MapGenerator* sInstance;
};

