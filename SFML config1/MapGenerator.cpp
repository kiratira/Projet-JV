#include "MapGenerator.h"
#include <assert.h>
#include <random>
#include "AssetManager.h"

/* caractéristiques de la map */
#define largeurMap 1000                         //largeur de la map
#define largeurBlock 4.0f                       // largeur des blocs
#define courbure 120                            // définit la courbure de la colline
#define filtrage 10                             // le nombre d'échantillons 
#define distributeur largeurMap*20              // nombres de blocs a distribuer
#define pointHaut (largeurMap/2)+filtrage       // position du haut de la colline


#define demiMap largeurMap/2
int highest = 0;


// MapGenerator* MapGenerator::sInstance = nullptr;

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


    int list[largeurMap] = {};

    // création de l'outil de distribution normale
    std::default_random_engine gen;
    std::normal_distribution<double> distribution(pointHaut, courbure);

    // remplissage du tableau avec les hauteur de map brutes
    for (int i = 0; i < distributeur; i++) {

        int number = int(distribution(gen));
        ++list[number % largeurMap];

    }

    // creation de la couche de bedrock
    for (int i = -demiMap; i < demiMap; i++) {
        platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(largeurBlock, largeurBlock), sf::Vector2f(largeurBlock * i, -1), 1));
    }

    // creation du relief
    for (int i = 0; i < largeurMap; i++) {
        int height = 0;

        // filtrage
        if (i < (largeurMap-filtrage-1)) {
            for (int iter = 0; iter < filtrage; iter++) {
                height += list[i + iter];
            }
            height /= filtrage;
        }
        else {
            for (int iter = 0; iter < filtrage; iter++) {
                height += list[i - iter];
            }
            height /= 10;
        }

        // recuperer le point le plus haut
        if (height > highest) { highest = height; }

        // creation de la partie destructible de la map
        for (int high = 0; high > -height; high--) {
            platformes->push_back(new Platforme("PixelSol.png", sf::Vector2f(largeurBlock, largeurBlock), sf::Vector2f(largeurBlock * (i-demiMap), largeurBlock * high), 0));
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

void MapGenerator::SPGen(int nbEquipes, int nbJoueurs, std::vector<sf::Vector2f*>* spawnPoints)
{
    // variables
    int entites = nbEquipes * nbJoueurs;
    int hauteur = -((highest + 1) * largeurBlock);
    int position = ((demiMap-50)/8);
    int rang = 1;

    for (int i = 1; i <= entites; i++) { // pour chaque personnage different

        // pour les joueurs pairs
        if ((i % 2) == 0) {

            spawnPoints->push_back(new sf::Vector2f(-position*i, hauteur));
            rang++; // passe a la rangee suivante
        }

        //pour les joueurs impairs
        else {
            spawnPoints->push_back(new sf::Vector2f( position*i, hauteur));
        }
    }
}



