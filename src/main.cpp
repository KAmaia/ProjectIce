#include "precompiled.h"

#include "engine/math/random.h"
#include "engine/EngineSystem.h"
#include "engine/world/WorldSystem.h"
#include "engine/render/RenderSystem.h"
#include "engine/UI/UISystem.h"
#include "engine/UI/Window.h"
#include "engine/UI/containers/TextContainer.h"
#include "engine/UI/containers/SelectContainer.h"

#include "game/items/IronItem.h"
#include "game/items/ArrowItem.h"
#include "game/items/containers/QuiverItem.h"

int main(){
	randomInit();

	LOG_INFO("----");
	LOG_INFO("engine starting");

	world::WorldSystem *world        = new world::WorldSystem();
	engine::UI::UISystem *ui         = new UI::UISystem();
	render::RenderSystem *render     = new render::RenderSystem(world,ui);

	world->init();
	render->init();
	ui->init();
	world->generate();

	/*\*/
	game::items::IronItem * iron = new game::items::IronItem();
	game::items::ArrowItem * arrow = new game::items::ArrowItem();
	game::items::containers::QuiverItem * quiver = new game::items::containers::QuiverItem();
	quiver->setQuantity( 1 );
	quiver->setQuantity( quiver->getQuantity() + 2 );
	quiver->setQuantity( 100 );
	/*\*/

	UI::Window welcomeWindow;
	welcomeWindow.setPos(vec2(4,3));
	welcomeWindow.setSize(vec2(35,15));
	welcomeWindow.setName("Welcome to ProjectIce");

	UI::containers::TextContainer *textCont = new UI::containers::TextContainer();
	textCont->init();
	textCont->setText("ProjectIce is an experimental roguelike project developed in C++. This is a early development build. And this string is useless and long to test the word wrapping feature on the textContainer. -- press anykey to continue --");
	textCont->setPressToContinue(true);

	welcomeWindow.setContainer(textCont);

	UI::Window blob;
	blob.setPos(vec2(84,3));
	blob.setSize(vec2(15,15));
	blob.setName("blob");

	UI::containers::SelectContainer *selectCont = new UI::containers::SelectContainer();
	selectCont->insertItem("0 zero");
	selectCont->insertItem("& second");
	selectCont->insertItem("# so on");
	selectCont->insertItem( iron->getName() );
	selectCont->insertItem( arrow->getName() );
	selectCont->insertItem( quiver->getName() );

	blob.setContainer(selectCont);

	ui->addWindow(welcomeWindow);
	ui->addWindow(blob);

	bool quitStatus = false;
	while(quitStatus == false){
		world->update();
		render->update();
		ui->update();
		//int key = getch();
	}

	render->uninit();
	world->uninit();

	/**
	 * Protobuff testing
	 */
	/*
	tileMsg test;
	test.set_posx(15);
	test.set_posy(10);
	test.set_visual("#");
	test.set_roomid(0);

	std::fstream stream;
	stream.open("gamesave", std::ios::out | std::ios::binary);

	test.SerializeToOstream(&stream);

	stream.close();

	std::fstream input;
	input.open("gamesave",std::ios::in | std::ios::binary);

	tileMsg blob;
	blob.ParseFromIstream(&input);

	input.close();

	printf("Tile x: %i tile y: %i [%s]\n",blob.posx(),blob.posy(),blob.visual().c_str());
	*/

	//Clean up the systems
	/*
	delete world;
	delete render;
	*/

	return 0;
}
