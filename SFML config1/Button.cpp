#include "GUI.h"

Button::Button(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f scale, sf::Vector2f position)
{

	this->normal.setTexture(normal);
	this->clicked.setTexture(clicked);
	this->text = text;
	state = false;

	this->normal.setScale(scale);
	this->clicked.setScale(scale);

	this->normal.setPosition(position);
	this->clicked.setPosition(position);

	text.setString(content);
	text.setPosition(position);
}

Button::~Button()
{
}

void Button::checkClicked(sf::Vector2f mousePos)
{
	if (mousePos.x > currentSprite->getPosition().x && mousePos.x < (currentSprite->getPosition().x + currentSprite->getSize().x)) {
		if (mousePos.y > currentSprite->getPosition().y && mousePos.y < (currentSprite->getPosition().y + currentSprite->getSize().y)) {
			setState(!state);
		}
	}
}


void Button::setText(std::string content)
{
	text.setString(content);
}


AddButton::AddButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f scale, sf::Vector2f position, Compteur* compteur) :
	Button(normal, clicked, content, scale, position)
{
	this->compteur = compteur;
}

AddButton::~AddButton()
{
	
}

void AddButton::Add()
{
	compteur->SetValue(compteur->GetValue() + 1);
}

MinusButton::MinusButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f scale, sf::Vector2f position, Compteur* compteur) :
	Button(normal, clicked, content, scale, position)
{
	this->compteur = compteur;
}

MinusButton::~MinusButton()
{

}

void MinusButton::Minus()
{
	if (compteur->GetValue() - 1 < 0)compteur->SetValue(0);
	else compteur->SetValue(compteur->GetValue() - 1);

	
}
