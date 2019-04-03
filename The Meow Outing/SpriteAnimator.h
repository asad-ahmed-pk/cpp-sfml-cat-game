// SpriteAnimator.h
// Sprite animator class for animating the movement of a sprite using the given spritesheet information.
// This class does not require a reference or pointer to the raw sprite sheet data.
// The only information that is required is the tile sizes, rows and cols and the movement directions.
// This class then, calculate the next bouding rect for the tilesheet for other classes to utilise.

// -- A note on animation frame speed -- 
// Animation frame speed is not managed by this class. It is assumed an outer framework or class manages timestep and
// update calls to this class's Animate function.

// -- Spritesheet requirements -- 
// This class is meant for animating moving entities in an orthographic 2d top-down game. (ie; 4 direction movement)
// Each row of the tile sheet is assumed to hold the sprite for movement in one direction
// hence, there must be 4 rows for each sprite to animate.
// Also, note that this class ONLY WORKS for tile sizes of 1:1 aspect ratio.

#ifndef SPRITE_ANIMTOR_H
#define SPRITE_ANIMTOR_H

#include <SFML/Graphics.hpp>
#include <map>

#include "Global_Enums.h"

class SpriteAnimator
{
public:
	SpriteAnimator();
	SpriteAnimator(int rows, int cols, int startCol, int tileSize);	// Provide spritesheet info
	void SetSpriteSheetInfo(int rows, int cols, int startCol, int tileSize);

	// This function must be called before requesting animation for the sprite.
	// A map must be provided to establish the mapping of the movement sprite directions for the row number.
	bool SetMovementRows(const std::map<Movement::Direction, int>& movementForRows);

	// Will provide the next texture rect for the spritesheet based on given movement direction
	// Important note: This function DOES NOT handle time step and animation frame speed.
	sf::IntRect Animate(Movement::Direction direction);

private:
	struct SpriteSheetLocation
	{
		int row;
		int col;
		Movement::Direction direction;
	};

private:
	int m_rows;
	int m_cols;
	int m_startCol;
	int m_tileSize;
	std::map<Movement::Direction, int> m_movementRows;
	SpriteSheetLocation m_currentTile;
};

#endif