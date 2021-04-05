#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "AssetManager.h"
#include "Player.h"
#include "Platforme.h"
#include "MapGenerator.h"
#include "Missile.h"
#include "Caisse.h"
#include "UI.h"

#define VectZero sf::Vector2f(0,0)


void ClearVector(std::vector<Platforme*> vect);
void ClearVector(std::vector<Player*> vect);
void ClearVector(std::vector<Missile*> vect);
void ClearVector(std::vector<Caisse*> vect);
void SwapMainPlayer(Player* actual, Player* next);
bool CheckPlayerAlive(std::vector<Player*> players);

int main()
{
    sf::RenderWindow window(sf::VideoMode(2048, 1080), "SFML works!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2048, 1080));
    sf::View Uiview(sf::Vector2f(window.getSize().x /2, window.getSize().y /2), sf::Vector2f(2048, 1080));
    AssetManager a_manager;
    //GUI ui_manager;
    //MapGenerator a_generator;
    sf::Clock clockDeltaTime;
    sf::Clock clockTimer;
    float deltaTime = 0.0f;

    std::vector<Player*> players;
    std::vector<Platforme*> platformes;
    std::vector<Missile*> missiles;
    std::vector<Caisse*> caisses;

    Player* mainPlayer;
    unsigned int mainPlayernbre = 0;
    bool canChange = true;

    bool startParty = false;

#pragma region TestZONE
    
    //Test Generation player + Main player
    players.push_back(new Player(&AssetManager::GetTexture("persoSheet.png"), sf::Vector2u(3, 3), 0.3f, 200.0f, sf::Vector2f(223, 190) / 3.0f, sf::Vector2f(0, 20), 200.0f, 100, 0));
    players.push_back(new Player(&AssetManager::GetTexture("persoSheet.png"), sf::Vector2u(3, 3), 0.3f, 200.0f, sf::Vector2f(223, 190) / 3.0f, sf::Vector2f(60, 0), 200.0f, 100, 1));
    players.push_back(new Player(&AssetManager::GetTexture("persoSheet.png"), sf::Vector2u(3, 3), 0.3f, 200.0f, sf::Vector2f(223, 190) / 3.0f, sf::Vector2f(200, 0), 200.0f, 100, 1));


    //Test Generation Map
    for (int y = 200; y < 404; y += 4)
    {
        for (int x = 0; x < 400; x += 4)
        {
            platformes.push_back(new Platforme(&AssetManager::GetTexture("PixelSol.png"), sf::Vector2f(4, 4), sf::Vector2f(x, y), 1));
        }
    }

    for (int y = 200; y < 304; y += 4)
    {
        for (int x = 440; x < 640; x += 4)
        {
            platformes.push_back(new Platforme(&AssetManager::GetTexture("PixelSol.png"), sf::Vector2f(4, 4), sf::Vector2f(x, y), 0));
        }
    }

    //caisse de munition

    caisses.push_back(new CaisseMunition(&AssetManager::GetTexture("AmmunitionCrate.png"), sf::Vector2f(32, 32), sf::Vector2f(270, 0), "missile", 3));
    caisses.push_back(new CaisseHeal(&AssetManager::GetTexture("HealCrate.png"), sf::Vector2f(32, 32), sf::Vector2f(330, 0), 30));

    //TEST SOUND (Fonctionnel)
    /*
    sf::Sound sound;
    sound.setBuffer(AssetManager::GetSoundBuffer("boom.ogg")); 
    */
    sf::Vector2f timerPosition = sf::Vector2f(window.getSize().x * 5 / 100, window.getSize().y * 90 / 100);

    Compteur* testCompteur = new Compteur(&AssetManager::GetFont("Stupid Meeting_D.otf"), timerPosition , 0,32,sf::Color::Blue);
    Image* testImage = new Image(&AssetManager::GetTexture("CadreUI.png"), timerPosition, sf::Vector2f(60, 60));
    Button* testButton = new Button(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture("CadreBouton.png"),&AssetManager::GetFont("Stupid Meeting_D.otf"),"Inventaire",32, sf::Vector2f(240,80), sf::Vector2f(window.getSize().x - 240 ,0),0);

    Image* testInventaire = new Image(&AssetManager::GetTexture("CadreBouton.png"), sf::Vector2f(window.getSize().x, window.getSize().y) * 0.45f, sf::Vector2f(window.getSize().x, window.getSize().y) * 0.9f);
    CaseInventaire* testCaseI = new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture("Bazooka.png"), &AssetManager::GetFont("Stupid Meeting_D.otf"), sf::Vector2f(100, 100), sf::Vector2f(100, 100));

    //MAIN PLAYER SELECTION
    players[0]->SetMovement(true);
    mainPlayer = players[mainPlayernbre];

#pragma endregion


    while (window.isOpen())
    {
        deltaTime = clockDeltaTime.restart().asSeconds();

        testCompteur->SetValue(20 - clockTimer.getElapsedTime().asSeconds());

        if (deltaTime > 1.0f / 20.0f) deltaTime = 1.0f / 20.0f; //bug de la fenêtre

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                //Fonction changement mainPlayer
            case sf::Event::EventType::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::T: //SWAP Player test
                    canChange = false;
                    mainPlayernbre++;
                    if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                    SwapMainPlayer(mainPlayer, players[mainPlayernbre]);
                    mainPlayer = players[mainPlayernbre];
                    break;
                case sf::Keyboard::G: // SHOOT

                    //TODO Gestion de l'angle de tire
                    if (mainPlayer->Shoot("missile"))
                    {
                        sf::Vector2f angle = sf::Vector2f(1, -2);
                        if (!mainPlayer->IsFaceRight()) angle.x *= -1;
                        missiles.push_back(new Missile(&AssetManager::GetTexture("missile.png"), sf::Vector2f(13, 24), mainPlayer->GetPosition(), 50, angle, 200, 50));
                    }
                    
                }
                break;
            case sf::Event::EventType::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::T:
                    canChange = true;
                    break;
                }
                break;

            case sf::Event::EventType::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    if (testButton->checkClicked(sf::Mouse::getPosition(window), true))
                    {
                        if (testButton->GetType() == 1)testButton->Add();
                        else if (testButton->GetType() == -1)testButton->Minus();
                    }
                    break;
                }
                break;
            case sf::Event::EventType::MouseButtonReleased:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    testButton->checkClicked(sf::Mouse::getPosition(window), false);
                    break;
                }
                break;
                
            }
            

        }
    

