#include "Player.h"
#include "AssetManager.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f size,sf::Vector2f* spawnPoint, float jumpHeight, int maxLife, Equipe* equipe) :
	animation(texture, imageCount, switchTime), Rigidbody(&body)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->maxLife = maxLife;
	this->life = maxLife;
	this->equipe = equipe;

	//animation
	row = 0;
	faceRight = true;

	body.setSize(size);
	body.setPosition(*spawnPoint);
	body.setOrigin(size * 0.5f);
	body.setTexture(texture);
	cpLife.setPosition(sf::Vector2f(spawnPoint->x, spawnPoint->y - size.y - 20));
	cpLife.setFont(AssetManager::GetFont("Stupid Meeting_D.otf"));
	cpLife.setFillColor(*equipe->GetColor());
}

Player::~Player()
{
}

void Player::Update(float deltaTime, bool* showViseur)
{
	velocity.x *= 0.2f;
	if (canMove)
	{	
		if (sf::Event::EventType::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				velocity.x -= speed;
				*showViseur = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				velocity.x += speed;
				*showViseur = false;
			}				

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
			{
				canJump = false;
				*showViseur = false;
				velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
			}
		}
	}

	velocity.y += 981.0f * deltaTime; //Gravite

	if (!canJump) row = 2;
	else {
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
	}
	

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	cpLife.setString(std::to_string(life));
	cpLife.setPosition(sf::Vector2f(body.getPosition().x - 12, body.getPosition().y - body.getSize().y - 20));

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
	return equipe->GetInventaire()->UseMunition(type);
}

int Player::GetMunition(std::string type)
{
	return equipe->GetInventaire()->GetMunition(type);
}

Equipe::Equipe(int tagEquipe, sf::Color* color)
{
	this->tagEquipe = tagEquipe;
	this->color = color;
}

Equipe::~Equipe()
{
}

bool Equipe::operator==(Equipe const& source)
{
	if (tagEquipe == source.tagEquipe) return true;
	return false;
}

bool Equipe::operator!=(Equipe const& source)
{
	if (tagEquipe != source.tagEquipe) return true;
	return false;
}

