// Player.cpp

#include "Player.h"

// Constructor
Player::Player(float speed, sf::Texture* texture, float hp) : AnimatableEntity(speed, texture)
{
	m_health = hp;
}

// ICollidable interface definition
sf::FloatRect Player::GetBoudingRect() const
{
	return getGlobalBounds();
}