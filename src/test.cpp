#include "scppt.h"
#include "engine/world/WorldSystem.h"
#include "engine/world/Room.h"
#include "engine/world/Tile.h"
#include "engine/UI/Window.h"
#include "engine/player/Player.h"
#include "game/actor/player/PlayerActor.h"

using namespace engine;

int testFails = 0;
int testOks   = 0;

int main(){
	SCPPT_START;

	PRINTLN("-> Tile");
	{
		world::Tile testTile;
		testTile.setType(world::TILE_TREE);

		SCPPT_COMPARE("Tree blocks movement",testTile.blocks,==,true);
		SCPPT_COMPARE("Tree has HP",testTile.hp,>,0);
	}

	PRINTLN("-> Room");
	{
		world::Room testRoom;
		testRoom.roomType = world::ROOM_TYPE_WATER;

		for(int i = 0;i <25;++i){
			testRoom.generate();
		}

		SCPPT_COMPARE("Rooms generate something",testRoom.getTile(5,5)->visual,==,'.');
	}

	PRINTLN("-> Window");
	{
		UI::Window window;
		window.setName("asdf");

		window.printDebugInfo();
	}

	PRINTLN("-> Player");
	{
		engine::player::Player player;

		player.init();
	}

	PRINTLN("-> Player");
	{
		game::actor::player::PlayerActor *playerActor = new game::actor::player::PlayerActor();

		playerActor->update();
	}

	PRINTLN("Tests complete");

	SCPPT_END;
}
