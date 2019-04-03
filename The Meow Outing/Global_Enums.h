// Global Enums for representing movement and texture types.

#ifndef GLOBAL_ENUMS_H
#define GLOBAL_ENUMS_H

namespace Textures
{
	enum TextureType
	{
		PLAYER,
		ENEMY01,
		ENEMY02,
		ENEMY03,
		WORLD_TILEMAP,
        FISH
	};
}

namespace Movement
{
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
}

namespace WorldData
{
	enum WORLD_DATA_KEY
	{
		TILEMAP_RAW,
		TILEMAP_OPAQUE_BLOCKS
	};
}

#endif