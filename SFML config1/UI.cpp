#include "UI.h"

Compteur::Compteur(sf::Font* font,sf::Vector2f position, int value)
{
	this->value = value;

	text.setPosition(position);	
	text.setFont(*font);
	text.setString(std::to_string(value));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Blue);
	
}

Compteur::~Compteur()
{
}

void Compteur::SetValue(int value)
{
	this->value = value;
	SetText();
}


