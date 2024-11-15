#include "sgg/graphics.h"
#include "gamestate.h"




void init()
{
	GameState::getInstance()->init();

}


void draw()
{
	
	GameState::getInstance()->draw();
	

}

void update(float dt)
{
	GameState::getInstance()->update(dt);
}



int main(int RGC, char** argv)
{
	graphics::createWindow(900, 900, "BEESituation");
	//graphics::setFullScreen(true);

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	


	graphics::startMessageLoop();
	return 0;
}