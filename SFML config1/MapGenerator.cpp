#include "MapGenerator.h"
#include "AssetManager.h"


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

    for (int y = 200; y < 304; y += 8)
    {
        for (int x = 440; x < 640; x += 8)
        {
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(8, 8), sf::Vector2f(x, y), 1));
        }
    }
}

void MapGenerator::PlayerGen(int nbreEquipes, int nbrePersonnages, std::vector<Player*>* players, std::vector<Equipe*>& equipes, std::vector<sf::Vector2f*>& spawnPoints)
{
    for (int i = 0; i < nbreEquipes; i++)
    {
        equipes.push_back(new Equipe(i + 1));
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