#pragma region Update des entitées

        for (Player* player : players)
        {
            player->Update(deltaTime);
        }

        for (Missile* missile : missiles)
        {
            missile->Update(deltaTime);
        }

        for (Caisse* caisse : caisses)
        {
            caisse->Update(deltaTime);
        }

#pragma endregion      

#pragma region CheckCollision

        sf::Vector2f direction;

        unsigned int cptP = 0;
        unsigned int cptE = 0;
        unsigned int cptM = 0;
        unsigned int cptPl = 0;

        for (Platforme* platforme : platformes)
        {
            for (Player* player : players) //CHECK DES PLAYERS / SOL
            {
                Collider playerCol = player->GetCollider();

                if (platforme->GetCollider().CheckCollision(playerCol, direction, 1.0f)) // UNIQUEMENT PLAYER
                {
                    if (platforme->GetLayer() == 0) //DESTRUCTION EN FCT DU LAYER
                    {
                        player->Oncollision(direction);
                        delete(platforme);
                        platformes.erase(platformes.begin() + cptP);
                    }
                    else
                    {
                        player->Oncollision(direction);
                    }
                }
            }

            cptM = 0;
            for (Missile* missile : missiles) //CHECK DES MISSILES / SOL
            {
                Collider missileCol = missile->GetCollider();

                if (platforme->GetCollider().CheckCollision(missileCol))
                {
                    Collider exploCol = missile->GetExploCollider();
                    
                    //sound.setPosition(missile->GetPosition().x, missile->GetPosition().y, 0);
                    //sound.play();

                    for (int i = 0; i < 7; i++)
                    {
                        cptE = 0;
                        for (Platforme* platforme : platformes)
                        {
                            if (platforme->GetCollider().CheckCollisionCircle(exploCol))
                            {
                                delete(platforme);
                                platformes.erase(platformes.begin() + cptE);
                            }

                            cptE++;
                        }
                    }
                    cptPl = 0;
                    for (Player* player : players)
                    {
                        if (player->GetCollider().CheckCollisionCircle(exploCol))
                            if (player->TakeDamage(missile->GetDamage()))
                            {
                                delete player;
                                players.erase(players.begin() + cptPl);

                                CheckPlayerAlive(players);
                            }
                        cptPl++;
                    }

                    delete(missile);
                    missiles.erase(missiles.begin() + cptM);
                }
                cptM++;
            }

            for (Caisse* caisse : caisses)
            {
                Collider caisseCol = caisse->GetCollider();
                if (platforme->GetCollider().CheckCollision(caisseCol, direction, 1.0f)) {
                    caisse->Oncollision(direction);
                }
            }

            cptP++;
        }
        unsigned int cptC = 0;
        for (Caisse* caisse : caisses)
        {
            for (Player* player : players)
            {
                Collider playerCol = player->GetCollider();

                if (caisse->GetCollider().CheckCollision(playerCol))
                {
                    if (caisse->GetTypeCaisse() == 1)
                    {
                        player->GetInventaire()->AddMunition(caisse->GetTypeMunition(), caisse->GetNbreMunition());
                        delete(caisse);
                        caisses.erase(caisses.begin() + cptC);
                    }
                    else if (caisse->GetTypeCaisse() == 2)
                    {
                        player->RecoverLife(caisse->GetNbreHeal());
                        delete(caisse);
                        caisses.erase(caisses.begin() + cptC);
                    }

                }
            }
            cptC++;
        }

