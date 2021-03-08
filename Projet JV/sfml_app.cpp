#include <SFML/Graphics.hpp>
#include "Motor.h"
#include "AssetManager.h"
#include "Animator.h"
//#include "PlayerController.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(300 , 300), "SFML works!");
    AssetManager a_manager;
    sf::Clock clock;
    sf::Time deltaTime = clock.restart();

    sf::Sprite player;
    Motor motor(&player);

    //ANIMATION PART
#ifndef ANIMATION



    sf::Sprite test;
    Animator animator(player);
    //Animator a_Player(player)
    

    auto& IdleDownPlayer = animator.CreateAnimation("IdleDown", "PlayerSheet.png", sf::seconds(0.1));
    IdleDownPlayer.AddFrames(sf::Vector2i(26, 0), sf::Vector2i(26, 36), 1);
        
    auto& IdleLeftPlayer = animator.CreateAnimation("IdleLeft", "PlayerSheet.png", sf::seconds(0.1));
    IdleLeftPlayer.AddFrames(sf::Vector2i(26, 36), sf::Vector2i(26, 36), 1);

    auto& IdleRightPlayer = animator.CreateAnimation("IdleRight", "PlayerSheet.png", sf::seconds(0.1));
    IdleRightPlayer.AddFrames(sf::Vector2i(26, 72), sf::Vector2i(26, 36), 1);

    auto& IdleUpPlayer = animator.CreateAnimation("IdleUp", "PlayerSheet.png", sf::seconds(0.1));
    IdleUpPlayer.AddFrames(sf::Vector2i(26, 108), sf::Vector2i(26, 36), 1);


    auto& WalkDownPlayer = animator.CreateAnimation("WalkDown", "PlayerSheet.png", sf::seconds(0.5),true);
    WalkDownPlayer.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(26, 36), 3);

    auto& WalkLeftPlayer = animator.CreateAnimation("WalkLeft", "PlayerSheet.png", sf::seconds(0.5), true);
    WalkLeftPlayer.AddFrames(sf::Vector2i(0, 36), sf::Vector2i(26, 36), 3);

    auto& WalkRightPlayer = animator.CreateAnimation("WalkRight", "PlayerSheet.png", sf::seconds(0.5), true);
    WalkRightPlayer.AddFrames(sf::Vector2i(0, 72), sf::Vector2i(26, 36), 3);

    auto& WalkUpPlayer = animator.CreateAnimation("WalkUp", "PlayerSheet.png", sf::seconds(0.5), true);
    WalkUpPlayer.AddFrames(sf::Vector2i(0, 108), sf::Vector2i(26, 36), 3);


    /*
    auto& IdleAnimation = animator.CreateAnimation("Idle", "chests_small.png", sf::seconds(1));
    IdleAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(16, 16), 1);

    auto& openAnimation = animator.CreateAnimation("Opening", "chests_small.png", sf::seconds(2));
    openAnimation.AddFrames(sf::Vector2i(0, 64), sf::Vector2i(16, 16), 4);
    */
#endif

    auto wSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, wSize.x, wSize.y));

    view.setCenter(sf::Vector2f(0, 0));
    window.setView(view);

    player.setOrigin(sf::Vector2f(26, 36) * 0.5f);
    
    while (window.isOpen())
    {
        deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::EventType::KeyPressed :
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    motor.SetDirection(1, 1);
                    animator.SwitchAnimation("WalkUp");
                    break;
                case sf::Keyboard::Down:
                    motor.SetDirection(2, 1);
                    animator.SwitchAnimation("WalkDown");
                    break;
                case sf::Keyboard::Left:
                    motor.SetDirection(3, 1);
                    animator.SwitchAnimation("WalkLeft");
                    break;
                case sf::Keyboard::Right:
                    motor.SetDirection(4, 1);
                    animator.SwitchAnimation("WalkRight");
                    break;
                case sf::Keyboard::Space:
                    animator.SwitchAnimation("Opening");
                }
                break;
            case sf::Event::EventType::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    motor.SetDirection(1, 0);      
                    animator.SwitchAnimation("IdleUp");
                    break;
                case sf::Keyboard::Down:
                    motor.SetDirection(2, 0);
                    animator.SwitchAnimation("IdleDown");
                    break;
                case sf::Keyboard::Left:
                    motor.SetDirection(3, 0);
                    animator.SwitchAnimation("IdleLeft");
                    break;
                case sf::Keyboard::Right:
                    motor.SetDirection(4, 0);
                    animator.SwitchAnimation("IdleRight");
                    break;
                }
                break;
            }          
        }

        animator.Update(deltaTime);
        motor.Move();

        //ALWAYS CENTER VIEW
        /*
        view.setCenter(player.getPosition());
        window.setView(view);
        */

        //Set listener
        sf::Vector2f playerPos = player.getPosition();
        sf::Listener::setPosition(playerPos.x, playerPos.y, 0);

        window.clear();
        window.draw(player);
        window.draw(test);
        window.display();
        window.setFramerateLimit(60);
    }

    return 0;
}