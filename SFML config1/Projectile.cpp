#include "Projectile.h"


#define PI 3.1416

Missile::Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo ,sf::Vector2f angle, float power) :
	Rigidbody(&body)
{
	this->power = power;
	this->angle = angle;

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
	velocity += angle * power;
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

Balle::Balle( sf::Vector2f spawnPoint, sf::Vector2f angle) :
	Rigidbody(&body)
{
	body.setSize(sf::Vector2f(6, 2));
	body.setOrigin(0, 1);
	body.setPosition(spawnPoint);
	this->angle = angle;
}

Balle::~Balle()
{
}

void Balle::Update(float deltaTime)
{
	velocity += angle * power;
	power = 0;
	velocity.y += 981.0f * deltaTime; //Gravite
	body.move(velocity * deltaTime);
}

void Balle::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}