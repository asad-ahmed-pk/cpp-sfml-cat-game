// ICollidable.h
// Iterface used by the collision detector for fetching an object's bouding rectangle.

#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include <SFML/Graphics.hpp>

class ICollidable
{
public:
	virtual sf::FloatRect GetBoudingRect() const = 0;
};

#endif