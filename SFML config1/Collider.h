#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Collider
{
public:
	Collider(sf::RectangleShape* body);
	Collider(sf::CircleShape* bodyC);
	~Collider();

	void Move(float dx, float dy) { body->move(dx, dy); }

	bool CheckCollision(Collider* other, sf::Vector2f* direction, float push);
	bool CheckCollision(Collider* other);
	bool CheckCollisionCircle(Collider* other,int radius);
	//rect
	sf::Vector2f GetPosition() { return body->getPosition(); }
	sf::Vector2f GetHalfSize() { return body->getSize() / 2.0f; }
	//circle
	sf::Vector2f GetPositionCircle() { return bodyC->getPosition(); }
	sf::Vector2f GetHalfSizeCircle() { return sf::Vector2f(bodyC->getRadius(), bodyC->getRadius()); }

private:
	
	sf::RectangleShape* body;
	sf::CircleShape* bodyC;

	
};

