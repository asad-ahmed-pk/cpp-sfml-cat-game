// CollisionDetector.h
// Simple collision detector that detects collsions for two bounding rectangles.
// Is also responsible for observing observable entities added to its obervation lists.
// This class has pointers to the observable objects and has no ownership of them.

#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "Entity.h"
#include "ICollidable.h"

class CollisionDetector
{
public:
	// Determines if a collision occurred between the 2 given ICollidable objects
	bool AreColliding(const ICollidable* c1, const ICollidable* c2) const;

	// Determines if a collision occurred between the 2 given bounding rectangles
	bool AreColliding(const sf::FloatRect& r1, const sf::FloatRect& r2) const;

	// Adds the given entity to this class's observable list.
	// Be wary of the performance as adding more entities to observe will require more computations to be carried out.
	// It is preferable to add a few entities such as the player and onscreen enemies.
	void AddCollidableObject(ICollidable* entity);

	// Removes the given entity with the given address from the observable entity list
	void RemoveCollidableObject(ICollidable* entity);

	// Clears the observable entity list by removing all of the observable entities
	void RemoveAllCollidableObjects();

	// Call this function for each frame that you would like to be notified for collisions
	// Note: Ensure that you have set the callback function by setting it calling the SetCallBack function member first.
	// Otherwise, you will not be notified of the collision events.
	// The callback function will be set with the pointers to the 2 objects that have collided.
	void Observe() const;

	// Sets the callback function to call when a collision occurs
	void SetCallBack(const std::function<void (ICollidable* c1, ICollidable* c2)>& callback);

private:
	std::vector<ICollidable*> m_collidables;
	std::function<void (ICollidable* c1, ICollidable* c2)> m_callback;
};

#endif