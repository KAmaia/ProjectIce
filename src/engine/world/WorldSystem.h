#ifndef ENGINE_WORLD_WORLDSYSTEM_H
#define ENGINE_WORLD_WORLDSYSTEM_H

#include "precompiled.h"

#include "engine/EngineSystem.h"
#include "engine/world/Room.h"
#include "engine/math/vec3.h"

#define ASSERT_ROOM_XYZ(p_x,p_y,p_z) ASSERT_ROOM_X(p_x) ASSERT_ROOM_Y(p_y) ASSERT_ROOM_Z(p_z)

#define ASSERT_ROOM_X(p_x) assert(p_x >= 0); assert(p_x < WORLD_WIDTH);
#define ASSERT_ROOM_Y(p_y) assert(p_y >= 0); assert(p_y < WORLD_HEIGHT);
#define ASSERT_ROOM_Z(p_z) assert(p_z >= 0); assert(p_z < WORLD_DEPTH);

namespace engine {
namespace world {

	class WorldSystem : public EngineSystem {
	public:
		typedef boost::unordered_map<String,Room*> RoomList;

	private:
		RoomList *roomList;

		//worlds age
		int age;

		/* Check functions for the mountain "flow" downhill */
		void checkNorth(int heightMap[][WORLD_HEIGHT], int x, int y);
		void checkSouth(int heightMap[][WORLD_HEIGHT], int x, int y);
		void checkEast(int heightMap[][WORLD_HEIGHT], int x, int y);
		void checkWest(int heightMap[][WORLD_HEIGHT], int x, int y);

		//TODO: create some ASSERTS to make sure the array is accessed correctly (2013-04-02)
	public:
		WorldSystem();

		~WorldSystem() {}

		virtual bool init();
		virtual void uninit();
		virtual void update();

		void generate();

		Room* getRoom(int x,int y,int z);
		Room* getRoom(vec3 pos);

		void loadFromFile(String filename);
		void saveToFile(String filename);

		void updateVisualOnPosition(vec3 location, vec2 position);
	};


}
}

#endif
