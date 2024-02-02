#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Gate : public GameObject, public Box
{

public:
	graphics::Brush m_brush_gate;
	Box m_gate_box;
	float g_x;
	float g_y;
	float gate_width;
	float gate_height;

	Gate(float x, float y);
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	void setActive(bool active) {
		GameObject::setActive(active);
		
	}
};