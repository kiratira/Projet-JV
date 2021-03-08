#include <SFML/Graphics.hpp>
#include "Motor.h"
class PlayerController
{
public:
	PlayerController();
	~PlayerController();
	static void Key(sf::Keyboard::Key key,Motor motor, bool state);
};

//,PlayerMotor motor, bool state