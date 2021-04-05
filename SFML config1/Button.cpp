#include "Button.h"

Button::Button(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f size, sf::Vector2f position, int type)
{
	this->type = type;
	this->normal.setTexture(normal);
	this->clicked.setTexture(clicked);
	this->text = text;
	state = false;

	this->normal.setSize(size);
	this->clicked.setSize(size);

	this->normal.setPosition(position);
	this->clicked.setPosition(position);

	text.setString(content);
	text.setPosition(position);

	currentSprite = &this->normal;

}

Button::~Button()
{
}

bool Button::checkClicked(sf::Vector2i mousePos, bool state)
{
	if (mousePos.x > currentSprite->getPosition().x && mousePos.x < (currentSprite->getPosition().x + currentSprite->getSize().x)) {
		if (mousePos.y > currentSprite->getPosition().y && mousePos.y < (currentSprite->getPosition().y + currentSprite->getSize().y)) {
			setState(state);
			return true;
		}
	}
	return false;
}

void Button::setState(bool state)
{
	this->state = state;
	if (this->state) currentSprite = &clicked;
	else currentSprite = &normal;
}


void Button::setText(std::string content)
{
	text.setString(content);
}

void Button::Add()
{
}

void Button::Minus()
{
}


AddButton::AddButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f size, sf::Vector2f position, Compteur* compteur) :
	Button(normal, clicked, content, size, position,1)
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
	Button(normal, clicked, content, scale, position,-1)
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
