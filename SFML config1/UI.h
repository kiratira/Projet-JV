#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class UI
{

};

class Compteur 
{
public:
	Compteur(sf::Font* font, sf::Vector2f position, int value, int fontSize, sf::Color color);
	~Compteur();

	void SetValue(int value);
	void Draw(sf::RenderWindow& window) { window.draw(text); }

	int GetValue() { return value; }
	sf::Text GetText() { return text; }


private:

	void SetText() { this->text.setString(std::to_string(value)); }

private:
	sf::Text text;
	int value;

};

class Image
{
public:
	Image(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	~Image();

	void Draw(sf::RenderWindow& window) { window.draw(body); }

private:
	sf::RectangleShape body;
};

//TOTALEMENT UN sf::TEXT XD
class Label
{
public:
	Label(sf::Font* font, sf::Vector2f position, std::string content, int fontSize, sf::Color color);
	~Label();

	void Draw(sf::RenderWindow& window) { window.draw(text); }
	void SetText(std::string content) { text.setString(content); }

private:
	sf::Text text;
};


class Button
{
public:
	Button(sf::Texture* normal, sf::Texture* clicked, sf::Vector2f size, sf::Vector2f position, int type);
	Button(sf::Texture* normal, sf::Texture* clicked,sf::Font* font, std::string content, int fontSize, sf::Vector2f size, sf::Vector2f position, int type);
	~Button();

	bool checkClicked(sf::Vector2i mousePos, bool state);
	void setState(bool state);
	void setText(std::string content);
	void Draw(sf::RenderWindow& window) { window.draw(*currentSprite); window.draw(text); };

	bool getState() { return state; }
	sf::RectangleShape* GetSprite() { return currentSprite; }
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
	AddButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f size, sf::Vector2f position, Compteur* compteur);
	~AddButton();

	void Add();

private:
	Compteur* compteur;
};

class MinusButton : public Button
{
public:
	MinusButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f size, sf::Vector2f position, Compteur* compteur);
	~MinusButton();

	void Minus();

private:
	Compteur* compteur;
};

class CaseInventaire
{
public:
	CaseInventaire(sf::Texture* back, sf::Texture* image, sf::Font* font, sf::Vector2f size, sf::Vector2f position);
	~CaseInventaire();

	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape back;
	sf::RectangleShape image;
	Compteur nbre;
};
