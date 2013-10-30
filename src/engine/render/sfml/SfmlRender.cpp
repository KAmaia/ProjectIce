#include "precompiled.h"
#include "engine/render/sfml/SfmlRender.h"
#include "engine/console/Cvar.h"

#ifdef SFMLRENDER

namespace cvar {
	CVAR(int,wallhack,0,CVAR_CHEAT);
}

namespace engine {
namespace render {
namespace sfml {

	void SfmlRender::update(){
		if(!window->isOpen()){
			//Window has been closed! Close the application
			LOG_INFO("[SfmlRender] Main window has been closed");
			//TODO: Closing is not handled correctly!
			return;
		}

		/*
		sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
		*/

		window->clear(sf::Color::Black);

		world::Room *currentRoom = sceneSystem->getWorld()->getRoom(cameraPos);
		vec2 currentPosition     = sceneSystem->getPlayerActor()->getPosition();

		vec2 pos;

		sf::Sprite sprite; //TODO: this may not be optimal

		for(int x = 0;x < ROOM_WIDTH;++x){
			for(int y = 0;y < ROOM_HEIGHT;++y){
				pos.x = (x + 2);
				pos.y = (y + 2);
				//Changing the color
				world::Tile *tile;

				if(*cvar::wallhack) {
					 tile = currentRoom->getTile(x,y);
				} else {
					 tile = currentRoom->getVisual(x,y);
				}

				switch(tile->type){
				case world::TILE_SOLID_ROCK:
					sprite = solidRockSprite;
					break;
				case world::TILE_ROCK_FLOOR:
					sprite = floorSprite;
					break;
				case world::TILE_VOID:
					sprite = voidSprite;
					break;
				case world::TILE_TREE:
					sprite = treeSprite;
					break;
				default:
					sprite = errorSprite;
				}

				sprite.setPosition( (x * 10.f) , (y * 10.f) );
				window->draw(sprite); 
			}

		}

		std::vector<actor::ActorBase *> actors = sceneSystem->getActorManager()->getActorStorage()->getActorsInRoom(cameraPos);

		for(unsigned int i = 0; i < actors.size();++i){
			sprite = dummySprite; //default gfx if not found
			actor::ActorBase *actor = actors.at(i);

			//TODO: Add some kind of linking of player <-> resource on a text file.
			if(actor->getName() == "Player"){
				sprite = playerSprite;
			}

			if(currentRoom->lineOfSight(currentPosition,actor->getPosition() ) ){
				sprite.setPosition( (actor->getPos()->x * 10) , (actor->getPos()->y * 10) );
				window->draw(sprite);
			}
		}

		window->display();
	}

}
}
}

#endif