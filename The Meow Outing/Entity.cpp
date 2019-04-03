// Entity.cpp
#include "Entity.h"
#include <algorithm>

// Standard constructor - texture is not owned by the Entity.
// Texture is assumed to be handled by another class.
Entity::Entity(float speed, sf::Texture* texture) : m_speed(speed), m_currentSpeed(speed)
{
	m_texture = texture;
	m_collided = false;
	setTexture(*texture);
}

// Move the entity in the given direction based on the velocity and notify all observers of movement
void Entity::Move(Movement::Direction direction)
{
	NotifyObservers(direction);

	switch (direction)
	{
	case Movement::DOWN:
		move(0.0f, m_currentSpeed);
		break;

	case Movement::UP:
		move(0.0f, -m_currentSpeed);
		break;

	case Movement::LEFT:
		move(-m_currentSpeed, 0.0f);
		break;

	case Movement::RIGHT:
		move(m_currentSpeed, 0.0f);
		break;
	}	
}

// Returns the speed of the entity
float Entity::GetCurrentSpeed() const
{
	return m_currentSpeed;
}

// Set the speed for the entity
void Entity::SetCurrentSpeed(float speed)
{
	m_currentSpeed = speed;
}

// Sets this entity falg for whether it has collided or not
void Entity::SetCollided(bool collided)
{
	m_collided = collided;

	if (m_collided)
		m_currentSpeed = 0.0f;
	else
		m_currentSpeed = m_speed;
}

// Returns true if this entity is in a collision state
bool Entity::HasCollided() const
{
	return m_collided;
}

// Add an observer to subscribe to movement events
void Entity::SubscribeToMovementEvents(IMovementObserver* observer)
{
	m_movementObservers.insert(observer);
}

// Remove an observer to subscribe to movement events
void Entity::UnSubscribeToMovementEvents(IMovementObserver* observer)
{
	auto found = m_movementObservers.find(observer);

	if (found != m_movementObservers.end()){
		m_movementObservers.erase(found);
	}
}

// Notify all observers in set about movement for the given direction
void Entity::NotifyObservers(Movement::Direction direction) const
{
	std::for_each(m_movementObservers.begin(), m_movementObservers.end(), [&](IMovementObserver* observer) {observer->EntityMoved(const_cast<Entity*>(this), direction); });
}