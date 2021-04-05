#include "UI.h"

Compteur::Compteur(sf::Font* font,sf::Vector2f position, int value, int fontSize, sf::Color color)
{
	this->value = value;

	
	text.setPosition(position);
	text.setFont(*font);
	text.setString(std::to_string(value));
	text.setCharacterSize(fontSize);
	text.setFillColor(color);
	
}

Compteur::~Compteur()
{
}

void Compteur::SetValue(int value)
{
	this->value = value;
	SetText();
}


Label::Label(sf::Font* font, sf::Vector2f position, std::string content, int fontSize, sf::Color color)
{
	text.setPosition(position);
	text.setFont(*font);
	text.setString(content);
	text.setCharacterSize(fontSize);
	text.setFillColor(color);
}

Label::~Label()
{
}


Image::Image(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
{
	body.setTexture(texture);
	body.setPosition(position);
	body.setOrigin(size * 0.5f);
	body.setSize(size);
}

Image::~Image()
{
}



Button::Button(sf::Texture* normal, sf::Texture* clicked, sf::Vector2f size, sf::Vector2f position, int type)
{
	this->type = type;
	this->normal.setTexture(normal);
	this->clicked.setTexture(clicked);
	state = false;

	this->normal.setSize(size);
	this->clicked.setSize(size);

	this->normal.setPosition(position);
	this->clicked.setPosition(position);

	currentSprite = &this->normal;

}

Button::Button(sf::Texture* normal, sf::Texture* clicked, sf::Font* font, std::string content,int fontSize, sf::Vector2f size, sf::Vector2f position, int type)
{
	this->type = type;
	
	this->normal.setTexture(normal);
	this->clicked.setTexture(clicked);
	this->normal.setSize(size);
	this->clicked.setSize(size);
	this->normal.setPosition(position);
	this->clicked.setPosition(position);

	text.setPosition(position);
	text.setOrigin(-size * 0.25f);
	text.setFont(*font);
	text.setString(content);
	text.setCharacterSize(fontSize);

	state = false;
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
	Button(normal, clicked,size, position, 1)
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

MinusButton::MinusButton(sf::Texture* normal, sf::Texture* clicked, std::string content, sf::Vector2f size, sf::Vector2f position, Compteur* compteur) :
	Button(normal, clicked, size, position, -1)
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

CaseInventaire::CaseInventaire(sf::Texture* back, sf::Texture* image, sf::Font* font, sf::Vector2f size, sf::Vector2f position) :
	nbre(font,sf::Vector2f(size),0,32,sf::Color::Blue)
{
	this->back.setTexture(back);
	this->image.setTexture(image);
	this->back.setSize(size);
	this->image.setSize(size * 0.8f);
	this->back.setOrigin(size * 0.5f);
	this->image.setOrigin(size * 0.5f);
	this->back.setPosition(position);
	this->image.setPosition(position);

}

CaseInventaire::~CaseInventaire()
{
}

void CaseInventaire::Draw(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(image);
	window.draw(nbre.GetText());
}
