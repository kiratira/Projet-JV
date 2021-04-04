#include "Caisse.h"

Caisse::Caisse(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint)
{
	body.setTexture(texture);
	body.setSize(size);
	body.setOrigin(size * 0.5f);
	body.setPosition(spawnPoint);
}

Caisse::~Caisse()
{
}

void Caisse::Update(float deltaTime)
{
	velocity.y += 981.0f * deltaTime; //Gravite
	body.move(velocity * deltaTime);
}

void Caisse::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
void Caisse::Oncollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f; // Left
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f; // Right
	}
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;	// Bottom
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f; //Top
	}
}


CaisseMunition::CaisseMunition(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, std::string type, int nbre) :
	Caisse(texture, size, spawnPoint)
{
	this->type = type;
	this->nbre = nbre;
}

CaisseMunition::~CaisseMunition()
{
}



CaisseHeal::CaisseHeal(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, int nbre) :
	Caisse(texture,size,spawnPoint)
{
	this->nbre = nbre;
}

CaisseHeal::~CaisseHeal()
{
}