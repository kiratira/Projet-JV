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

/* parametres */
#define largeurFen 1280
#define hauteurFen 720
#define sizeButton sf::Vector2f(64, 64) // taille des fleches dans le menu du choix du nombre de joueurs
#define maxTime 30 // durée d'un round en seconde
#define sizeCase  100.0f // taille des cases d'inventaire


#define VectZero sf::Vector2f(0,0)

template <class T>
void ClearVector(std::vector<T*>* vect);

void SwapMainPlayer(Player* actual, Player* next);
bool CheckPlayerAlive(std::vector<Player*> players, bool* game, bool* over, bool* canGen, bool* doneGen, std::string* winner);

int main()
{
    // creation de la fenetre
	sf::RenderWindow window(sf::VideoMode(largeurFen, hauteurFen), "vers de ter'z");
	sf::View view(VectZero, sf::Vector2f(largeurFen, hauteurFen));
	sf::View Uiview(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), sf::Vector2f(largeurFen, hauteurFen));
	sf::View Inventaireview(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), sf::Vector2f(largeurFen, hauteurFen));

    /* variables */
    // gestion du temps
    sf::Clock clockDeltaTime;
    sf::Clock clockTimer;
    sf::Clock PowerTimer;
    float deltaTime = 0.0f;

    // vecteurs
    std::vector<Player*> players;
    std::vector<Equipe*> equipes;
    std::vector<sf::Vector2f*> spawnPoints;
    std::vector<Platforme*> platformes;
    std::vector<Missile*> missiles;
    std::vector<Grenade*> grenades;
    std::vector<Mine*> mines;
    std::vector<Caisse*> caisses;
    std::vector<Balle*> balles;
    std::vector<CaseInventaire*> casesInventaire;
    std::vector<Button*> buttons;
    std::vector<Compteur*> compteurs;
    std::vector<Image*> images;
    std::vector<Label*> labels;


    AssetManager a_manager;
    Player* mainPlayer = nullptr;

    // booleens de reglages
    unsigned int mainPlayernbre = 0; 
    bool readyToPlay = false;
    bool canChange = false;

    bool startParty = true;
    bool showInventaire = false;
    bool showViseur = false;
    bool isPressed = false;

    bool showMenu = true;
    bool showParametres = false;
    bool showGame = false;
    bool showReady = true;
    bool showGameOver = false;
    bool pause = false;

    bool canGen = true;
    bool doneGen = false;
    bool exitPause = true;

    std::string selectedWeapon = "Bazooka";
    std::string winner = "";
    sf::RectangleShape* viseur = new sf::RectangleShape();
    int cptCI;

    // compteurs de checkCollision
    unsigned int cptPl;
    unsigned int cptE;
    unsigned int cptM;
    unsigned int cptT;
    unsigned int cptP;
    unsigned int cptMine;

    // mise des booleens dans des vecteurs
    std::vector<bool*> goToParametes;
    std::vector<bool*> goToGame;
    std::vector<bool*> goToMenu;
    std::vector<bool*> goToPause;
    std::vector<bool*> goToInventaire;

    goToParametes.push_back(&showMenu);
    goToParametes.push_back(&showParametres);
    goToParametes.push_back(&canGen);
    goToParametes.push_back(&doneGen);

    goToGame.push_back(&showParametres);
    goToGame.push_back(&showGame);
    goToGame.push_back(&canGen);
    goToGame.push_back(&doneGen);

    goToPause.push_back(&pause);

    goToInventaire.push_back(&showInventaire);

    goToMenu.push_back(&showGameOver);
    goToMenu.push_back(&showMenu);
    goToMenu.push_back(&canGen);

    sf::Sound soundExplosion, soundAwp, soundBazooka, musicOpen, musicGame, soundAmmo, soundHeal, soundHit, soundGrenade,soundMine;
    soundExplosion.setBuffer(AssetManager::GetSoundBuffer("Explosion.ogg"));
    soundAwp.setBuffer(AssetManager::GetSoundBuffer("Awp.ogg"));
    soundBazooka.setBuffer(AssetManager::GetSoundBuffer("Bazooka.ogg"));
    musicOpen.setBuffer(AssetManager::GetSoundBuffer("Open.ogg"));
    musicGame.setBuffer(AssetManager::GetSoundBuffer("FondSonore.ogg"));
    soundHeal.setBuffer(AssetManager::GetSoundBuffer("Heal.ogg"));
    soundAmmo.setBuffer(AssetManager::GetSoundBuffer("Ammo.ogg"));
    soundHit.setBuffer(AssetManager::GetSoundBuffer("hit.ogg"));
    soundGrenade.setBuffer(AssetManager::GetSoundBuffer("Grenade.ogg"));
    soundMine.setBuffer(AssetManager::GetSoundBuffer("Mine.ogg"));


    while (window.isOpen())
    {
        // Generation
        if (canGen)
        {
            /* menu titre */
            if (showMenu)
            {
                // clear le texte et le boutons
                if (!labels.empty()) ClearVector(&labels);
                if (!buttons.empty()) ClearVector(&buttons);

				buttons.push_back(
                    new BoolButton(
                        &AssetManager::GetTexture("CadreBouton.png"),
                        &AssetManager::GetTexture("CadreBouton.png"),
                        "Lancer partie",
                        32,
                        sf::Vector2f(300, 70),
                        sf::Vector2f(window.getSize().x / 2.5f, 
                        (window.getSize().y / 2.0f) - 10.0f),
                        goToParametes));

				canGen = false;
                musicOpen.play();
            }

            /* menu de gestion des equipes/personnages */
            if (showParametres) 
            {
                ClearVector(&buttons); //clear de tous les boutons du menu
                labels.push_back(new Label(sf::Vector2f(window.getSize().x / 4.0f, window.getSize().y / 3.0f),"Equipes",24,sf::Color::Yellow));
                labels.push_back(new Label(sf::Vector2f(window.getSize().x / 4.0f, window.getSize().y / 2.0f),"Joueurs",24,sf::Color::Yellow));

                
                compteurs.push_back(new Compteur(sf::Vector2f(window.getSize().x / 2.0f - 100.0f, window.getSize().y / 3.0f), 2, 4, 2, 32, sf::Color::Blue)); // Equipe
                compteurs.push_back(new Compteur(sf::Vector2f(window.getSize().x / 2.0f - 100.0f, window.getSize().y / 2.0f), 1, 4, 1, 32, sf::Color::Blue)); // Personnages

                //add Equipe
                buttons.push_back(new AddButton(
                    &AssetManager::GetTexture("ButtonNormalCompteur.png"),
                    &AssetManager::GetTexture("ButtonClickedCompteur.png"),
                    sizeButton, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 3.0f), compteurs[0])); 

                //minus Equipe
                buttons.push_back(new MinusButton(
                    &AssetManager::GetTexture("ButtonNormalCompteurInverse.png"),
                    &AssetManager::GetTexture("ButtonClickedCompteurInverse.png"),
                    sizeButton, sf::Vector2f(window.getSize().x / 3.0f, window.getSize().y / 3.0f), compteurs[0])); 

                //add Personnages
                buttons.push_back(new AddButton(
                    &AssetManager::GetTexture("ButtonNormalCompteur.png"),
                    &AssetManager::GetTexture("ButtonClickedCompteur.png"),
                    sizeButton, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), compteurs[1])); 

                //minus Personnages
                buttons.push_back(new MinusButton(
                    &AssetManager::GetTexture("ButtonNormalCompteurInverse.png"),
                    &AssetManager::GetTexture("ButtonClickedCompteurInverse.png"),
                    sizeButton, sf::Vector2f(window.getSize().x / 3.0f, window.getSize().y / 2.0f), compteurs[1])); 

                // changement d'ecran
                buttons.push_back(new BoolButton(
                    &AssetManager::GetTexture("CadreBouton.png"),
                    &AssetManager::GetTexture("CadreBouton.png"),
                    "Start", 32, sf::Vector2f(130, 80), sf::Vector2f(window.getSize().x / 2.5f, (window.getSize().y * 0.8f)), goToGame));

                canGen = false;
            }

            /* ecran de jeu */
            if (showGame)
            {
                //creation de la map et des spawns
                musicGame.play();
                musicOpen.stop();
                ClearVector(&labels);
                ClearVector(&buttons);
                MapGenerator::SPGen(compteurs[0]->GetValue(), compteurs[1]->GetValue() ,&spawnPoints);
                MapGenerator::PlayerGen(compteurs[0]->GetValue(), compteurs[1]->GetValue(), &players, equipes, spawnPoints);
                MapGenerator::MapRand(&platformes);
                ClearVector(&compteurs);
                mainPlayer = players[mainPlayernbre];

                // interface timer
                sf::Vector2f* timerPosition =  new sf::Vector2f(window.getSize().x * 5.0f / 100.0f, window.getSize().y * 90.0f / 100.0f);
                images.push_back( new Image(&AssetManager::GetTexture("CadreUI.png"), *timerPosition, sf::Vector2f(60, 60))); //Fond du Timer
                compteurs.push_back(new Compteur(*timerPosition - sf::Vector2f(8,15), 0, maxTime, 0, 32, sf::Color::Blue)); //Timer temps restant

                /* interface de jeu */
                //message de debut de round
                labels.push_back( new Label(sf::Vector2f(window.getSize().x / 3.0f, window.getSize().y / 2.0f), "Appuyer sur \"Enter\" pour jouer", 64, sf::Color::White)); 

                //Fond de l'inventaire
                images.push_back(new Image(&AssetManager::GetTexture("CadreBouton.png"), sf::Vector2f(float(window.getSize().x), float(window.getSize().y)) * 0.45f,
                    sf::Vector2f(float(window.getSize().x), float(window.getSize().y)) * 0.9f));

                // Button Inventaire
                buttons.push_back(new BoolButton(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture("CadreBouton.png"), "Inventaire", 32,
                    sf::Vector2f(240, 80), sf::Vector2f(window.getSize().x - 240.0f, 0), goToInventaire)); 

                //Fond de Pause
                images.push_back(new Image(&AssetManager::GetTexture("CadreBouton.png"), sf::Vector2f(float(window.getSize().x), float(window.getSize().y)) * 0.45f,
                    sf::Vector2f(window.getSize().x*1.5f, window.getSize().y*1.5f)));

                //Button Pause
                buttons.push_back(new BoolButton(&AssetManager::GetTexture("CadreBoutonPause.png"), &AssetManager::GetTexture("CadreBoutonPause.png"), "", 32,
                    sf::Vector2f(128, 128), sf::Vector2f(window.getSize().x - 240.0f, 100), goToPause)); 

                std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                cptCI = 0;

                // boucle parmi les cases de l'inventaire
                for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                {
                    casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                        sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase*cptCI, 0), it->first));
                    casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                    cptCI++;
                }

                viseur->setSize(sf::Vector2f(96, 32));
                viseur->setOrigin(sf::Vector2f(0, mainPlayer->GetSize().y / 2));

                canGen = false;
                doneGen = true;
            }

            // Generation "GameOver"
            if (showGameOver)
            { 
                musicGame.stop();
                ClearVector(&players);
                ClearVector(&platformes);
                ClearVector(&equipes);
                ClearVector(&buttons);
                ClearVector(&images);
                ClearVector(&casesInventaire);
                ClearVector(&compteurs);
                ClearVector(&labels);
                ClearVector(&spawnPoints);
                ClearVector(&mines);

                labels.push_back(new Label(sf::Vector2f(window.getSize().x / 3.0f, window.getSize().y / 2.0f), "l'Equipe " + winner + " a gagne !", 64, sf::Color::White)); //message de victoire
                buttons.push_back(
                    new BoolButton(
                        &AssetManager::GetTexture("CadreBouton.png"),
                        &AssetManager::GetTexture("CadreBouton.png"),
                        "Revenir au menu",
                        32,
                        sf::Vector2f(300, 70),
                        sf::Vector2f(window.getSize().x / 2.5f,
                            (window.getSize().y / 1.4f) - 10.0f),
                        goToMenu));
                canGen = false;
                doneGen = true;
            }
        }
       
