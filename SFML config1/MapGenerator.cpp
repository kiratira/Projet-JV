#include "MapGenerator.h"
#include <assert.h>

MapGenerator* MapGenerator::sInstance = nullptr;

MapGenerator::MapGenerator()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::BlockGeneration(sf::Texture* texture, sf::Vector2f sizeTexture, sf::Vector2f size)
{
	auto& pVector = sInstance->m_Platformes;

	for (int y = 0; y < size.y; y += sizeTexture.y)
	{
		for (int x = 0; x < size.x; x += sizeTexture.x)
		{
			pVector.push_back(new Platforme(texture, sizeTexture, sf::Vector2f(x, y)));
		}			
	}
}

