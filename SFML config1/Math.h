#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public:
	
	static float GetAngleVector(sf::Vector2f vect);
	static float GetSizeVector(sf::Vector2f vect) { return (float)(vect.x * vect.x + vect.y * vect.y); };

};

