
#include <iostream>
#include "util.h"
#include "Hearts.h"

Hearts::Hearts(float x, float y)
	: GameObject("Hearts"), heart_width(0.5f), heart_height(0.5f) {
	h_x = x;
	h_y = y;


	init();
}
//Η init της heart φορτωνοντας και την αντιστοιχη εικονα
void Hearts::init() {


	

	m_brush_hearts.fill_opacity = 1.0f;
	m_brush_hearts.outline_opacity = 0.0f;
	m_brush_hearts.texture = m_state->getFullAssetPath("heart.png");

	setActive(true);


}
//Η update της heart και ο ορισμος της m_heart_box το οποιο θα μας χρησιμευσει για τα collisions
void Hearts::update(float dt) {
	// Καλούμε την update της βάσης (GameObject)


	m_hearts_box.m_pos_x = h_x;
	m_hearts_box.m_pos_y = h_y;
	m_hearts_box.m_width = heart_width;
	m_hearts_box.m_height = heart_height;


	GameObject::update(dt);




}
//H draw της heart
void Hearts::draw() {
	float x = h_x + m_state->m_global_offset_x;
	float y = h_y + m_state->m_global_offset_y;



	graphics::drawRect(x, y, heart_width, heart_height, m_brush_hearts);

	if (m_state->m_debugging)
		debugDraw();

}



void Hearts::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 0.5f, 0.4f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(h_x + m_state->m_global_offset_x, h_y + m_state->m_global_offset_y, heart_width, heart_height, debug_brush);


}