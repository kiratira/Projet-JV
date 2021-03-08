#include <SFML/Graphics.hpp>

class Motor
{

private:
    sf::Sprite* player;
    bool up = 0;
    bool down = 0;
    bool left = 0;
    bool right = 0;

public:
    Motor(sf::Sprite* player);
    ~Motor();
    void SetDirection(int direction, bool state);
    void Move();
};

