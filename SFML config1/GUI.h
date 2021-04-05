#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"
#include "Player.h"
#include "Platforme.h"
#include "Caisse.h"
#include "Missile.h"

class GUI
{
public:
	GUI();
	~GUI();

	static std::vector<Player*>* GetPlayers() { return &players; }
	static std::vector<Platforme*>* GetPlatforme() { return &platformes; }
	static std::vector<Caisse*>* GetCaisse() { return &caisses; }
	static std::vector<Missile*>* GetMissile() { return &missiles; }
	static std::vector<UI*>* GetUI() { return &ui; }

private:
	static std::vector<Player*> players;
	static std::vector<Platforme*> platformes;
	static std::vector<Caisse*> caisses;
	static std::vector<Missile*> missiles;
	static std::vector<UI*> ui;

	static GUI* sInstance;

};

