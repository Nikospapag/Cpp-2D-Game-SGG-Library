#pragma once
#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Hearts : public GameObject, public Box
{

public:
	graphics::Brush m_brush_hearts;
	Box m_hearts_box;
	float h_x;
	float h_y;
	float heart_width;
	float heart_height;

	Hearts(float x, float y);
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	void debugDraw();


	void setActive(bool active) {
		GameObject::setActive(active);
		
	}
};