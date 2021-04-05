#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Caisse
{
public:
	Caisse(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint,int type);
	~Caisse();

	Collider GetCollider() { return Collider(&body); }


	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Oncollision(sf::Vector2f direction);

	int GetTypeCaisse() { return typeCaisse; }

	virtual std::string GetTypeMunition();
	virtual int GetNbreMunition();
	virtual int GetNbreHeal();

	
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	int typeCaisse = 0; // 1 = Munition / 2 = Heal 
};


class CaisseMunition : public Caisse
{
public:
	CaisseMunition(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, std::string type, int nbre);
	~CaisseMunition();

	std::string GetTypeMunition() { return typeMunition; }
	int GetNbreMunition() { return nbre; }


private:

	std::string typeMunition;
	int nbre;

};



class CaisseHeal : public Caisse
{
public:
	CaisseHeal(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, int nbre);
	~CaisseHeal();

	int GetNbreHeal() { return nbre; }

private:

	int nbre;

};

