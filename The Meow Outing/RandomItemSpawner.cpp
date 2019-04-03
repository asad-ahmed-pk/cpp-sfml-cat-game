// RandomItemSpawner.cpp

#include "RandomItemSpawner.h"
#include <ctime>
#include <iostream>

// Constructor - sets up the random number generator and the info needed to begin generating numbers
RandomItemSpawner::RandomItemSpawner(int mapRows, int mapCols) : m_mapRows(mapRows), m_mapCols(mapCols)
{
    m_rng.seed(std::time(0));
}

// Spawns an item for the given tile coordinates (row, col)
sf::Vector2i RandomItemSpawner::SpawnItem()
{
    //std::cerr << "Begin Spawn Item..." << std::endl;
    
    int row = static_cast<int>(m_rng() % m_mapRows);
    int col = static_cast<int>(m_rng() % m_mapCols);
    
    //std::cerr << "Spawned at row: " << row << " and col: " << col << std::endl;
    return sf::Vector2i(row, col);
}