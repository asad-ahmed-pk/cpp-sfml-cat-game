// AnimatableEntity.cpp

#include "AnimatableEntity.h"

// Constructor takes in info for the sprite and optional spritesheet info
// If sprite info is not given, this class assumed that a single unanimatable sprite is to be used.
AnimatableEntity::AnimatableEntity(float speed, sf::Texture* texture) : Entity(speed, texture)
{

}

// Sets the given animation attributes for managing the animation frame speed
void AnimatableEntity::SetAnimationAttributes(float frameSpeed, float frameSwitch)
{
	m_animationFrameSpeed = frameSpeed;
	m_animationFrameSwitch = frameSwitch;
	m_animationFrameCounter = 0.0f;
}

// Sets the spritesheet attributes for loading and managing the texture from the spritesheet for the sprite animator
void AnimatableEntity::SetSpriteSheetAttributes(int spriteSheetRows, int spriteSheetCols, int spriteSheetStartCol, int spriteSheetTileSize, const std::map<Movement::Direction, int>& movementRows)
{
	m_spriteAnimator.SetSpriteSheetInfo(spriteSheetRows, spriteSheetCols, spriteSheetStartCol, spriteSheetTileSize);
	m_spriteAnimator.SetMovementRows(movementRows);
}

// Animates the sprite and takes animation frame speed into account
void AnimatableEntity::Animate(const sf::Time& time, Movement::Direction direction)
{
	m_animationFrameCounter += m_animationFrameSpeed * m_clock.restart().asSeconds();

	if (m_animationFrameCounter >= m_animationFrameSwitch){
		// Get the next texture rect since enough frames have passed to show the next animation
		setTextureRect(m_spriteAnimator.Animate(direction));
		m_animationFrameCounter = 0;
	}
}