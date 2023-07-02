#include "Random.h"
#include <random>

int Random::next(int min, int max)
{
	return rand() % (max - min) + min;
}

int Random::next(int max)
{
	return next(0, max);
}
