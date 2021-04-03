#include "Missile.h"
#include <iostream>

Missile::Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo ,sf::Vector2f angle, float power)
{
	this->power = power;
	this->angle = angle;

	body.setSize(size);
	body.setTexture(texture);
	body.setOrigin(size * 0.5f);
	body.setPosition(spawnPoint);

	explosion.setRadius(radiusExplo);
	explosion.setOrigin(sf::Vector2f(radiusExplo, radiusExplo));
	explosion.setPosition(spawnPoint);
	
}

Missile::~Missile()
{
}

void Missile::Update(float deltaTime)
{
	velocity.y += 981.0f * deltaTime; //Gravite
	body.move(velocity * deltaTime);
	explosion.setPosition(body.getPosition());
}

void Missile::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Missile::DrawExplosion(sf::RenderWindow& window)
{
	window.draw(explosion);
}
