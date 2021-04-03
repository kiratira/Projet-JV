#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>

class Missile
{
public:

	Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo , sf::Vector2f angle, float power);
	~Missile();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void DrawExplosion(sf::RenderWindow& window);

	Collider GetCollider() { return Collider(&body); }
	Collider GetExploCollider() { return Collider(&explosion); }
	sf::Vector2f GetPosition() { return body.getPosition(); }


private:

	sf::RectangleShape body;
	sf::CircleShape explosion;
	sf::Vector2f velocity;
	sf::Vector2f angle;
	float power;
};

