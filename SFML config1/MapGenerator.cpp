#include "MapGenerator.h"
#include "AssetManager.h"
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

void MapGenerator::MapGen(std::vector<Platforme*> &platformes)
{

    for (int y = 200; y < 404; y += 4)
    {
        for (int x = 0; x < 400; x += 4)
        {
            platformes.push_back(new Platforme("PixelSol.png", sf::Vector2f(4, 4), sf::Vector2f(x, y), 1));
        }
    }

    for (int y = 200; y < 304; y += 4)
    {
        for (int x = 440; x < 640; x += 4)
        {
            platformes.push_back(new Platforme("PixelSol.png", sf::Vector2f(4, 4), sf::Vector2f(x, y), 0));
        }
    }
}

