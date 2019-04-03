// SpriteAnimator.cpp

#include "SpriteAnimator.h"

// Standard constructor that takes in the required info about the tilesheet
SpriteAnimator::SpriteAnimator(int rows, int cols, int startCol, int tileSize)
{
	SetSpriteSheetInfo(rows, cols, startCol, tileSize);
}

SpriteAnimator::SpriteAnimator()
{
	SetSpriteSheetInfo(0, 0, 0, 0);
}

// Sets the given attributes for the spritesheet
void SpriteAnimator::SetSpriteSheetInfo(int rows, int cols, int startCol, int tileSize)
{
	m_rows = rows > 0 ? rows : 0;
	m_cols = cols > 0 ? cols : 0;
	m_startCol = startCol >= 0 ? startCol : 0;
	m_tileSize = tileSize > 0 ? tileSize : 0;

	m_currentTile.row = 0;
	m_currentTile.col = 0;
}

// Assign the rows numbers for the corresponding movement direction
bool SpriteAnimator::SetMovementRows(const std::map<Movement::Direction, int>& movementForRows)
{
	// can only have 4 directions as given by the Movement::Direction enum
	if (movementForRows.size() != 4){
		return false;
	}

	m_movementRows = movementForRows;
}

// Returns the texture rect for drawing the next animation frame based on the movement
sf::IntRect SpriteAnimator::Animate(Movement::Direction direction)
{
	// If movement direction was same as the last one then increment col
	if (direction == m_currentTile.direction){
		if (++m_currentTile.col >= m_startCol + m_cols){
			m_currentTile.col = m_startCol;
		}
	}
	else{
		// Restart animation from column 0 of the movement row
		m_currentTile.direction = direction;
		m_currentTile.row = m_movementRows[direction];
		m_currentTile.col = m_startCol;
	}

	return sf::IntRect(m_currentTile.col * m_tileSize, m_currentTile.row * m_tileSize, m_tileSize, m_tileSize);
}