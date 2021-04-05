#include "Math.h"

float Math::GetAngleVector(sf::Vector2f vect)
{
	if (vect.y == 0)
		return vect.x < 0 ? 180 : 0;
	else if (vect.x == 0)
		return vect.y < 0 ? 270 : 90;

	if (vect.y > 0)
		if (vect.x > 0)
			return atan(vect.y / vect.x) * 180.f / 3.14159f;
		else
			return 180.0f - atan(vect.y / -vect.x) * 180.f / 3.14159f;
	else
		if (vect.x > 0)
			return 360.0f - atan(-vect.y / vect.x) * 180.f / 3.14159f;
		else
			return 180.0f + atan(-vect.y / -vect.x) * 180.f / 3.14159f;
}

