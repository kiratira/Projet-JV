#include "MapGenerator.h"
#include <assert.h>
#include <random>
#include "AssetManager.h"

#define largeurMap 300
#define block 4.0f

//MapGenerator* MapGenerator::sInstance = nullptr;

MapGenerator::MapGenerator()
{
    
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::MapGen(std::vector<Platforme*>* platformes)
{

    for (float y = 200.0; y < 404.0; y += 8)
    {
        for (float x = 0.0; x < 400.0; x += 8)
        {
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(8, 8), sf::Vector2f(x, y), 1));
        }
    }

    for (float y = 200.0; y < 404.0; y += 8.0)
    {
        for (float x = 0.0; x < 400.0; x += 8.0)
        {
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(8, 8), sf::Vector2f(x, y), 1));
        }
    }

    for (float y = 200.0; y < 304.0; y += 16.0)
    {
        for (float x = 440.0; x < 640.0; x += 16.0)
        {
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(16, 16), sf::Vector2f(x, y), 1));
        }
    }
}

void MapGenerator::MapRand(std::vector<Platforme*>* platformes)
{

    double courbure = 80.0;
    int filtrage = 10;
    int list[largeurMap] = {};
    std::default_random_engine gen;
    std::normal_distribution<double> distribution(largeurMap / 2, courbure);

    //remplissage du tableau avec les hauteur de map
    for (int i = 0; i < 3000; i++) {

        int number = int(distribution(gen));
        ++list[number % largeurMap];

    }

    // creation de la couche de bedrock
    for (int i = 0; i < largeurMap; i++) {
        platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(block, block), sf::Vector2f(block * i, -1), 1));
    }


    for (int i = 0; i < largeurMap; i++) {
        int height = 0;
        //filtrage
        if (i < 289) {
            for (int iter = 0; iter < filtrage; iter++) {
                height += list[i + iter];
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
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(block, block), sf::Vector2f(block * i, block * high), 0));
        }
    }
}

void MapGenerator::PlayerGen(int nbreEquipes, int nbrePersonnages, std::vector<Player*>* players, std::vector<Equipe*>& equipes, std::vector<sf::Vector2f*>& spawnPoints)
{
    std::vector<sf::Color> colors;
    colors.push_back(sf::Color::Blue);
    colors.push_back(sf::Color::Red);
    colors.push_back(sf::Color::Green);
    colors.push_back(sf::Color::Yellow);

    for (int i = 0; i < nbreEquipes; i++)
    {  
        equipes.push_back(new Equipe(i + 1,&colors[i]));
    }

    for (int i = 0; i < nbrePersonnages; i++)
    {
        for (int x = 0; x < nbreEquipes; x++)
        {
            int a = rand() % spawnPoints.size();
            players->push_back(new Player(&AssetManager::GetTexture("PlayerSheet.png"), sf::Vector2u(4, 3), 0.2f, 100.0f, sf::Vector2f(32, 32), spawnPoints[a], 100.0f, 100, equipes[x]));
            delete(spawnPoints[a]);
            spawnPoints.erase(spawnPoints.begin() + a);
        }
    }

}

void MapGenerator::SPGen(std::vector<sf::Vector2f*>* spawnPoints)
{
    spawnPoints->push_back(new sf::Vector2f(0, 0));
    spawnPoints->push_back(new sf::Vector2f(100, 0));
    spawnPoints->push_back(new sf::Vector2f(200, 0));
    spawnPoints->push_back(new sf::Vector2f(300, 0));
}



