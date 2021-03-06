#include "precompiled.h"
#include "engine/render/term/TermRender.h"
#include "engine/console/Cvar.h"

//Only compile if its in use
#ifdef TERMRENDER

#include "engine/console/Cvar.h"

namespace cvar {
	CVAR(int,wallhack,0,CVAR_CHEAT);
}

namespace engine {
namespace render {
namespace term {

	void TermRender::update(){
		tb_cell cell; //temp cell used in rendering

		//Check that the camera is not out of bounds...
		if(cameraPos.x < 0 || cameraPos.x >= WORLD_WIDTH){
			LOG_ERROR("Camera out of bounds! (x)");
			return;
		}

		if(cameraPos.y < 0 || cameraPos.y >= WORLD_HEIGHT){
			LOG_ERROR("Camera out of bounds! (y)");
			return;
		}

		if(cameraPos.z < 0 || cameraPos.z >= WORLD_DEPTH){
			LOG_ERROR("Camera out of bounds! (z)");
			return;
		}

		/* RENDER MAP */
		world::Room *currentRoom = sceneSystem->getWorld()->getRoom(cameraPos);
		vec2 currentPosition     = sceneSystem->getPlayerActor()->getPosition();

		vec2 pos;
		for(int x = 0;x < ROOM_WIDTH;++x){
			for(int y = 0;y < ROOM_HEIGHT;++y){
				pos.x = (x + 2);
				pos.y = (y + 2);

				world::Tile *tile;

				if(*cvar::wallhack){
					tile = currentRoom->getTile(x,y);
				}else{
					tile = currentRoom->getVisual(x,y);
				}

				cell.ch = tile->visual;
				cell.fg = convertColor(tile->fgColor);
				cell.bg = convertColor(tile->bgColor);

				tb_put_cell(x,y,&cell);
			}
		}

		/* RENDER ACTORS */

		std::vector<actor::ActorBase *> actors = sceneSystem->getActorManager()->getActorStorage()->getActorsInRoom(cameraPos);

		cell.fg = TB_WHITE;
		cell.bg = TB_BLACK;
		for(unsigned int i = 0; i < actors.size();++i){
			cell.ch = actors.at(i)->getSymbol();
			cell.bg = currentRoom->getVisual(actors.at(i)->getPos()->x,actors.at(i)->getPos()->y)->bgColor;

			if(currentRoom->lineOfSight(currentPosition,actors.at(i)->getPosition() ) ){
				tb_put_cell(actors.at(i)->getPos()->x, actors.at(i)->getPos()->y, &cell);
			}
		}

		/* "RENDER" UI */

		renderUI();

		/* RENDER THE ACTUAL STUFF */

		tb_present();

		return;
	}

	void TermRender::renderUI() {
		const actor::ActorBase *actor = sceneSystem->getPlayerActor();

		const actor::BodyPartContainer *parts = actor->getBodyParts();

		int count = 0;
		for (unsigned int i = 0; i < parts->size(); ++i) {
			++count;
		}

		tb_cell cell;

		cell.ch = '%';
		cell.fg = TB_WHITE;
		cell.bg = TB_BLACK;

		tb_put_cell(2,22,&cell);
		//TODO: actually display something relevant.
	}

	/**
	 * Convert engine color to termbox color
	 */
	uint16_t TermRender::convertColor(render::Color color){
		switch(color){
			case C_WHITE:
				return TB_WHITE;
			case C_BLACK:
				return TB_BLACK;
			case C_RED:
				return TB_RED;
			case C_GREEN:
				return TB_GREEN;
			case C_BLUE:
				return TB_BLUE;
		}

		return TB_WHITE;
	}

}
}
}

#endif
