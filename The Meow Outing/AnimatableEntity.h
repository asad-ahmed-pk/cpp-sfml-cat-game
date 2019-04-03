// AnimatableEntity.h
// An entity that supports character animation for movement. It currently does not support idle animations.

#ifndef ANIMATABLE_ENTITY_H
#define ANIMATABLE_ENTITY_H

#include "Entity.h"
#include "SpriteAnimator.h"

class AnimatableEntity : public Entity
{
public:
	AnimatableEntity(float speed, sf::Texture* texture);
	void SetSpriteSheetAttributes(int spriteSheetRows, int spriteSheetCols, int spriteSheetStartCol, int spriteSheetTileSize, const std::map<Movement::Direction, int>& movementRows);
	void SetAnimationAttributes(float frameSpeed, float frameSwitch);
	void Animate(const sf::Time& time, Movement::Direction direction);
	virtual ~AnimatableEntity() {}

private:
	SpriteAnimator m_spriteAnimator;
	float m_animationFrameSpeed;
	float m_animationFrameSwitch;
	float m_animationFrameCounter;
	sf::Clock m_clock;
};

#endif