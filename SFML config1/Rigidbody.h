#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Rigidbody
{
public:
	Rigidbody(sf::RectangleShape* body);
	~Rigidbody();

	sf::Vector2f GetPosition() { return body->getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape* body;
};

