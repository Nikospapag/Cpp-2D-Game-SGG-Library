#include "sgg/graphics.h"
#include "gamestate.h"
#include <string>
#include <iostream>
#include "util.h"
#include "box.h" 
#include "effect.h"

Effect::Effect(float x, float y)
	: GameObject("Effects"), effect_width(0.9f), effect_height(0.9f) {
	effect_x = x;
	effect_y = y;


	init();
}

void Effect::init() {


	//m_en_width /= 2.0f;

	m_brush_effect.fill_opacity = 1.0f;
	m_brush_effect.outline_opacity = 0.0f;
	m_brush_effect.texture = m_state->getFullAssetPath("explosions.png");

	setActive(true);





}

void Effect::update(float dt) {
	// Καλούμε την update της βάσης (GameObject)


	//m_coins_box.m_pos_x = c_x;
	//m_coins_box.m_pos_y = c_y;
	//m_coins_box.m_width = coin_width;
	//m_coins_box.m_height = coin_height;


	GameObject::update(dt);




}

void Effect::draw() {



	float x = effect_x + m_state->m_global_offset_x;
	float y = effect_y + m_state->m_global_offset_y;



	graphics::drawRect(x, y, effect_width, effect_height, m_brush_effect);

	//if (m_state->m_debugging)
		//debugDraw();

}


/*void Coins::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 0.7f, 0.2f, 0.8f);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(c_x + m_state->m_global_offset_x, c_y + m_state->m_global_offset_y, coin_width, coin_height, debug_brush);


}*/