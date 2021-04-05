#include "Missile.h"


#define PI 3.1416

Missile::Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo ,sf::Vector2f force, float power, int damage)
{
	this->power = power;
	this->force = force;
	this->damage = damage;

	body.setSize(size);
	body.setTexture(texture);
	body.setOrigin(size * 0.5f);
	body.setPosition(spawnPoint);
	body.setRotation(90);

	explosion.setRadius(radiusExplo);
	explosion.setOrigin(sf::Vector2f(radiusExplo, radiusExplo));
	explosion.setPosition(spawnPoint);
	
}

Missile::~Missile()
{
}

void Missile::Update(float deltaTime)
{
	velocity += force * power;
	power = 0;
	velocity.y += 981.0f * deltaTime; //Gravite
	body.move(velocity * deltaTime);

	body.setRotation(90.0f + Math::GetAngleVector(velocity));
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

