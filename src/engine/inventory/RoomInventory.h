#ifndef ENGINE_INVENTORY_ROOMINVENTORY_H
#define ENGINE_INVENTORY_ROOMINVENTORY_H

#include "precompiled.h"

#include "engine/math/vec2.h"
#include "engine/world/Room.h"
#include "engine/item/ItemBase.h"

#include <map>
#include <vector>

namespace engine {
namespace inventory {

	//typedef std::pair<int,int> pairVec2;
	typedef std::vector<item::ItemBase*> ItemList;
	typedef std::map< vec2, ItemList* > ItemMap;
	typedef std::vector<item::ItemBase*>::iterator ItemIterator;
	typedef std::map< vec2, ItemList* >::iterator MapIterator;

	/**
	 *	This object is responsible for the room's inventory
	 */
	class RoomInventory {
	private:
		//vec2 pairToVec2( pairVec2 pair );
		//pairVec2 vec2ToPair( vec2 vec );
		ItemList * initEmptyList( vec2 vp );
		void clean(); // removes untracked items on get

		world::Room * owner;
		ItemMap itemMap;
	public:
		RoomInventory( world::Room * owner );

		/** Returns the entire contents of the inventory
		 * @returns a map containing lists of items
		 */
		ItemMap getItemMap();

		/** Returns all of the items this room containins in the form of a vector
		 * @returns a list containing all the items in the world
		 */
		ItemList * getItemMapAsList();

		/** Returns a list of items from a given position in the room
		 * @param position the position to search for
		 * @returns the list of items
		 */
		ItemList * getItemListByPosition( vec2 position );

		/** Searches the room for the item instance with the supplied ID number
		 * @param id the identification number
		 * @returns the instance of the item (if found, NULL if not)
		 */
		item::ItemBase * getItemByID(int id);

		/** Returns a list of instances which have the same name
		 * @param name the name to search for
		 * @returns the list of found items
		 */		
		ItemList * getItemListByName( String name );

		/** Returns a count of all the items on the map
		 * @returns the item count
		 */	
		int getItemCount();

		/** Returns a count of items at a given position on the map
		 * @returns the item count
		 */	
		int getItemCountAtPosition( vec2 position );

		/** Adds an instance of an item to a given position on the map
		 * @param position the position to add the item too
		 * @param item the instance of the item (if registered with the engine)
		 * @returns a flag indicating if it was added or not
		 */	
		bool addItemToPosition( vec2 position, item::ItemBase * item );

		/** Removes 
		 * @param position the position to add the item too
		 * @param id the identification number of the item
		 * @returns a flag indicating if it was removed or not (false if not found)
		 */			
		bool deleteItemByPosition( vec2 position, int id );

	};

}
}

#endif