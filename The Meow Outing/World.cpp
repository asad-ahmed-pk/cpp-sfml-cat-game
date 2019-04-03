// World.cpp
#include "World.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

const int TILE_SIZE = 32;
const int FISH_SPAWN_LIMIT = 20;
const int FISH_SCORE = 5;

// Constructor
World::World(const std::string& tileMapDataFile, const std::string& collisionMapDataFile, TextureLoader* textureLoader, const int tileRows, const int tileCols)
{
    m_textureLoader = textureLoader;
    
	// Get the tilemap sheet from the loader and set world sprite
	m_worldTileMap.setTexture(*(textureLoader->GetTextureRef(Textures::WORLD_TILEMAP)));
	m_tileMapRows = tileRows;
	m_tileMapCols = tileCols;

	// Load tile map data and collision block data
	LoadTileMapData(tileMapDataFile.c_str(), collisionMapDataFile.c_str());

	// Setup the collision detector callback
	m_collisionDetector.SetCallBack(std::bind(&World::EntitiesCollided, this, std::placeholders::_1, std::placeholders::_2));
    
    // Setup the random item spawner for spawning fish items
    m_itemSpawner = std::unique_ptr<RandomItemSpawner>(new RandomItemSpawner(m_tileMapData.size(), m_tileMapData[0].size()));
    
    
    // Load and setup the sprite for fish items
    m_fishItem.setTexture(*(textureLoader->GetTextureRef(Textures::FISH)));
    m_fishItem.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    m_fishItemPositions = new sf::Vector2i[FISH_SPAWN_LIMIT];
    
    for (int i = 0; i < FISH_SPAWN_LIMIT; i++)
    {
        m_fishItemPositions[i].x = -1;
        m_fishItemPositions[i].y = -1;
    }

    sf::Vector2i randomFishPos;
    for (int i = 0; i < FISH_SPAWN_LIMIT; i++)
    {
        randomFishPos = m_itemSpawner->SpawnItem();
        
        while (m_collisionMapData[randomFishPos.y][randomFishPos.x])
        {
            randomFishPos = m_itemSpawner->SpawnItem();
        }
        
        m_fishItemPositions[i] = randomFishPos;
    }
}

// Destructor
World::~World()
{
    delete[] m_fishItemPositions;
}

// Loads the given tile map data from the data file - expects a CSV file with tile numbers
void World::LoadTileMapData(const char* tileMapDataFile, const char* collisionMapFile)
{
	// Read in collision map data first
	std::ifstream collisionDataFile(collisionMapFile);
	std::vector<int> collisionTiles;
	int collisionTile = 0;

	while (!collisionDataFile.eof())
	{
		collisionDataFile >> collisionTile;
		collisionTiles.push_back(collisionTile);
	}

	std::ifstream dataFile(tileMapDataFile);
	std::vector<int> line;

	while (!dataFile.eof())
	{
		LoadCSVTileRow(dataFile, line);
		LoadCollisionMapRow(line, collisionTiles);
		m_tileMapData.push_back(line);
		line.clear();
	}

	dataFile.close();
}

// Sets the view for this world to manipulate
void World::SetView(sf::View* view)
{
	m_view = view;
}

// Returns the size of the world
sf::Vector2f World::GetSize()
{
	return sf::Vector2f(m_tileMapData[0].size() * TILE_SIZE, m_tileMapData.size() * TILE_SIZE);
}

// Callback for player scoring event
void World::NotifyForScoringEvent(const std::function<void (int)> &callback)
{
    m_scoreCallback = callback;
}

// Observe collisions
void World::ObserveCollisions() const
{
	// Observe for collisions between entities
	m_collisionDetector.Observe();

	// Observe for collisions between player and collision tiles
	// Get the tiles in the vicinity
	std::vector<sf::FloatRect> tiles;
	sf::Vector2i tileIndex;
	GetVicinityTileRects(m_player->getPosition(), tiles);
    

	// Check all the tiles with player's bounding rect
	for (const sf::FloatRect& rect : tiles)
	{
		tileIndex = GetTileIndex(sf::Vector2f(rect.left, rect.top));
		if (m_collisionMapData[tileIndex.y][tileIndex.x] && m_collisionDetector.AreColliding(rect, m_player->GetBoudingRect())){
			m_player->SetCollided(true);
		}
	}
    
    // Observe for player collecting fish items
    sf::FloatRect fishItemRect;
    for (int i = 0; i < FISH_SPAWN_LIMIT; i++)
    {
        if (m_fishItemPositions[i].x >= 0 && m_fishItemPositions[i].y >= 0){
            
            fishItemRect.left = m_fishItemPositions[i].x * TILE_SIZE;
            fishItemRect.top = m_fishItemPositions[i].y * TILE_SIZE;
            fishItemRect.width = fishItemRect.height = TILE_SIZE;
            
            // If player collides with the sprite rect, then set position to a negative value so it will not be drawn in next render cycle
            if(m_collisionDetector.AreColliding(fishItemRect, m_player->GetBoudingRect())){
                m_fishItemPositions[i].x = m_fishItemPositions[i].y = -1;
                m_scoreCallback(FISH_SCORE);
            }
        }
    }
}

