#ifndef ENGINE_WORLD_ROOM_H
#define ENGINE_WORLD_ROOM_H

#include "precompiled.h"

#include "engine/world/Tile.h"
#include "engine/math/vec2.h"

#define ASSERT_TILE_XY(p_x,p_y) ASSERT_TILE_X(p_x) ASSERT_TILE_Y(p_y)

#define ASSERT_TILE_X(p_x) assert(p_x >= 0); assert(p_x < ROOM_WIDTH);
#define ASSERT_TILE_Y(p_y) assert(p_y >= 0); assert(p_y < ROOM_HEIGHT);

namespace engine {
namespace world {

	enum ROOM_TYPES{
		ROOM_TYPE_EMPTY   = 0, //void, air or uninitialiazed tile
		ROOM_TYPE_GROUND  = 1,
		ROOM_TYPE_WATER   = 2,
		ROOM_TYPE_DUNGEON = 3,
	};

	/**
	* Room contains the layout of the room, with all the tile data.
	*/
	class Room {
	public:
		Room();

	private:
		Tile tiles[ROOM_WIDTH * ROOM_HEIGHT];

	public:
		//Roomtype also used as visual
		ROOM_TYPES roomType;

		Tile* getTile(vec2 pos);
		Tile* getTile(int x,int y);
		Tile* getTileArray();

		void setTile(vec2 pos,Tile tile);
		void setTile(int x,int y,Tile tile);

		void generate();

		void printLayout();
	};
}
}

#endif /* ENGINE_WORLD_ROOM_H */
