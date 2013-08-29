#ifndef ENGINE_SCENE_SCENESYSTEM_H
#define ENGINE_SCENE_SCENESYSTEM_H

#include "precompiled.h"

#include "engine/EngineSystem.h"
#include "engine/world/WorldSystem.h"
#include "engine/inventory/Inventory.h"
#include "engine/inventory/RoomInventory.h"
#include "engine/actor/ActorManager.h"

namespace engine {
namespace scene {

	/**
	 * Scene contains world,items and actors.
	 *
	 * It will also have saving/loading of the world
	 */
	class SceneSystem : public EngineSystem {
		private:
			world::WorldSystem *worldSystem;

			actor::ActorManager *actorManager;

			//TODO: Create RoomIventoryManager
			inventory::RoomInventory * roomInventory;

			// player objects
			actor::ActorBase * playerActor;
			inventory::Inventory * playerInventory;
		public:

			SceneSystem( world::WorldSystem * world, actor::ActorManager * actorMan, actor::ActorBase * player ) {
				worldSystem = world;
				actorManager = actorMan;
				playerActor = player; //TODO: WTF is player charachter handled this way !?!? FIX IT
				playerInventory = new inventory::Inventory();
				playerInventory->setOwner(playerActor);

				roomInventory = new inventory::RoomInventory( worldSystem->getRoom(0,0,0) );

				actorManager->insertActorToRoom(playerActor);
			}

			bool init( ){
				return true;
			}

			void uninit(){
				worldSystem->uninit();
			}

			void update(){
				worldSystem->update();

				/*
				std::vector<actor::ActorBase*> actorList = actorManager->getActorsInRoom(vec3(0,0,0));

				std::vector<actor::ActorBase*>::iterator it;
				for( it = actorList.begin(); it != actorList.end(); ++it ) {
					(*it)->update();
				}
				*/
			}

			/*getters & setters */

			inventory::RoomInventory * getRoomInventoryByPos(vec3 pos){
				//TODO: ONLY RETURNS THE TEST ROOM.
				return roomInventory;
			}

			actor::ActorManager * getActorManager(){
				return actorManager;
			}

			actor::ActorBase * getPlayerActor(){
				return playerActor;
			}

			world::WorldSystem* getWorld(){
				return worldSystem;
			}

			void addItem(item::ItemBase * item) {
				roomInventory->addItemToPosition( vec2(0,0), item );
			}

	};

}
}

#endif