//-------------------------------------------------------------------------
        /* Gestion interface "Menu/Parametres" */
//-------------------------------------------------------------------------

        if (showMenu || showParametres || showGameOver)
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed: // fermeture de la fenetre
                    window.close();
                    break;

                case sf::Event::EventType::MouseButtonPressed: // pression sur un bouton
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        for (Button* button : buttons)
                        {
                            if (button->checkClicked(sf::Mouse::getPosition(window), true))
                            {
                                switch (button->GetType())
                                {
                                case 1:
                                    button->Add();
                                    break;
                                case -1:
                                    button->Minus();
                                    break;
                                case 2:
                                    button->Swap();
                                    break;
                                }
                            }

                        }
                    }
                    break;
                case sf::Event::EventType::MouseButtonReleased: // relache un bouton
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        for (Button* button : buttons)
                        {
                            button->checkClicked(sf::Mouse::getPosition(window), false);
                        }
                    }
                    break;
                };
            }
        } 

        //Gestion interaction player + interface "Game"
        if (showGame && doneGen && !pause)

        {
            deltaTime = clockDeltaTime.restart().asSeconds();

            compteurs[0]->SetValue(maxTime - int(clockTimer.getElapsedTime().asSeconds()));
            if (compteurs[0]->GetValue() <= 0 && readyToPlay && canChange)
            {
#pragma region SwapPlayer
                //Swap Player
                mainPlayernbre++;
                if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                mainPlayer->SetMovement(false);
                mainPlayer = players[mainPlayernbre];
                clockTimer.restart().asSeconds();
                readyToPlay = false;
                showReady = true;
                canChange = false;
                showViseur = false;
                viseur->setRotation(0);
                MapGenerator::CaisseGen(&caisses);
                ClearVector(&casesInventaire);
                std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                int cptCI = 0;
                for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                {
                    casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                        sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                    casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                    cptCI++;
                }
#pragma endregion
            }


            if (deltaTime > 1 / 20.0f) deltaTime = 1 / 20.0f; //bug de la fenetre

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
                    case sf::Keyboard::Enter: //SWAP Player test
                        if (!readyToPlay)
                        {
                            readyToPlay = true;
                            showReady = false;
                            canChange = true;
                            mainPlayer->SetMovement(true);
                            clockTimer.restart().asSeconds();
                        }
                        break;
                    case sf::Keyboard::Up:
                        if (viseur->getRotation() <= 90 || viseur->getRotation() >= 270)viseur->rotate(200 * -deltaTime);
                        else viseur->setRotation(272);
                        break;
                    case sf::Keyboard::Down:
                        if (viseur->getRotation() <= 90 || viseur->getRotation() >= 270)viseur->rotate(200 * deltaTime);
                        else viseur->setRotation(89);
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
                    case sf::Keyboard::F:
                        if (showViseur)
                        {
                            isPressed = false;
                            if (selectedWeapon == "Bazooka")
                            {
                                if (mainPlayer->Shoot("Bazooka"))
                                {
                                    float theta = viseur->getRotation() * 3.1416f / 180;
                                    sf::Vector2f angle = sf::Vector2f(cosf(theta), sinf(theta));
                                    float power = float(PowerTimer.getElapsedTime().asMilliseconds());
                                    if (!mainPlayer->IsFaceRight())
                                    {
                                        angle = -angle;
                                        missiles.push_back(new Missile(&AssetManager::GetTexture("missile.png"), sf::Vector2f(13, 24),
                                            mainPlayer->GetPosition() - sf::Vector2f(mainPlayer->GetSize().x, mainPlayer->GetSize().y / 2), 50, angle, power));
                                    }
                                    else
                                    {
                                        missiles.push_back(new Missile(&AssetManager::GetTexture("missile.png"), sf::Vector2f(13, 24),
                                            mainPlayer->GetPosition() + sf::Vector2f(mainPlayer->GetSize().x, -mainPlayer->GetSize().y / 2), 50, angle, power));
                                    }
                                    soundBazooka.play();
                                }                         
                            }
                            else if (selectedWeapon == "Grenade")
                            {
                                if (mainPlayer->Shoot("Grenade"))
                                {
                                    float theta = viseur->getRotation() * 3.1416f / 180;
                                    sf::Vector2f angle = sf::Vector2f(cosf(theta), sinf(theta));
                                    float power = float(PowerTimer.getElapsedTime().asMilliseconds());
                                    if (!mainPlayer->IsFaceRight())
                                    {
                                        angle = -angle;
                                        grenades.push_back(new Grenade(&AssetManager::GetTexture("Grenade.png"), sf::Vector2f(16, 16),
                                            mainPlayer->GetPosition() - sf::Vector2f(mainPlayer->GetSize().x, mainPlayer->GetSize().y / 2), 120, angle, power, 5));
                                    }
                                    else
                                    {
                                        grenades.push_back(new Grenade(&AssetManager::GetTexture("Grenade.png"), sf::Vector2f(16, 16),
                                            mainPlayer->GetPosition() + sf::Vector2f(mainPlayer->GetSize().x, -mainPlayer->GetSize().y / 2), 120, angle, power, 5));
                                    }
                                    soundGrenade.play();
                                }
                            }
                            else if (selectedWeapon == "Mine")
                            {
                                if (mainPlayer->Shoot("Mine")) {
                                    mines.push_back(new Mine(&AssetManager::GetTexture("Mine.png"), sf::Vector2f(16, 8), mainPlayer->GetPosition(), 85, 60, 3, 4));
                                }
                                

                                ClearVector(&casesInventaire);
                                std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                                int cptCI = 0;
                                for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                                {
                                    casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                        sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                                    casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                                    cptCI++;
                                }
                            }
                            else if (selectedWeapon == "Awp")
                            {
                                if (mainPlayer->Shoot("Awp"))
                                {         
                                    sf::Vector2f position;
                                    float theta = viseur->getRotation() * 3.1416f / 180;
                                    sf::Vector2f angle = sf::Vector2f(cos(theta), sin(theta));
                                    if (mainPlayer->IsFaceRight())position = mainPlayer->GetPosition() + sf::Vector2f(mainPlayer->GetSize().x + 2, 0);
                                    else
                                    {
                                        angle = -angle;
                                        position = mainPlayer->GetPosition() + sf::Vector2f(-mainPlayer->GetSize().x + 2, 0);
                                    }
                                    balles.push_back(new Balle(position, angle));
                                    soundAwp.play();
                                }
                            }
                            showViseur = false;
                            viseur->setRotation(0);
                        }
                    }
                    break;

                case sf::Event::EventType::MouseButtonPressed:
                    switch (event.mouseButton.button)
                    {
                    case sf::Mouse::Left:
                        if (readyToPlay)
                        {
                            for (Button* button : buttons)
                            {
                                if (button->checkClicked(sf::Mouse::getPosition(window), true))
                                {
                                    button->Swap();
                                }
                            }

                            for (CaseInventaire* CI : casesInventaire)
                            {
                                if (CI->checkClicked(sf::Mouse::getPosition(window)))
                                {
                                    selectedWeapon = *CI->GetType();
                                    showInventaire = false;
                                    viseur->setTexture(&AssetManager::GetTexture(*CI->GetType() + ".png"));
                                    if (mainPlayer->IsFaceRight())viseur->setScale(sf::Vector2f(1, 1));
                                    else viseur->setScale(sf::Vector2f(-1, 1));
                                    viseur->setPosition(mainPlayer->GetPosition());
                                    showViseur = true;
                                }
                            }
                        }    
                        break;
                    }
                    break;            
                }
            }
        }
    
        //update + CheckCollision "Game"
        if (showGame && doneGen && !pause) 
        {

#pragma region Update des entites

            for (Player* player : players)
            {
                player->Update(deltaTime,&showViseur);
            }

            for (Missile* missile : missiles)
            {
                missile->Update(deltaTime);
            }
            int cptG = 0;
            for (Grenade* grenade : grenades)
            {
                grenade->Update(deltaTime);
                if (grenade->isTimeOut())
                {
                    Collider exploCol = grenade->GetExploCollider();
                    soundExplosion.play();

                    for (int i = 0; i < 7; i++)
                    {
                        cptE = 0;
                        for (Platforme* platforme : platformes)
                        {
                            if (platforme->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
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
                        if (player->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
                        {
                            if (player->TakeDamage(grenade->GetDamage()))
                            {
                                delete player;
                                players.erase(players.begin() + cptPl);
                            }
                            soundHit.play();
                        }
                        cptPl++;
                    }

                    if (!CheckPlayerAlive(players, &showGame, &showGameOver, &canGen, &doneGen, &winner))
                    {
#pragma region SwapPlayer
                        //Swap Player
                        mainPlayernbre++;
                        if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                        SwapMainPlayer(mainPlayer, players[mainPlayernbre]);
                        mainPlayer = players[mainPlayernbre];
                        clockTimer.restart().asSeconds();
                        readyToPlay = false;
                        showReady = true;
                        canChange = false;
                        showViseur = false;
                        viseur->setRotation(0);
                        MapGenerator::CaisseGen(&caisses);
                        ClearVector(&casesInventaire);
                        std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                        int cptCI = 0;
                        for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                        {
                            casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                            casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                            cptCI++;
                        }
#pragma endregion             
                    }
                    delete(grenade);
                    grenades.erase(grenades.begin() + cptG);

                }
                cptG++;
            }
            cptMine = 0;
            for (Mine* mine : mines)
            {
                mine->Update(deltaTime);

                if (mine->isTimeOut())
                {
                    Collider exploCol = mine->GetExploCollider();
                    soundExplosion.play();

                    for (int i = 0; i < 7; i++)
                    {
                        cptE = 0;
                        for (Platforme* platforme : platformes)
                        {
                            if (platforme->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
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
                        if (player->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
                        {
                            if (player->TakeDamage(mine->GetDamage()))
                            {
                                delete player;
                                players.erase(players.begin() + cptPl);
                            }
                            soundHit.play();
                        }
                        cptPl++;
                    }

                    if (!CheckPlayerAlive(players, &showGame, &showGameOver, &canGen, &doneGen, &winner))
                    {
#pragma region SwapPlayer
                        //Swap Player
                        mainPlayernbre++;
                        if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                        SwapMainPlayer(mainPlayer, players[mainPlayernbre]);
                        mainPlayer = players[mainPlayernbre];
                        clockTimer.restart().asSeconds();
                        readyToPlay = false;
                        showReady = true;
                        canChange = false;
                        showViseur = false;
                        viseur->setRotation(0);
                        MapGenerator::CaisseGen(&caisses);
                        ClearVector(&casesInventaire);
                        std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                        int cptCI = 0;
                        for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                        {
                            casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                            casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                            cptCI++;
                        }
#pragma endregion             
                    }
                    delete(mine);
                    mines.erase(mines.begin() + cptMine);
                }
                cptM++;
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

            // !!!!!!!!!!!!! NETTOYER LES COLLISIONS AVEC DES POINTEURS + "FOR" pour retirer les pointeurs

            cptPl = 0;
            for (Player* player : players)
            {
                cptMine = 0;

                for (Mine* mine : mines)
                {
                    Collider mineDetectionCol = mine->GetDetectionCollider();
                    if (player->GetCollider().CheckCollisionCircle(&mineDetectionCol, int(mineDetectionCol.GetHalfSizeCircle().x)))
                    {
                        if (!mine->isDetected() && mine->isActivated())
                        {
                            mine->Detect();
                            soundMine.play();
                        }        
                    }
                }

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
                            
                        }
                        soundHit.play();
                        delete(balle);
                        balles.erase(balles.begin() + cptT);

                        if (!CheckPlayerAlive(players, &showGame, &showGameOver,&canGen,&doneGen,&winner))
                        {
                            std::cout << "Swap1" << std::endl;
#pragma region SwapPlayer
                            //Swap Player
                            mainPlayernbre++;
                            if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                            SwapMainPlayer(mainPlayer, players[mainPlayernbre]);
                            mainPlayer = players[mainPlayernbre];
                            clockTimer.restart().asSeconds();
                            readyToPlay = false;
                            showReady = true;
                            canChange = false;
                            showViseur = false;
                            viseur->setRotation(0);
                            MapGenerator::CaisseGen(&caisses);
                            ClearVector(&casesInventaire);
                            std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                            int cptCI = 0;
                            for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                            {
                                casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                    sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                                casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                                cptCI++;
                            }
#pragma endregion
                        }

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
                        soundExplosion.play();

                        for (int i = 0; i < 7; i++)
                        {
                            cptE = 0;
                            for (Platforme* platforme : platformes)
                            {
                                if (platforme->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
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
                            if (player->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
                                if (player->TakeDamage(missile->GetDamage()))
                                {
                                    delete player;
                                    players.erase(players.begin() + cptPl);

                                }
                            soundHit.play();
                            cptPl++;
                        }

                        delete(missile);
                        missiles.erase(missiles.begin() + cptM);

                        if (!CheckPlayerAlive(players, &showGame, &showGameOver, &canGen, &doneGen, &winner))
                        {
#pragma region SwapPlayer
                            //Swap Player
                            mainPlayernbre++;
                            if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                            SwapMainPlayer(mainPlayer, players[mainPlayernbre]);
                            mainPlayer = players[mainPlayernbre];
                            clockTimer.restart().asSeconds();
                            readyToPlay = false;
                            showReady = true;
                            canChange = false;
                            showViseur = false;
                            viseur->setRotation(0);
                            MapGenerator::CaisseGen(&caisses);
                            ClearVector(&casesInventaire);
                            std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                            int cptCI = 0;
                            for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                            {
                                casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                    sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                                casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                                cptCI++;
                            }
#pragma endregion
                        }
                        
                    }
                    cptM++;
                }

                cptPl++;
            }


            cptP = 0;
            for (Platforme* platforme : platformes)
            {
                cptPl = 0;
                for (Player* player : players) //CHECK DES PLAYERS / SOL
                {
                    Collider playerCol = player->GetCollider();

                    if (platforme->GetCollider().CheckCollision(&playerCol, &direction, 1.0f)) // UNIQUEMENT PLAYER
                    {
                        if (platforme->GetLayer() == 2) //DESTRUCTION EN FCT DU LAYER
                        {
                            player->Oncollision(direction);
                            delete(platforme);
                            platformes.erase(platformes.begin() + cptP);
                        }
                        else if (platforme->GetLayer() == 3) //Case eau
                        {
                            if (player->TakeDamage(999))
                            {
                                delete player;
                                players.erase(players.begin() + cptPl);
                            }
                            if (!CheckPlayerAlive(players, &showGame, &showGameOver, &canGen, &doneGen, &winner))
                            break;
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

                        soundExplosion.play();

                        for (int i = 0; i < 7; i++)
                        {
                            cptE = 0;
                            for (Platforme* platforme : platformes)
                            {
                                if (platforme->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
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
                            if (player->GetCollider().CheckCollisionCircle(&exploCol, int(exploCol.GetHalfSizeCircle().x)))
                            {
                                if (player->TakeDamage(missile->GetDamage()))
                                {
                                    delete player;
                                    players.erase(players.begin() + cptPl);                                                             
                                }      
                                soundHit.play();
                            }
                            cptPl++;
                        }
                        
                        delete(missile);
                        missiles.erase(missiles.begin() + cptM);

                        if (!CheckPlayerAlive(players, &showGame, &showGameOver, &canGen, &doneGen, &winner))
                        {
#pragma region SwapPlayer
                            //Swap Player
                            mainPlayernbre++;
                            if (mainPlayernbre > players.size() - 1) mainPlayernbre = 0;
                            SwapMainPlayer(mainPlayer, players[mainPlayernbre]);
                            mainPlayer = players[mainPlayernbre];
                            clockTimer.restart().asSeconds();
                            readyToPlay = false;
                            showReady = true;
                            canChange = false;
                            showViseur = false;
                            viseur->setRotation(0);
                            MapGenerator::CaisseGen(&caisses);
                            ClearVector(&casesInventaire);
                            std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                            int cptCI = 0;
                            for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                            {
                                casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                    sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                                casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                                cptCI++;
                            }
#pragma endregion             
                        }                 
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

                for (Grenade* grenade : grenades)
                {
                    Collider grenadeCol = grenade->GetCollider();
                    if (platforme->GetCollider().CheckCollision(&grenadeCol, &direction, 1.0f)) {
                        grenade->Oncollision(direction);
                    }
                }
                for (Mine* mine : mines)
                {
                    Collider mineCol = mine->GetCollider();
                    if (platforme->GetCollider().CheckCollision(&mineCol, &direction, 1.0f)) {
                        mine->Oncollision(direction);
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
                            ClearVector(&casesInventaire);
                            std::map<std::string, int> inventaire = mainPlayer->GetEquipe()->GetInventaire()->GetAllMunitions(); //generation des cases de l'inventaire
                            int cptCI = 0;
                            for (std::map<std::string, int>::iterator it = inventaire.begin(); it != inventaire.end(); it++)
                            {
                                casesInventaire.push_back(new CaseInventaire(&AssetManager::GetTexture("CadreBouton.png"), &AssetManager::GetTexture(it->first + ".png"),
                                    sf::Vector2f(100, 100), sf::Vector2f(sizeCase, sizeCase) + sf::Vector2f(sizeCase * cptCI, 0), it->first));
                                casesInventaire[cptCI]->GetCompteur()->SetValue(it->second);
                                cptCI++;
                            }
                            soundAmmo.play();
                        }
                        else if (caisse->GetTypeCaisse() == 2)
                        {
                            player->RecoverLife(caisse->GetNbreHeal());
                            delete(caisse);
                            caisses.erase(caisses.begin() + cptC);
                            soundHeal.play();
                        }

                    }
                }
                cptC++;
            }

#pragma endregion
            
        }

#pragma region Camera + Affichage 

        window.clear();

        if (showMenu)
        {
            window.setView(Uiview);

            for (Button* button : buttons)
            {
                button->Draw(window);
            }
        }

        if (showParametres)
        {
            window.setView(Uiview);
            for (Button* button : buttons)
            {
                button->Draw(window);
            }

            for (Compteur* compteur : compteurs)
            {
                compteur->Draw(window);
            }

            for (Label* label : labels)
            {
                label->Draw(window);
            }
        }

        //GameView
        if (showGame && doneGen)
        {       
            sf::Listener::setPosition(mainPlayer->GetPosition().x, mainPlayer->GetPosition().y, 0);
            view.setCenter(mainPlayer->GetPosition());
            window.setView(view);

            if (showViseur) window.draw(*viseur);
            for (Player* player : players)
            {
                player->Draw(window);
            }

            for (Missile* missile : missiles)
            {
                missile->Draw(window);
            }

            for (Grenade* grenade : grenades)
            {
                grenade->Draw(window);
            }

            for (Mine* mine : mines)
            {
                mine->Draw(window);
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

            //Timer
            images[0]->Draw(window); 
            compteurs[0]->Draw(window);

            buttons[0]->Draw(window); //button inventaire           

            if (showInventaire) {

                images[1]->Draw(window);
                for (CaseInventaire* CI : casesInventaire)
                {
                    CI->Draw(window);
                }
            }
            if (showReady)labels[0]->Draw(window);
            //if (pause)images[2]->Draw(window); //Fond de pause
            //buttons[1]->Draw(window); // Pause
        } 

        if (showGameOver && doneGen)
        {
            labels[0]->Draw(window);
            buttons[0]->Draw(window);
        }

        window.display();

#pragma endregion
    
    }
        
#pragma region Cleaning
    ClearVector(&platformes);
    ClearVector(&missiles);
    ClearVector(&players);
    ClearVector(&caisses);
    ClearVector(&equipes);
    ClearVector(&buttons);
    ClearVector(&casesInventaire);
    ClearVector(&compteurs);
    ClearVector(&images);
    ClearVector(&labels);
    ClearVector(&grenades);
    ClearVector(&mines);

    delete(viseur);
#pragma endregion

    return 0;
}

template<class T>
void ClearVector(std::vector<T*>* vect)
{
    for (T* element : *vect)
    {
        delete element;
    }
    vect->clear();
}

void SwapMainPlayer(Player* actual, Player* next)
{
    actual->SetMovement(false);
}

bool CheckPlayerAlive(std::vector<Player*> players,bool* game,bool* over,bool* canGen, bool* doneGen, std::string* winner) {
    if (players.size() == 1)
    {
        *winner = *players[0]->GetEquipe()->GetNom();
        *game = false;
        *over = true;
        *canGen = true;
        *doneGen = false;
        return true;
    }
    else if (players.size() == 0) {
        
        *winner = "Personne";
        *game = false;
        *over = true;
        *canGen = true;
        *doneGen = false;
        return true;
    }

    for (unsigned int i = 0; i < players.size() - 1; i++)
    {
        if (*players[i]->GetEquipe() != *players[i + 1]->GetEquipe()) {
            break;
        }
        
        if (i == players.size() - 2)
        {
            if (*players[i]->GetEquipe()->GetTagEquipe() != *players[i + 1]->GetEquipe()->GetTagEquipe()) {
                return false;
            }

            if (i == players.size() - 2)
            {
                *winner = *players[i]->GetEquipe()->GetNom();
                *game = false;
                *over = true;
                *canGen = true;
                *doneGen = false;
                return true;
            }
        }
    }

    return false;
}