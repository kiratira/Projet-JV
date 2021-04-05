#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI.h"


class Button
{
public:
	Button(sf::Texture* normal, sf::Texture* clicked, std::string content,sf::Vector2f size, sf::Vector2f position,int type);
	~Button();

	bool checkClicked(sf::Vector2i mousePos, bool state);
	void setState(bool state);
	void setText(std::string content);
	void Draw(sf::RenderWindow& window) { window.draw(*currentSprite); };

	bool getState() { return state; };
	sf::RectangleShape* GetSprite() { return currentSprite; };
	sf::Text* GetText() { return &text; }
	int GetType() { return type; }

	virtual void Add();
	virtual void Minus();


private:
	sf::RectangleShape normal;
	sf::RectangleShape clicked;
	sf::RectangleShape* currentSprite;
	sf::Text text;
	bool state;
	int type; // 0 = Menu | 1 = AddButton |  -1 = MinusButton
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
