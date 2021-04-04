#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Caisse
{
public:
	Caisse(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint);
	~Caisse();

	Collider GetCollider() { return Collider(&body); }


	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Oncollision(sf::Vector2f direction);

	
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
};


class CaisseMunition : public Caisse
{
public:
	CaisseMunition(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, std::string type, int nbre);
	~CaisseMunition();

	std::string GetType() { return type; }
	int GetNbre() { return nbre; }


private:

	std::string type;
	int nbre;

};



class CaisseHeal : public Caisse
{
public:
	CaisseHeal(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, int nbre);
	~CaisseHeal();

	int GetNbre() { return nbre; }

private:

	int nbre;

};

