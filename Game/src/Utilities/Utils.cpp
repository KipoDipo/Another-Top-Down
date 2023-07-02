#include "Utils.h"
#include <math.h>
#include <iostream>

using namespace sf;

const float Utils::root2 = sqrtf(2);

Vector2f Utils::normalized(Vector2f vector)
{
	if (vector == Vector2f(0, 0))
		return Vector2f(0, 0);

	return vector / sqrtf(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Utils::roundedBySubdivions(Vector2f vector, int subDivisions)
{
	float roundToNearest = 1.f / subDivisions;

	float x = (int)vector.x + roundToNearest * (int)((vector.x - (int)vector.x) / roundToNearest);
	float y = (int)vector.y + roundToNearest * (int)((vector.y - (int)vector.y) / roundToNearest);
	
	return Vector2f(x, y);
}

void Utils::printVector(Vector2f vector, std::string caption)
{
	std::cout << caption << " { " << vector.x << ", " << vector.y << " }" << std::endl;
}