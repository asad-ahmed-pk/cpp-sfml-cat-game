// CollisionDetector.cpp

#include "CollisionDetector.h"
#include <algorithm>
#include <cassert>

// Determines if a collision is occuring between the two collidables using bounding box collision
bool CollisionDetector::AreColliding(const ICollidable* c1, const ICollidable* c2) const
{
	return AreColliding(c1->GetBoudingRect(), c2->GetBoudingRect());
}

// Determines if a collision is occuring between the 2 given sf::FloatRects
bool CollisionDetector::AreColliding(const sf::FloatRect& r1, const sf::FloatRect& r2) const
{
	float r1_left = r1.left;
	float r1_right = r1_left + r1.width;
	float r1_top = r1.top;
	float r1_bottom = r1_top + r1.height;

	float r2_left = r2.left;
	float r2_right = r2_left + r2.width;
	float r2_top = r2.top;
	float r2_bottom = r2_top + r2.height;

	return (!(r2_left > r1_right || r2_right < r1_left || r2_top > r1_bottom || r2_bottom < r1_top));
}

// Add collidable object to observation list
void CollisionDetector::AddCollidableObject(ICollidable* collidable)
{
	assert(collidable != nullptr);
	m_collidables.push_back(collidable);
}

// Sets the callback function for calling when a collision occurs
void CollisionDetector::SetCallBack(const std::function<void(ICollidable* c1, ICollidable* c2)>& callback)
{
	m_callback = callback;
}

// Remove a collidable object from the observation list
void CollisionDetector::RemoveCollidableObject(ICollidable* collidable)
{
	auto found = std::find(m_collidables.begin(), m_collidables.end(), collidable);
	if (found != m_collidables.end()){
		m_collidables.erase(found);
	}
}

// Removes all collidable objects from the observation list
void CollisionDetector::RemoveAllCollidableObjects()
{
	m_collidables.clear();
}

// Observe for collisions and notify delegate if any collisions have occurred
void CollisionDetector::Observe() const
{
	for (std::size_t i = 0; i < m_collidables.size(); i++)
	{
		for (std::size_t j = i + 1; j < m_collidables.size(); j++)
		{
			if (AreColliding(m_collidables[i], m_collidables[j])){
				m_callback(m_collidables[i], m_collidables[j]);
			}
		}
	}
}