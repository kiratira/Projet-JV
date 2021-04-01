#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
class Platforme
{
public:
	Platforme(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platforme();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }


private:
	sf::RectangleShape body;
};

