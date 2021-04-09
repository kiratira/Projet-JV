#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "AssetManager.h"
#include "Player.h"
#include "Platforme.h"
#include "MapGenerator.h"
#include "Projectile.h"
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
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280, 720));
    sf::View Uiview(sf::Vector2f(window.getSize().x /2, window.getSize().y /2), sf::Vector2f(1280, 720));
    sf::View Inventaireview(sf::Vector2f(window.getSize().x /2, window.getSize().y /2), sf::Vector2f(1280, 720));
    AssetManager a_manager;
    //GUI ui_manager;
    MapGenerator map;
    sf::Clock clockDeltaTime;
    sf::Clock clockTimer;
    sf::Clock PowerTimer;
    float deltaTime = 0.0f;

    std::vector<Player*> players;
    std::vector<Platforme*> platformes;
    std::vector<Missile*> missiles;
    std::vector<Caisse*> caisses;
    std::vector<Balle*> balles;

    std::vector<CaseInventaire*> casesInventaire;

    Player* mainPlayer;
    unsigned int mainPlayernbre = 0;
    bool canChange = true;

    bool startParty = true;
    bool showInventaire = false;
    bool showViseur = false;
    bool isPressed = false;

    bool showMenu = true;
    bool showParametres = false;
    bool showGame = true;
    bool pause = false;

    std::string selectedWeapon = "Bazooka";

#pragma region TestZONE
    

    //Test Generation player + Main player + Equipe

    Equipe* equipe1 = new Equipe(1);
    Equipe* equipe2 = new Equipe(2);

    players.push_back(new Player(&AssetManager::GetTexture("PlayerSheet.png"), sf::Vector2u(4, 3), 0.2f, 200.0f, sf::Vector2f(128, 128) / 3.0f, sf::Vector2f(50, -100), 80.0f, 100, equipe1));
    players.push_back(new Player(&AssetManager::GetTexture("PlayerSheet.png"), sf::Vector2u(4, 3), 0.3f, 200.0f, sf::Vector2f(128, 128) / 3.0f, sf::Vector2f(40, -100), 80.0f, 100, equipe2));
    players.push_back(new Player(&AssetManager::GetTexture("PlayerSheet.png"), sf::Vector2u(4, 3), 0.3f, 200.0f, sf::Vector2f(128, 128) / 3.0f, sf::Vector2f(45, -100), 80.0f, 100, equipe2));


    //MAIN PLAYER SELECTION
    players[0]->SetMovement(true);
    mainPlayer = players[mainPlayernbre];


    //Test Generation Map

    map.MapRand(platformes);


    //caisse de munition

    caisses.push_back(new CaisseMunition(&AssetManager::GetTexture("AmmunitionCrate.png"), sf::Vector2f(32, 32), sf::Vector2f(270, 0), "Bazooka", 3));
    caisses.push_back(new CaisseMunition(&AssetManager::GetTexture("AmmunitionCrate.png"), sf::Vector2f(32, 32), sf::Vector2f(400, 0), "Bazooka", 3));
    caisses.push_back(new CaisseHeal(&AssetManager::GetTexture("HealCrate.png"), sf::Vector2f(32, 32), sf::Vector2f(330, 0), 30));

    //TEST SOUND (Fonctionnel)
    /*
    sf::Sound sound;
    sound.setBuffer(AssetManager::GetSoundBuffer("boom.ogg")); 
    */
    sf::Vector2f timerPosition = sf::Vector2f(window.getSize().x * 5 / 100, window.getSize().y * 90 / 100);

    Compteur* testCompteur = new Compteur(&AssetManager::GetFont("Stupid Meeting_D.otf"), timerPosition , 0,32,sf::Color::Blue);
    Image* testImage = new Image(&AssetManager::GetTexture("CadreUI.png"), timerPosition, sf::Vector2f(60, 60));

    std::vector<bool*> inventaireBool;
    inventaireBool.push_back(&showInventaire);
    Button* testButton = new BoolButton(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture("CadreBouton.png"),&AssetManager::GetFont("Stupid Meeting_D.otf")
        ,"Inventaire",32, sf::Vector2f(240,80), sf::Vector2f(window.getSize().x - 240 ,0),inventaireBool);

    Image* testInventaire = new Image(&AssetManager::GetTexture("CadreBouton.png"), sf::Vector2f(window.getSize().x, window.getSize().y) * 0.45f, sf::Vector2f(window.getSize().x, window.getSize().y) * 0.9f);
    


    std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions();
    float cptCI = 0;
    float sizeCase = 100;
    for (std::map<std::string, int>::iterator it = inventaire.begin(); it !=inventaire.end(); it++)
    {
        std::cout << it->first << std::endl;
        casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first +".png"), &AssetManager::GetFont("Stupid Meeting_D.otf"), sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase,0)*cptCI,it->first));
        casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
        cptCI++;
    }
    


    sf::RectangleShape viseur;
    viseur.setSize(sf::Vector2f(96, 32));
    viseur.setOrigin(sf::Vector2f(0, mainPlayer->GetSize().y / 2));

