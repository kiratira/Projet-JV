#include "MapGenerator.h"
#include <assert.h>
#include <random>

#define largeurMap 300
#define block 4

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

    for (int y = 200; y < 404; y += 8)
    {
        for (int x = 0; x < 400; x += 8)
        {
            platformes.push_back(new Platforme("PixelSol.png", sf::Vector2f(8, 8), sf::Vector2f(x, y), 1));
        }
    }

    for (int y = 200; y < 304; y += 16)
    {
        for (int x = 440; x < 640; x += 16)
        {
            platformes.push_back(new Platforme("PixelSol.png", sf::Vector2f(16, 16), sf::Vector2f(x, y), 1));
        }
    }
}

void MapGenerator::MapRand(std::vector<Platforme*> &platformes)
{

    double courbure = 80.0;
    int filtrage = 10;
    int list[largeurMap] = {};
    std::default_random_engine gen;
    std::normal_distribution<double> distribution(largeurMap/2, courbure);

    //remplissage du tableau avec les hauteur de map
    for (int i = 0; i < 3000; i++) {

        int number = distribution(gen);
        ++list[number % largeurMap];
        
    }

    // creation de la couche de bedrock
    for (int i = 0; i < largeurMap; i++) {
        platformes.push_back(new Platforme("PixelSol.png", sf::Vector2f(block, block), sf::Vector2f(block * i, -1), 1));
    }


    for (int i = 0; i < largeurMap; i++) {
        int height = 0;
        //filtrage
        if (i < 289) {
            for (int iter = 0; iter < filtrage; iter++) {
            height += list[i+iter];
            }
            height /= 10;
        }
        else {
            for (int iter = 0; iter < filtrage; iter++) {
                height += list[i - iter];
            }
            height /= 10;
        }

        //creation de la map
        for (int high = 0; high > -height; high--) {
            platformes.push_back(new Platforme("PixelSol.png", sf::Vector2f(block, block), sf::Vector2f(block*i, block*high), 0));
        }
    }

}

