#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class UI
{

};

class Compteur 
{
public:
	Compteur(sf::Vector2f position, int value, int maxValue, int minValue, int fontSize, sf::Color color);
	~Compteur();

	void SetValue(int value);
	void Draw(sf::RenderWindow& window) { window.draw(text); }
	void SetPosition(sf::Vector2f position) { text.setPosition(position); }

	int GetValue() { return value; }
	sf::Text GetText() { return text; }


private:

	void SetText() { this->text.setString(std::to_string(value)); }

private:
	sf::Text text;
	int value;
	int maxValue;
	int minValue;

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
	Label(sf::Vector2f position, std::string content, int fontSize, sf::Color color);
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
	Button(sf::Texture* normal, sf::Texture* clicked, std::string content, int fontSize, sf::Vector2f size, sf::Vector2f position, int type);
	~Button();

	bool checkClicked(sf::Vector2i mousePos, bool state);
	void setState(bool state);
	void setText(std::string content);
	void Draw(sf::RenderWindow& window) { window.draw(*currentSprite); window.draw(text); };
	void SetRotation(float rotation) { normal.setRotation(rotation); clicked.setRotation(rotation); }

	bool getState() { return state; }
	sf::RectangleShape* GetSprite() { return currentSprite; }
	sf::Text* GetText() { return &text; }
	int GetType() { return type; }

	virtual void Add();
	virtual void Minus();
	virtual void Swap();


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
	AddButton(sf::Texture* normal, sf::Texture* clicked, sf::Vector2f size, sf::Vector2f position, Compteur* compteur);
	~AddButton();

	void Add();

private:
	Compteur* compteur;
};

class MinusButton : public Button
{
public:
	MinusButton(sf::Texture* normal, sf::Texture* clicked, sf::Vector2f size, sf::Vector2f position, Compteur* compteur);
	~MinusButton();

	void Minus();

private:
	Compteur* compteur;
};

class BoolButton : public Button
{
public:
	BoolButton(sf::Texture* normal, sf::Texture* clicked, std::string content,int fontSize, sf::Vector2f size, sf::Vector2f position, std::vector<bool*> vect);
	~BoolButton();

	void Swap();

private:
	std::vector<bool*> vect;
};

class CaseInventaire 
{
public:
	CaseInventaire(sf::Texture* back, sf::Texture* image, sf::Vector2f size, sf::Vector2f position, std::string type);
	~CaseInventaire();

	void Draw(sf::RenderWindow& window);

	bool checkClicked(sf::Vector2i mousePos);
	std::string* GetType() { return &type; }
	Compteur* GetCompteur() { return &nbre; }

private:
	sf::RectangleShape back;
	sf::RectangleShape image;
	Compteur nbre;
	std::string type;
};
