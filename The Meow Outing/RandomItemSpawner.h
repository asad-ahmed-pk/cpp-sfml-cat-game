//RandomItemSpawner.h
// Class responsible for spawining an item for the given texture at a given range of tiles

#ifndef RANDOM_ITEM_SPAWNER_H
#define RANDOM_ITEM_SPAWNER_H

#include <SFML/Graphics.hpp>
#include <random>

class RandomItemSpawner
{
public:
	// Init map info so this class knows where to spawn items
	RandomItemSpawner(int mapRows, int mapCols);

	// Returns a random spawn position for a tile position index (a row and col number)
	sf::Vector2i SpawnItem();

private:
	int m_mapRows;
	int m_mapCols;
    std::mt19937 m_rng;
};

#endif