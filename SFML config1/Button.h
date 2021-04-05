#pragma once
#include <SFML/Graphics.hpp>
#include "Displayable.h"

class Button
{
public:
	Button(sf::Texture* normal, sf::Texture* clicked, std::string content,sf::Vector2f size, sf::Vector2f position);
	~Button();

	void checkClicked(sf::Vector2f mousePos);
	void setState(bool state) { this->state = state; };
	void setText(std::string content);

	bool getState() { return state; };
	sf::RectangleShape* GetSprite() { return currentSprite; };
	sf::Text* GetText() { return &text; }

private:
	sf::RectangleShape normal;
	sf::RectangleShape clicked;
	sf::RectangleShape* currentSprite;
	sf::Text text;
	bool state;
};


class AddButton : public Button
{
public:
	AddButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f scale, sf::Vector2f position, Compteur* compteur);
	~AddButton();

	void Add();

private:
	Compteur* compteur;
};

class MinusButton : public Button
{
public:
	MinusButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f scale, sf::Vector2f position, Compteur* compteur);
	~MinusButton();

	void Minus();

private:
	Compteur* compteur;
};