#pragma endregion

#pragma region Camera + Affichage

        view.setCenter(mainPlayer->GetPosition());

        //sf::Listener::setPosition(mainPlayer->GetPosition().x, mainPlayer->GetPosition().y, 0);

        window.clear();

        //entité view
        if (startParty)
        {
            window.setView(view);
            for (Player* player : players)
            {
                player->Draw(window);
            }

            for (Missile* missile : missiles)
            {
                missile->Draw(window);
            }

            for (Platforme* platforme : platformes)
            {
                platforme->Draw(window);
            }

            for (Caisse* caisse : caisses)
            {
                caisse->Draw(window);
            }
        }
       

        //UI view
        window.setView(Uiview);

        testImage->Draw(window);
        testCompteur->Draw(window);    
        testButton->Draw(window);
        testInventaire->Draw(window);
        testCaseI->Draw(window);
        window.display();

#pragma endregion
    
    }
        

    ClearVector(platformes);
    ClearVector(missiles);
    ClearVector(players);
    ClearVector(caisses);


    delete(testButton);
    delete(testImage);
    delete(testCompteur);
    delete(testInventaire);


    return 0;
}


void ClearVector(std::vector<Platforme*> vect)
{
    for (Platforme* element : vect)
    {
        delete element;
    }
    vect.clear();
}

void ClearVector(std::vector<Player*> vect)
{
    for (Player* element : vect)
    {
        delete element;
    }
    vect.clear();
}

void ClearVector(std::vector<Missile*> vect)
{
    for (Missile* element : vect)
    {
        delete element;
    }
    vect.clear();
}

void ClearVector(std::vector<Caisse*> vect)
{
    for (Caisse* element : vect)
    {
        delete element;
    }
    vect.clear();
}

void SwapMainPlayer(Player* actual, Player* next)
{
    actual->SetMovement(false);
    next->SetMovement(true);  
}

bool CheckPlayerAlive(std::vector<Player*> players) {

    if (players.size() == 1)
    {
        std::cout << "GG l'Equipe " << players[0]->GetTagEquipe() << " a gagne" << std::endl;
        return 0;
    }
    else if (players.size() == 0) {
        std::cout << "ex aequo" << std::endl;
        return 0;
    }

    for (int i = 0; i < players.size() - 1; i++)
    {
        if (!players[i]->GetTagEquipe() == players[i + 1]->GetTagEquipe()) {
            break;
        }
        
        if (i == players.size() - 2)
        {
            std::cout << "GG l'Equipe " << players[i]->GetTagEquipe() << " a gagne" << std::endl;
            return 0;
        }
    }

}
