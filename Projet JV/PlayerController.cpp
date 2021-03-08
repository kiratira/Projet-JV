#include "PlayerController.h"


PlayerController::PlayerController() 
{


}
PlayerController::~PlayerController()
{

}


void PlayerController::Key(sf::Keyboard::Key key,Motor motor, bool state)
{
    switch (key)
    {
    case sf::Keyboard::Up:
        motor.SetDirection(1, state);
        break;
    case sf::Keyboard::Down:
        motor.SetDirection(2, state);
        break;
    case sf::Keyboard::Left:
        motor.SetDirection(3, state);
        break;
    case sf::Keyboard::Right:
        motor.SetDirection(4, state);
        break;
    }
}