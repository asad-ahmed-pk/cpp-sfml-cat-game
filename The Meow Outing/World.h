// World.h
// Represents the game world for a game instance. Includes tile map data and the entities in the world.

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "TextureLoader.h"
#include "Entity.h"
#include "Player.h"
#include "CollisionDetector.h"
#include "ICollidable.h"
#include "IMovementObserver.h"
#include "RandomItemSpawner.h"

class World : public IMovementObserver
{
public:
	// Constructs the world with enough info to draw out a tile map sprite for the world
	// @param textureLoader must be loaded with the world map tilesheet before calling this constructor
	// Note: The tile data is expected to be a csv file with tile map numbers (exported from the Tiled program)
	World(const std::string& tileMapDataFile, const std::string& collisionMapDataFile, TextureLoader* textureLoader, const int tileRows, const int tileCols);

	// Adds an entity to this world's tile based sytem for tracking entity location and collisions
	void AddEntity(Entity* entity);

	// Adds the player to track for collisions with the tile map
	void AddPlayer(Player* player);

	// Draws out the whole world using the given render target
	void Draw(sf::RenderWindow& window);

	// Calls on the world to observe a collision for a frame
	void ObserveCollisions() const;

	// IMovementObserver interface implementation
	virtual void EntityMoved(Entity* entity, Movement::Direction direction);

	// Set the view for this world to manipulate
	void SetView(sf::View* view);

	// Returns the size of the world
	sf::Vector2f GetSize();
    
    // Set the callback for notifying when a player scoring event occurs
    void NotifyForScoringEvent(const std::function<void(int)>& callback);
    
    // Destructor
    ~World();

private:
	void LoadTileMapData(const char* tileMapDataFile, const char* collisionMapFile);
	void LoadCSVTileRow(std::ifstream& file, std::vector<int>& tileRowNumbers);
	void LoadCollisionMapRow(std::vector<int>& tileDataRow, std::vector<int>& collsionTiles);
	sf::Vector2f ConvertTilePosToCoord(int row, int col);
	sf::Vector2i GetTileCoordinates(const int tileNumber) const;
	sf::Vector2i GetTileIndex(const sf::Vector2f& coords) const;
	sf::Vector2i GetEntityGhostTileIndex(Entity* entity, Movement::Direction direction) const;
	
private:
	TextureLoader* m_textureLoader;		// no ownership
	std::vector<Entity*> m_entities;	// no ownership
	Player* m_player;					// no ownership
	sf::View* m_view;					// no ownership
    
    // Fish items
    std::unique_ptr<RandomItemSpawner> m_itemSpawner;
    sf::Sprite m_fishItem;
    sf::Vector2i* m_fishItemPositions;
    
	// Tilemap data
	std::vector<std::vector<int>> m_tileMapData;
	std::vector<std::vector<bool>> m_collisionMapData;
	sf::Sprite m_worldTileMap;
	int m_tileMapRows;
	int m_tileMapCols;

	// Collision detection
	void EntitiesCollided(ICollidable* c1, ICollidable* c2);
	CollisionDetector m_collisionDetector;
	void GetVicinityTileRects(const sf::Vector2f& pos, std::vector<sf::FloatRect>& rects) const;
	sf::Vector2i GetTileIndexOffset(int xOffset, int yOffset, const sf::Vector2f& pos) const;
    
    // Player score event callback
    std::function<void (int)> m_scoreCallback;
};

#endif