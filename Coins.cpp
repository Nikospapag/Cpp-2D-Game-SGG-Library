
#include <iostream>
#include "util.h" 
#include "Coins.h"

Coins::Coins(float x, float y)
	: GameObject("Coins"), coin_width(0.5f), coin_height(0.5f) {
	c_x =x;
	c_y = y;


	init();
}
//� init ��� Coins ��� �� ������� ��� vector coin_sprites ��� ������� �� �� ����������� animation ��� ������� �� ������� �� coin
void Coins::init() {


	

	m_brush_coins.fill_opacity = 1.0f;
	m_brush_coins.outline_opacity = 0.0f;
	

	setActive(true);


	coin_sprites.push_back(m_state->getFullAssetPath("coin-1.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-2.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-3.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-4.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-5.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-6.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-8.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-9.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-13.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-16.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-17.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-19.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-20.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-21.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-23.png"));
	coin_sprites.push_back(m_state->getFullAssetPath("coin-24.png"));
}
//� update ��� coin �� �� ���������� m_coin_box ��� �� collision
void Coins::update(float dt) {
	// ������� ��� update ��� ����� (GameObject)


	m_coins_box.m_pos_x = c_x;
	m_coins_box.m_pos_y = c_y;
	m_coins_box.m_width = coin_width;
	m_coins_box.m_height = coin_height;


	GameObject::update(dt);




}
//� draw ��� coin � ������������� ��� s �� ����� �� ������� �������� ������� ��� ���������� ��� coin_sprites
void Coins::draw() {
	
	float x = c_x + m_state->m_global_offset_x;
	float y = c_y + m_state->m_global_offset_y;



	graphics::drawRect(x, y, coin_width, coin_height, m_brush_coins);

	
	
	

	s = (s + 1) % coin_sprites.size();
	m_brush_coins.texture = coin_sprites[s];
	
	
		


	if (m_state->m_debugging)
		debugDraw();

}


void Coins::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 0.7f, 0.2f, 0.8f);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(c_x + m_state->m_global_offset_x, c_y + m_state->m_global_offset_y, coin_width, coin_height, debug_brush);


}
