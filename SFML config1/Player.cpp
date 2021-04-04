#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f size,sf::Vector2f spawnPoint, float jumpHeight, int maxLife, int tagEquipe) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->maxLife = maxLife;
	this->life = maxLife;
	this->tagEquipe = tagEquipe;

	//animation
	row = 0;
	faceRight = true;

	body.setSize(size);
	body.setPosition(spawnPoint);
	body.setOrigin(size * 0.5f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (canMove)
	{
		velocity.x *= 0.2f;

		if (sf::Event::EventType::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				velocity.x -= speed;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				velocity.x += speed;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
			{
				canJump = false;

				velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
			}
		}
	}

	velocity.y += 981.0f * deltaTime; //Gravite

	if (velocity.x == 0.0f)
		row = 0;
	else
	{
		row = 1;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

}

void Player::Draw(sf::RenderWindow& window)
{

	window.draw(body);

}

void Player::Oncollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f; //Top
	}
}

void Player::SetMovement(bool state)
{
	canMove = state;
}

void Player::RecoverLife(int amount)
{
	std::cout << "J'avais : " << life << std::endl;
	if (life + amount > maxLife) life = maxLife;
	else life += amount;
	std::cout << "J'ai maintenant : " << life << std::endl;
}

bool Player::TakeDamage(int damage)
{
	life -= damage;
	if (life <= 0) return true;	
	return false;
}

bool Player::Shoot(std::string type)
{
	return inventaire.UseMunition(type);
}

int Player::GetMunition(std::string type)
{
	return inventaire.GetMunition(type);
}
