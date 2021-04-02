#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platforme.h"

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	static void BlockGeneration(sf::Texture* texture, sf::Vector2f sizeTexture, sf::Vector2f size);
	static MapGenerator* Instance() { return sInstance; }

private:
	std::vector<Platforme*> m_Platformes;

	static MapGenerator* sInstance;
};

