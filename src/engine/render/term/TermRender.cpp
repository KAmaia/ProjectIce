// This code is reserved for the term system that is going to be here...

//bool RenderSystem::init(){
//	initscr();
//	if(has_colors() == false){
//		endwin();
//		LOG_ERROR("Your terminal doesn't support colors...\nFind more modern system/terminal.");
//		return false;
//	}
//
//	start_color();
//
//	cameraPos.x = 0;
//	cameraPos.y = 0;
//	cameraPos.z = 0;
//
//	return true;
//}
//
//void RenderSystem::uninit(){
//	clear();
//	endwin();
//	return;
//}
//
//void RenderSystem::update(){
//	clear();
//
//	//Render world position info on top of the screen..
//	move(0,0);
//	printw("World x: %i y: %i z: %i",cameraPos.x,cameraPos.y,cameraPos.z);
//
//	//Check that the camera is not out of bounds...
//	if(cameraPos.x < 0 || cameraPos.x >= WORLD_WIDTH){
//		LOG_ERROR("Camera out of bounds! (x)");
//		return;
//	}
//
//	if(cameraPos.y < 0 || cameraPos.y >= WORLD_HEIGHT){
//		LOG_ERROR("Camera out of bounds! (y)");
//		return;
//	}
//
//	if(cameraPos.z < 0 || cameraPos.z >= WORLD_DEPTH){
//		LOG_ERROR("Camera out of bounds! (z)");
//		return;
//	}
//
//	/* RENDER MAP */
//	world::Room *currentRoom = sceneSystem->getWorld()->getRoom(cameraPos);
//
//	vec2 pos;
//	for(int x = 0;x < ROOM_WIDTH;++x){
//		for(int y = 0;y < ROOM_HEIGHT;++y){
//			pos.x = (x + 2);
//			pos.y = (y + 2);
//			//Changing the color
//			world::Tile *tile = currentRoom->getTile(x,y);
//
//			init_pair(1, tile->fgColor, tile->bgColor);
//
//			attron(COLOR_PAIR(1));
//			drawChar(pos,currentRoom->getTile(x,y)->visual);
//			attroff(COLOR_PAIR(1));
//		}
//	}
//
//	/* RENDER ITEMS INTO THE MAP */
//	inventory::typeItemList * items = sceneSystem->getRoomInventoryByPos(cameraPos)->getItemMapAsList();
//	if ( items ) {}
//	//LOG_DEBUG_F("Items to render: %i",items.size());
//
//	/*
//	 * idea for looping the items:
//	 *
//
//	 for( tyItemIterator ii = items->begin(); ii != items->end(); ++ii ) {
//	 item::ItemBase * item = (*ii);
//	 LOG_WARNING("//TODO: get position of the item here!");
//	 }
//	 */
//
//	/* RENDER ACTORS TO MAP */
//
//	/*
//	   pos.x = sceneSystem->getPlayerActor()->getPos()->x+2;
//	   pos.y = sceneSystem->getPlayerActor()->getPos()->y+2;
//	   drawChar(pos,'@');
//	   */
//
//	std::vector<actor::ActorBase *> actors = sceneSystem->getActorManager()->getActorsInRoom(cameraPos);
//
//	for(int i = 0; i < actors.size();++i){
//		pos.x = actors.at(i)->getPosition().x + 2; //Padding because of the map positioning
//		pos.y = actors.at(i)->getPosition().y + 2;
//		drawChar( pos,actors.at(i)->getSymbol() );
//	}
//
//	/* RENDER UI ON TOP OF EVERYTHING */
//
//
//	for(int i = 0;i < uiSystem->windows.size();++i){
//		//Render window decorations
//		vec2 pos  = uiSystem->windows[i].getPos();
//		vec2 size = uiSystem->windows[i].getSize();
//
//		for(int x = pos.x; x < pos.x + size.x + 1; ++x){
//			for(int y = pos.y; y < pos.y + size.y + 1; ++y){
//				drawChar(vec2(x,y), ' ');
//
//				if(x == pos.x){
//					drawChar(vec2(x,y), '|');
//				}
//
//				if(x == pos.x + size.x){
//					drawChar(vec2(x,y), '|');
//				}
//
//				if(y == pos.y){
//					drawChar(vec2(x,y), '-');
//				}
//
//				if(y == pos.y + size.y){
//					drawChar(vec2(x,y), '-');
//				}
//			}
//		}
//
//		//Corners
//		drawChar(pos,'/');
//		drawChar(vec2(pos.x + size.x , pos.y),'\\');
//		drawChar(vec2(pos.x , pos.y + size.y),'\\');
//		drawChar(vec2(pos.x + size.x , pos.y + size.y),'/');
//
//		//lets place window title nicely to the middle
//		if(uiSystem->windows[i].getName().size() > size.x){
//			LOG_WARNING("Window name too long!");
//		}else{
//			move(pos.y,pos.x + 2);
//			printw("[%s]",uiSystem->windows[i].getName().c_str());
//		}
//
//		//render contents to windows
//		UI::ContainerBase *container = uiSystem->windows[i].getContainer();
//
//		if(container != NULL){
//			//AABB where the container is allowed to draw
//
//			AABB bounds;
//
//			bounds.pos = uiSystem->windows[i].getPos();
//			bounds.size = uiSystem->windows[i].getSize();
//
//			//The bounds are INSIDE the window, not the same size as the window
//			++bounds.pos.x;
//			++bounds.pos.y;
//			--bounds.size.x;
//			--bounds.size.y;
//
//			container->render(bounds);
//		}else{
//			LOG_ERROR("Window doesn't have container!");
//		}
//	}
//
//	return;
//}
