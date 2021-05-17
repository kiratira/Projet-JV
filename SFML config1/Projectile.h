#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collider.h"
#include "Math.h"
#include "Rigidbody.h"
#include "AssetManager.h"


class Missile : public Rigidbody
{
public:

	Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo, sf::Vector2f angle, float power);
	~Missile();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void DrawExplosion(sf::RenderWindow& window);

	Collider GetExploCollider() { return Collider(&explosion); }
	int GetDamage() { return damage; }


private:

	sf::RectangleShape body;
	sf::CircleShape explosion;
	sf::Vector2f velocity;
	sf::Vector2f angle;
	float power;
	int damage = 50;
};


class Balle : public Rigidbody
{
public:
	Balle(sf::Vector2f spawnPoint, sf::Vector2f angle);
	~Balle();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	int GetDamage() { return damage; }

private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	sf::Vector2f angle;
	float power = 3000;
	int damage = 35;
};

class Grenade : public Rigidbody
{
public:
	Grenade(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo, sf::Vector2f angle, float power,float timeExplo);
	~Grenade();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void DrawExplosion(sf::RenderWindow& window);
	void Oncollision(sf::Vector2f direction);

	int GetDamage() {return damage;}
	bool isTimeOut();

private:
	sf::RectangleShape body;
	sf::CircleShape explosion;
	sf::Vector2f velocity;
	sf::Vector2f angle;
	float power;
	int damage = 60;
	float timeExplo;
	sf::Clock timer;
	sf::Text txtTimer;
};

