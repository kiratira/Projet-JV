#include <SFML/Graphics.hpp>
#include <vector>
#include "AssetManager.h"
#include "Player.h"
#include "Platforme.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(600.0f, 600.0f));
    AssetManager a_manager;
    sf::Clock clock;
    float deltaTime = 0.0f;

    Player player(&AssetManager::GetTexture("persoSheet.png"), sf::Vector2u(3, 3), 0.3f, 200.0f,sf::Vector2f(74,63), 200.0f);
    
    std::vector<Platforme> platformes;

    platformes.push_back(Platforme(nullptr, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(60.0f, 100.0f)));
    platformes.push_back(Platforme(nullptr, sf::Vector2f(20.0f, 10.0f), sf::Vector2f(0.0f, -5.0f)));

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
        for (Platforme& platforme : platformes)
        {
            if (platforme.GetCollider().CheckCollision(playerCol, direction, 0.0f))
            {
                player.Oncollision(direction);
            }
        }


        view.setCenter(player.GetPosition());
        window.clear();
        window.setView(view);
        player.Draw(window);
        for (Platforme& platforme : platformes)
        {
            platforme.Draw(window);
        }

        window.display();
    }

    return 0;
}