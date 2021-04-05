#pragma once
#include <SFML/Graphics.hpp>

class Displayable
{

};

class Compteur 
{
public:
	Compteur(sf::Vector2f position, int value);
	~Compteur();

	void SetValue(int value);
	void Draw(sf::RenderWindow& window) { window.draw(text); };

	int GetValue() { return value; };


private:

	void SetText() { this->text.setString(std::to_string(value)); };

private:
	sf::Text text;
	int value;

};

