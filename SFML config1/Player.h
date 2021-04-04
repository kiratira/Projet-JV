#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Collider.h"
#include "inventory.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f size, sf::Vector2f spawnPoint ,float jumpHeight);
	~Player();


	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Oncollision(sf::Vector2f direction);
	void SetMovement(bool state);
	void SetTagEquipe(int tag);
	

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(&body); }
	int GetLife() { return life; }
	bool IsFaceRight() { return faceRight; }
	bool TakeDamage(int damage);
	bool Shoot(std::string type);
	int GetMunition(std::string type);
	int GetTagEquipe() { return tagEquipe; }
	inventory* GetInventaire() { return &inventaire; }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump = true;
	float jumpHeight;
	bool canMove = false;

	int life = 100;

	inventory inventaire;
	int tagEquipe;

};

