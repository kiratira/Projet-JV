#include "MapGenerator.h"
#include <assert.h>
#include <random>

#define largeurMap 300
#define block 4

MapGenerator* MapGenerator::sInstance = nullptr;

MapGenerator::MapGenerator()
{
    
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::MapGen(std::vector<Platforme*>* platformes)
{

    for (int y = 200; y < 404; y += 8)
    {
        for (int x = 0; x < 400; x += 8)
        {
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(8, 8), sf::Vector2f(x, y), 1));
        }
    }

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



