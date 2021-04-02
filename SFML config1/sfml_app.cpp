#include <SFML/Graphics.hpp>
#include <vector>
#include "AssetManager.h"
#include "Player.h"
#include "Platforme.h"
#include "MapGenerator.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(600.0f, 600.0f));
    AssetManager a_manager;
    //MapGenerator a_generator;
    sf::Clock clock;
    float deltaTime = 0.0f;



    Player player(&AssetManager::GetTexture("persoSheet.png"), sf::Vector2u(3, 3), 0.3f, 200.0f,sf::Vector2f(223,190) / 3.0f, 200.0f);   

    std::vector<Platforme*> platformes;

    for (int y = 200; y < 404; y += 4)
    {
        for (int x = 0; x < 400; x += 4)
        {
            platformes.push_back(new Platforme(&AssetManager::GetTexture("PixelSol.png"), sf::Vector2f(4,4), sf::Vector2f(x, y)));
        }
    }


    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f) deltaTime = 1.0f / 20.0f; //bug de la fenêtre


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(deltaTime);

        sf::Vector2f direction;
        Collider playerCol = player.GetCollider();
        
        
        unsigned int cpt = 0;
        for (Platforme* platforme : platformes )
        {
            
            if (platforme->GetCollider().CheckCollision(playerCol, direction, 1.0f)) // UNIQUEMENT PLAYER
            {
                player.Oncollision(direction);
                platformes.erase(platformes.begin() + cpt);
            }
            cpt++;
        }

        view.setCenter(player.GetPosition());
        window.clear();
        window.setView(view);
        player.Draw(window);
        
        for (Platforme* platforme : platformes)
        {
            platforme->Draw(window);
        }

        window.display();
    }

    return 0;
}