#include "Displayable.h"

Compteur::Compteur(sf::Vector2f position, int value)
{
	text.setPosition(position);
	this->value = value;
}

Compteur::~Compteur()
{
}

void Compteur::SetValue(int value)
{
	this->value = value;
	SetText();
}


