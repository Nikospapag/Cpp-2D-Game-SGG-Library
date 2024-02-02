#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Effect : public GameObject, public Box
{

public:
	graphics::Brush m_brush_effect;
	//Box m_coins_box;
	float effect_x;
	float effect_y;
	float effect_width;
	float effect_height;

	Effect(float x, float y);
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	//void debugDraw();
	void setActive(bool active) {
		GameObject::setActive(active);
		// Add additional logic if needed (e.g., play death animation)
	}
};