#pragma endregion


    while (window.isOpen())
    {

        deltaTime = clockDeltaTime.restart().asSeconds();

        testCompteur->SetValue(20 - clockTimer.getElapsedTime().asSeconds());

        if (deltaTime > 1.0f / 20.0f) deltaTime = 1.0f / 20.0f; //bug de la fen�tre

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
                case sf::Keyboard::Up:
                    if(viseur.getRotation() <= 90 || viseur.getRotation() >= 270)viseur.rotate(600 * -deltaTime);
                    else viseur.setRotation(272);
                    break;
                case sf::Keyboard::Down:
                    if (viseur.getRotation() <= 90 || viseur.getRotation() >= 270)viseur.rotate(600 * deltaTime);
                    else viseur.setRotation(89);
                    break;
                case sf::Keyboard::F:
                    if (showViseur)
                    {
                        if (!isPressed)
                        {
                            isPressed = true;
                            PowerTimer.restart().asSeconds();
                        }
                    }
                }
                break;
            case sf::Event::EventType::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::T:
                    canChange = true;
                    break;
                case sf::Keyboard::F:
                    if (showViseur)
                    {
                        isPressed = false;
                        if (selectedWeapon == "Bazooka") //modifier pour prendre l'arme
                        {
                            mainPlayer->Shoot("Bazooka");
                            float theta = viseur.getRotation() * 3.1416 / 180;
                            sf::Vector2f angle = sf::Vector2f(cos(theta), sin(theta));
                            float power = PowerTimer.getElapsedTime().asMilliseconds();
                            if (!mainPlayer->IsFaceRight()) angle = -angle;                      
                            missiles.push_back(new Missile(&AssetManager::GetTexture("missile.png"), sf::Vector2f(13, 24), mainPlayer->GetPosition() + sf::Vector2f(mainPlayer->GetSize().x,-mainPlayer->GetSize().y /2), 50, angle, power));
                        }
                        if (selectedWeapon == "Awp")
                        {
                            mainPlayer->Shoot("Awp");
                            sf::Vector2f position;
                            float theta = viseur.getRotation() * 3.1416 / 180;
                            sf::Vector2f angle = sf::Vector2f(cos(theta), sin(theta));
                            if (mainPlayer->IsFaceRight())position = mainPlayer->GetPosition() + sf::Vector2f(mainPlayer->GetSize().x + 2, 0);
                            else
                            {
                                angle = -angle;
                                position = mainPlayer->GetPosition() + sf::Vector2f(-mainPlayer->GetSize().x + 2, 0);
                            }
                            balles.push_back(new Balle(position, angle));
                        }
                        showViseur = false;
                        viseur.setRotation(0);
                    }
                }
                break;

            case sf::Event::EventType::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    if (testButton->checkClicked(sf::Mouse::getPosition(window), true))
                    {
                        switch (testButton->GetType())
                        {
                        case 1:
                            testButton->Add();
                            break;
                        case -1:
                            testButton->Minus();
                            break;
                        case 2:
                            testButton->Swap();
                            break;
                        }
                    }
                    for (CaseInventaire* CI : casesInventaire)
                    {
                        if (CI->checkClicked(sf::Mouse::getPosition(window)))
                        {
                            selectedWeapon = *CI->GetType();
                            showInventaire = false;
                            viseur.setTexture(&AssetManager::GetTexture(*CI->GetType() + ".png"));
                            if (mainPlayer->IsFaceRight())viseur.setScale(sf::Vector2f(1, 1));       
                            else viseur.setScale(sf::Vector2f(-1, 1));
                            viseur.setPosition(mainPlayer->GetPosition());
                            showViseur = true;
                        }
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
    
        if (showGame) 
        {

#pragma region Update des entites

            for (Player* player : players)
            {
                player->Update(deltaTime);
            }

            for (Missile* missile : missiles)
            {
                missile->Update(deltaTime);
            }

            for (Balle* balle : balles)
            {
                balle->Update(deltaTime);
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
            unsigned int cptT = 0;


            // !!!!!!!!!!!!! NETTOYER LES COLLISIONS AVEC DES POINTEURS + "FOR" pour retirer les pointeurs

            cptPl = 0;
            for (Player* player : players)
            {
                cptT = 0;
                for (Balle* balle : balles)
                {
                    Collider balleCol = balle->GetCollider();
                    if (player->GetCollider().CheckCollision(&balleCol))
                    {
                        if (player->TakeDamage(balle->GetDamage()))
                        {
                            delete player;
                            players.erase(players.begin() + cptPl);

                            CheckPlayerAlive(players);
                        }
                        delete(balle);
                        balles.erase(balles.begin() + cptT);
                        break;
                    }
                    cptT++;
                }

                cptM = 0;
                for (Missile* missile : missiles) //CHECK DES MISSILES / SOL
                {
                    Collider missileCol = missile->GetCollider();

                    if (player->GetCollider().CheckCollision(&missileCol))
                    {
                        Collider exploCol = missile->GetExploCollider();

                        //sound.setPosition(missile->GetPosition().x, missile->GetPosition().y, 0);
                        //sound.play();

                        for (int i = 0; i < 7; i++)
                        {
                            cptE = 0;
                            for (Platforme* platforme : platformes)
                            {
                                if (platforme->GetCollider().CheckCollisionCircle(&exploCol, exploCol.GetHalfSizeCircle().x))
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
                            if (player->GetCollider().CheckCollisionCircle(&exploCol, exploCol.GetHalfSizeCircle().x))
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

                cptPl++;
            }



            for (Platforme* platforme : platformes)
            {
                cptPl = 0;
                for (Player* player : players) //CHECK DES PLAYERS / SOL
                {
                    Collider playerCol = player->GetCollider();

                    if (platforme->GetCollider().CheckCollision(&playerCol, &direction, 1.0f)) // UNIQUEMENT PLAYER
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

                    if (platforme->GetCollider().CheckCollision(&missileCol))
                    {
                        Collider exploCol = missile->GetExploCollider();

                        //sound.setPosition(missile->GetPosition().x, missile->GetPosition().y, 0);
                        //sound.play();

                        for (int i = 0; i < 7; i++)
                        {
                            cptE = 0;
                            for (Platforme* platforme : platformes)
                            {
                                if (platforme->GetCollider().CheckCollisionCircle(&exploCol, exploCol.GetHalfSizeCircle().x))
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
                            if (player->GetCollider().CheckCollisionCircle(&exploCol, exploCol.GetHalfSizeCircle().x))
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
                    if (platforme->GetCollider().CheckCollision(&caisseCol, &direction, 1.0f)) {
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

                    if (caisse->GetCollider().CheckCollision(&playerCol))
                    {
                        if (caisse->GetTypeCaisse() == 1)
                        {
                            player->GetEquipe()->GetInventaire()->AddMunition(caisse->GetTypeMunition(), caisse->GetNbreMunition());
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

        }

#pragma region Camera + Affichage

        view.setCenter(mainPlayer->GetPosition());

        //sf::Listener::setPosition(mainPlayer->GetPosition().x, mainPlayer->GetPosition().y, 0);

        window.clear();

        //GameView
        if (showGame)
        {
            window.setView(view);

            if (showViseur) window.draw(viseur);
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

            for (Balle* balle : balles)
            {
                balle->Draw(window);
            }
            //UI view
            window.setView(Uiview);

            testImage->Draw(window);
            testCompteur->Draw(window);
            testButton->Draw(window);

            if (showInventaire) {

                testInventaire->Draw(window);
                for (CaseInventaire* CI : casesInventaire)
                {
                    CI->Draw(window);
                }
            }
        }
         
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
    //delete(testInventaire);

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
        std::cout << "GG l'Equipe " << players[0]->GetEquipe()->GetNom() << " a gagne" << std::endl;
        return 0;
    }
    else if (players.size() == 0) {
        std::cout << "ex aequo" << std::endl;
        return 0;
    }

    for (int i = 0; i < players.size() - 1; i++)
    {
        if (!*players[i]->GetEquipe()->GetTagEquipe() == *players[i + 1]->GetEquipe()->GetTagEquipe()) {
            break;
        }
        
        if (i == players.size() - 2)
        {
            std::cout << "GG l'Equipe " << players[i]->GetEquipe()->GetNom() << " a gagne" << std::endl;
            return 0;
        }
    }

}
