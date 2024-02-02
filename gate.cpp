#include "sgg/graphics.h"
#include "gamestate.h"
#include <string>
#include <iostream>
#include "util.h"
#include "box.h" 
#include "Gate.h"

Gate::Gate(float x, float y)
	: GameObject("Hearts"), gate_width(1.0f), gate_height(1.0f) {
	g_x = x;
	g_y = y;


	init();
}
//Η init της gate με την αντιστοιχη εικονα
void Gate::init() {


	//m_en_width /= 2.0f;

	m_brush_gate.fill_opacity = 1.0f;
	m_brush_gate.outline_opacity = 0.0f;
	m_brush_gate.texture = m_state->getFullAssetPath("planet.png");

	setActive(true);


}
//Η update της gate με τον ορισμο των m_gate_box για τα collisions
void Gate::update(float dt) {
	// Καλούμε την update της βάσης (GameObject)


	m_gate_box.m_pos_x = g_x;
	m_gate_box.m_pos_y = g_y;
	m_gate_box.m_width = gate_width;
	m_gate_box.m_height = gate_height;


	GameObject::update(dt);




}
//Η αντιστοιχη draw της gate
void Gate::draw() {
	float x = g_x + m_state->m_global_offset_x;
	float y = g_y + m_state->m_global_offset_y;



	graphics::drawRect(x, y, gate_width, gate_height, m_brush_gate);

	//if (m_state->m_debugging)
		//debugDraw();

}