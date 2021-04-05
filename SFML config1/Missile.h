#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collider.h"
#include "Math.h"

class Missile
{
public:

	Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo, sf::Vector2f angle, float power, int damage);
	~Missile();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void DrawExplosion(sf::RenderWindow& window);

	Collider GetCollider() { return Collider(&body); }
	Collider GetExploCollider() { return Collider(&explosion); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	int GetDamage() { return damage; }


private:

	sf::RectangleShape body;
	sf::CircleShape explosion;
	sf::Vector2f velocity;
	sf::Vector2f force;
	float power;
	int damage;
};