// Collision occurred between 2 entities
void World::EntitiesCollided(ICollidable* c1, ICollidable* c2)
{
	// TESTING - just set the speed of the entities to 0.0 if collided
	Entity* e1 = dynamic_cast<Entity*>(c1);
	Entity* e2 = dynamic_cast<Entity*>(c2);

	if (!(e1 == nullptr || e2 == nullptr)){
		e1->SetCurrentSpeed(0.0);
		e2->SetCurrentSpeed(0.0);
	}
}

// IMovementObserver interface implementation - An entity moved
void World::EntityMoved(Entity* entity, Movement::Direction direction)
{
	// If entity speed is 0 and entity ghost is OK to move in the desired direction, set speed back to normal
	if (entity->HasCollided())
	{
		// Get ghost movement and set to non-collided state if the ghost tile index is not a collision tile
		sf::Vector2i ghostPos = GetEntityGhostTileIndex(entity, direction);
		if (!m_collisionMapData[ghostPos.y][ghostPos.x]){
			entity->SetCollided(false);
		}
	}
}

// Add an entity to the world to track collisions
void World::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);

	ICollidable* c = dynamic_cast<ICollidable*>(entity);
	if (c != nullptr){
		m_collisionDetector.AddCollidableObject(c);
	}
}

// Add player to check for collisions with tile map and subscribe as player's movement observer
void World::AddPlayer(Player* player)
{
	m_player = player;
	m_player->SubscribeToMovementEvents(this);
}

// Reads in a CSV line for the tile coords and loads it into the given vector
void World::LoadCSVTileRow(std::ifstream& file, std::vector<int>& tileRowNumbers)
{
	std::string number;
	std::string coords;

	std::getline(file, coords);
	std::istringstream ss(coords);

	// Get the last record and remove from the string
	std::string last = coords.substr(coords.find_last_of(',') + 1);
	coords.erase(coords.find_last_of(',') + 1);

	// Read in the rest of the CSV records
	while (!coords.empty())
	{
		std::getline(ss, number, ',');
		tileRowNumbers.push_back(std::stoi(number));
		coords.erase(0, coords.find_first_of(',') + 1);
	}
    
	tileRowNumbers.push_back(std::stoi(last));
}

// Loads in the collision map row for the given row of the tile data file
void World::LoadCollisionMapRow(std::vector<int>& tileDataRow, std::vector<int>& collsionTiles)
{
	std::vector<bool> collisionMapRow;

	for (int tile : tileDataRow)
	{
		if (std::find(collsionTiles.begin(), collsionTiles.end(), tile) != collsionTiles.end()){
			collisionMapRow.push_back(true);
		}
		else{
			collisionMapRow.push_back(false);
		}
	}

	m_collisionMapData.emplace_back(collisionMapRow);
}

// Draw function to draw out the whole world and fish items using the given render target
void World::Draw(sf::RenderWindow& window)
{
	sf::Vector2i tileCoords;

    // Draw out the world map tiles
	for (int i = 0; i < m_tileMapData.size(); i++)
	{
		for (int j = 0; j < m_tileMapData[i].size(); j++)
		{
			tileCoords = GetTileCoordinates(m_tileMapData[j][i]);
			m_worldTileMap.setPosition(i * TILE_SIZE, j * TILE_SIZE);
			m_worldTileMap.setTextureRect(sf::IntRect(tileCoords.x, tileCoords.y, TILE_SIZE, TILE_SIZE));
			window.draw(m_worldTileMap);
		}
	}
    
    // Draw out the fish tiles
    for (int i = 0; i < FISH_SPAWN_LIMIT; i++)
    {
        if (m_fishItemPositions[i].x >= 0 && m_fishItemPositions[i].y >= 0){
            m_fishItem.setPosition(m_fishItemPositions[i].x * TILE_SIZE, m_fishItemPositions[i].y * TILE_SIZE);
            window.draw(m_fishItem);
        }
    }
}

