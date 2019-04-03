// Player.h
// Class to represent the player and encapsulate player functions such as movement and stats.

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "AnimatableEntity.h"
#include "ICollidable.h"

class Player : public AnimatableEntity, public ICollidable
{
public:
	Player(float speed, sf::Texture* texture, float hp = 0.0);
	virtual sf::FloatRect GetBoudingRect() const;

private:
	float m_health;
};

#endif