// IMovementObserver.h
// Interface for an observer that is interested in being notified about movement events from an entity.

#ifndef I_MOVEMENT_OBSERVER_H
#define I_MOVEMENT_OBSERVER_H

#include "Global_Enums.h"

class Entity;

class IMovementObserver
{
public:
	virtual void EntityMoved(Entity* entity, Movement::Direction direction) = 0;
};

#endif