// Converts the position of the tile row and column to a screen coordinate
// returns the top left coordinate of the tile in the coordinate space
sf::Vector2f World::ConvertTilePosToCoord(int row, int col)
{
	return sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE);
}

// Returns the tile coordinates for the given size of the tiles and the tile number offset from the first tile
sf::Vector2i World::GetTileCoordinates(const int tileNumber) const
{
	int col = tileNumber % m_tileMapCols;
    int row = std::ceil(tileNumber / m_tileMapCols);
	return sf::Vector2i(col * TILE_SIZE, row * TILE_SIZE);	// because x and y coordinates
}

// Returns the index of the tile for the given screen coords
// Returns a int sf::vector with x -> the col and y -> the row of the tile
// Hence, call [y][x] to index into the tilemap data vector
sf::Vector2i World::GetTileIndex(const sf::Vector2f& coords) const
{
	// Round coords to the top left (x, y) coordinates
	int col = static_cast<int>(coords.x / TILE_SIZE);
	int row = static_cast<int>(coords.y / TILE_SIZE);

	return sf::Vector2i(col, row);
}

// Returns the tile index of the entity's 'ghost' position by one tile offset in the given direction
sf::Vector2i World::GetEntityGhostTileIndex(Entity* entity, Movement::Direction direction) const
{
	// Get current tile index position and offset by one tile in the given direction
	sf::Vector2f playerCoords = entity->getPosition();
	playerCoords.x += entity->getLocalBounds().width / 2;
	playerCoords.y += entity->getLocalBounds().height / 2;
	sf::Vector2i pos = GetTileIndex(playerCoords);

	switch (direction)
	{
	case Movement::DOWN:
		pos.y = (pos.y + 1) % m_tileMapRows;
		break;

	case Movement::UP:
		pos.y = (pos.y - 1) > 0 ? pos.y - 1 : 0;
		break;

	case Movement::LEFT:
		pos.x = (pos.x - 1) > 0 ? pos.x - 1 : 0;
		break;

	case Movement::RIGHT:
		pos.x = (pos.x + 1) % m_tileMapCols;
		break;
	}

	return pos;
}

// Fills in the given vector with bounding rects of the tiles in the vicinity of the given position
void World::GetVicinityTileRects(const sf::Vector2f& pos, std::vector<sf::FloatRect>& rects) const
{
    // New method
    sf::Vector2i centerTileIndex = GetTileIndex(pos);
    
    // set x tile range above and below 3
    int xStart = centerTileIndex.x - 3 < 0 ? 0 : centerTileIndex.x - 3;
    int xEnd = (centerTileIndex.x + 3) % m_tileMapData.size();
    
    // set y tile range above and below 3
    int yBegin = centerTileIndex.y - 3 < 0 ? 0 : centerTileIndex.y - 3;
    int yEnd = (centerTileIndex.y + 3) % m_tileMapData[0].size();
    
    //std::cerr << "Collision range: x: " << xStart << " - " << xEnd << std::endl;
    //std::cerr << "Collision range: y: " << yBegin << " - " << yEnd << std::endl;
    
    // build the tile rects using the above calculated ranges
    sf::FloatRect rect;
    for (int x = xStart; x < xEnd; x++)
    {
        for (int y = yBegin; y < yEnd; y++)
        {
            rect.left = x * TILE_SIZE;
            rect.top = y * TILE_SIZE;
            rect.width = TILE_SIZE;
            rect.height = TILE_SIZE;
            rects.push_back(rect);
        }
    }
}

// Returns the index of the tile given by the x and y offsets from the given position
sf::Vector2i World::GetTileIndexOffset(int xOffset, int yOffset, const sf::Vector2f& pos) const
{
	sf::Vector2i currentTileIndex = GetTileIndex(pos);
	sf::Vector2i offsetTileIndex = currentTileIndex;

	// calculate xOffset
	if (currentTileIndex.x + xOffset < 0){
		offsetTileIndex.x = 0;
	}
	else{
		offsetTileIndex.x += xOffset;
	}

	// calculate yOffset
	if (currentTileIndex.y + yOffset < 0){
		offsetTileIndex.y = 0;
	}
	else{
		offsetTileIndex.y += yOffset;
	}

	return offsetTileIndex;
}