#include "Motor.h"


Motor::Motor(sf::Sprite* player)
{
    this->player = player;
}

Motor::~Motor() {

}

void Motor::SetDirection(int direction, bool state) {

    switch (direction)
    {
    case 1: //up
        up = state;
        break;
    case 2: //down
        down = state;
        break;
    case 3: //left
        left = state;
        break;
    case 4: //right
        right = state;
        break;
    }
}

void Motor::Move()
{

    if (this->up)player->move(0, -2);
    if (this->down)player->move(0, 2);
    if (this->left)player->move(-2, 0);
    if (this->right)player->move(2, 0);

}