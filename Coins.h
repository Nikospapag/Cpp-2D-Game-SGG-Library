#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Coins : public GameObject, public Box
{
	int s = 0;
	
	std::vector<std::string> coin_sprites;
public:
	graphics::Brush m_brush_coins;
	Box m_coins_box;
	float c_x;
	float c_y;
	float coin_width;
	float coin_height;

	Coins(float x, float y);
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	void debugDraw();
	void setActive(bool active) {
		GameObject::setActive(active);
		
	}
};