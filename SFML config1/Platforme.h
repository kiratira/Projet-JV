#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>
class Platforme
{
public:
	Platforme(const std::string img, sf::Vector2f size, sf::Vector2f position,unsigned int layer);
	~Platforme();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(&body); }
	unsigned int GetLayer() { return layer; }


private:
	sf::RectangleShape body;
	unsigned int layer;
};

