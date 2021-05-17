#include "Projectile.h"
#include "AssetManager.h"


#define PI 3.1416

Missile::Missile(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo ,sf::Vector2f angle, float power) :
	Rigidbody(&body)
{
	this->power = power;
	this->angle = angle;

	body.setSize(size);
	body.setTexture(texture);
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

Grenade::Grenade(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo, sf::Vector2f angle, float power, float timeExplo) :
	Rigidbody(&body)
{
	this->power = power;
	this->angle = angle;
	this->maxTime = timeExplo;

	body.setSize(size);
	body.setTexture(texture);
	body.setPosition(spawnPoint);
	body.setRotation(90);

	explosion.setRadius(radiusExplo);
	explosion.setOrigin(sf::Vector2f(radiusExplo, radiusExplo));
	explosion.setPosition(spawnPoint);

	txtTimer.setPosition(body.getPosition() - sf::Vector2f(0, 10));
	txtTimer.setFont(AssetManager::GetFont("Stupid Meeting_D.otf"));
	txtTimer.setString(std::to_string(timeExplo));
	timer.restart();
}

Grenade::~Grenade()
{
}

void Grenade::Update(float deltaTime)
{
	velocity += angle * power;
	power = 0;
	velocity.y += 981.0f * deltaTime; //Gravite
	body.move(velocity * deltaTime);

	body.setRotation(90.0f + Math::GetAngleVector(velocity));
	explosion.setPosition(body.getPosition());

	timeExplo = maxTime - timer.getElapsedTime().asSeconds();
	txtTimer.setString(std::to_string(timeExplo));
	txtTimer.setPosition(body.getPosition() - sf::Vector2f(0, 10));

}

void Grenade::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(txtTimer);
}

void Grenade::DrawExplosion(sf::RenderWindow& window)
{
	window.draw(explosion);
}

void Grenade::Oncollision(sf::Vector2f direction)
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

bool Grenade::isTimeOut()
{
	if (timeExplo > 0) {
		return false;
	}
	return true;
}


Mine::Mine(sf::Texture* texture, sf::Vector2f size, sf::Vector2f spawnPoint, float radiusExplo,float radiusDetection , float timeExplo, float beforeActi) :
	Rigidbody(&body)
{
	this->maxTime = timeExplo;
	this->beforeActi = beforeActi;
	this->timeExplo = timeExplo;
	body.setSize(size);
	body.setTexture(texture);
	body.setPosition(spawnPoint);
	body.setRotation(0);

	explosion.setRadius(radiusExplo);
	explosion.setOrigin(sf::Vector2f(radiusExplo, radiusExplo));
	explosion.setPosition(spawnPoint);

	detectionZone.setRadius(radiusDetection);
	detectionZone.setOrigin(sf::Vector2f(radiusDetection, radiusDetection));
	detectionZone.setPosition(spawnPoint);

	txtTimer.setPosition(body.getPosition() - sf::Vector2f(0, 30));
	txtTimer.setFont(AssetManager::GetFont("Stupid Meeting_D.otf"));
	txtTimer.setString(std::to_string((int)timeExplo));

	timer.restart();
	
}

Mine::~Mine()
{
}

void Mine::Update(float deltaTime)
{

	velocity.y += 981.0f * deltaTime; //Gravite
	body.move(velocity * deltaTime);

	explosion.setPosition(body.getPosition());
	detectionZone.setPosition(body.getPosition());

	if (detect)
	{
		timeExplo = maxTime - timer.getElapsedTime().asSeconds();
		txtTimer.setString(std::to_string(timeExplo));
		txtTimer.setPosition(body.getPosition() - sf::Vector2f(0, 30));
	}
	else if (!activated)
	{
		Activate();
	}
	else
	{
		timer.restart();
	}
}

void Mine::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(txtTimer);
}

void Mine::DrawExplosion(sf::RenderWindow& window)
{
	window.draw(explosion);
}

void Mine::Oncollision(sf::Vector2f direction)
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

bool Mine::isTimeOut()
{
	if (timeExplo > 0) {
		return false;
	}
	return true;
}


void Mine::Activate()
{
	if (timer.getElapsedTime().asSeconds() > beforeActi)
	{
		activated = true;
		timer.restart();
	}
}