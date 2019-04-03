// Entity class for representing the base entity behaviour and game characteristics

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <set>
#include "Global_Enums.h"
#include "IMovementObserver.h"

class Entity : public sf::Sprite
{
public:
	Entity(float speed, sf::Texture* texture);	// No ownership of texture
	void Move(Movement::Direction direction);
	float GetCurrentSpeed() const;
	void SetCurrentSpeed(float velocity);
	void SetCollided(bool collided);
	bool HasCollided() const;
	void SubscribeToMovementEvents(IMovementObserver* observer);
	void UnSubscribeToMovementEvents(IMovementObserver* observer);
	void NotifyObservers(Movement::Direction direction) const;
	virtual ~Entity() {}

private:
	float m_speed;
	float m_currentSpeed;
	sf::Texture* m_texture;
	bool m_collided;
	std::set<IMovementObserver*> m_movementObservers;	// no ownership of observers
};

#endif