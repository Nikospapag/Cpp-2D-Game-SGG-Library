#include "enemy.h"
#include <iostream>
#include "util.h"


Enemy::Enemy(float initialX, float initialY)
	: GameObject("Enemy"), m_en_width(0.9f), m_en_height(0.9f) {
	m_en_x = initialX;
	m_en_y = initialY;
	

	init();
}

//� init ��� Enemy ��� �� ������� ���� ��� ������������ �������� ��� enemy ���� enemy_sprites
void Enemy::init() {


	
	float m_en_direction = -1.0f;	//�������� ��� direction ��� �� ������� ���� �� ��� ��������
	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	//m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");
	
	setActive(true);



	enemy_sprites.push_back(m_state->getFullAssetPath("bee1.png"));
	enemy_sprites.push_back(m_state->getFullAssetPath("bee5.png"));
	enemy_sprites.push_back(m_state->getFullAssetPath("bee2.png"));
	enemy_sprites.push_back(m_state->getFullAssetPath("bee3.png"));
	enemy_sprites.push_back(m_state->getFullAssetPath("bee4.png"));
	enemy_sprites.push_back(m_state->getFullAssetPath("bee6.png"));



	enemy_sprites2.push_back(m_state->getFullAssetPath("bee11.png"));
	enemy_sprites2.push_back(m_state->getFullAssetPath("bee15.png"));
	enemy_sprites2.push_back(m_state->getFullAssetPath("bee12.png"));
	enemy_sprites2.push_back(m_state->getFullAssetPath("bee13.png"));
	enemy_sprites2.push_back(m_state->getFullAssetPath("bee14.png"));
	enemy_sprites2.push_back(m_state->getFullAssetPath("bee16.png"));


}

//� update ��� Enemy ��� �� m_enemy_box ��� ������ ��� collision
void Enemy::update(float dt) {
	
	
	moveEnemy(dt);

	m_enemy_box.m_pos_x = m_en_x;
	m_enemy_box.m_pos_y = m_en_y;
	m_enemy_box.m_width = m_en_width;
	m_enemy_box.m_height = m_en_height;


	GameObject::update(dt);
	


	
}

//H draw ��� enemy ��� � ������� ��� ������� ��� ������������ ������� �� ��� ���������� ��� �������� � enemy ��������������� ��� s
void Enemy::draw() {
	float x = m_en_x + m_state->m_global_offset_x;
	float y = m_en_y + m_state->m_global_offset_y;


	
	graphics::drawRect(x, y, m_en_width, m_en_height, m_brush_enemy);

	if (m_state->m_debugging)
		debugDraw();


	if (m_en_direction < 0) {
		
		s = (int)fmod(1000.0f - m_en_x * 2.0f, enemy_sprites.size());

		m_brush_enemy.texture = enemy_sprites[s];
		return;
	}
	else if (m_en_direction > 0) { 
		
		s = (int)fmod(1000.0f - m_en_x * 2.0f, enemy_sprites2.size());

		m_brush_enemy.texture = enemy_sprites2[s];
		return;
	}


}

//�������� ��� ������ ��� enemies ��� ���� �� �������� ���������� 
void Enemy::moveEnemy(float dt) {
	float delta_time = dt / 1000.0f;
	m_en_x += m_en_direction * m_en_speed * delta_time;

	// ������� �� � ������ ���� ������ ��� ���� ��� �����
	if (m_en_x <= 0.0f) {
		m_en_x = 0.0f;
		m_en_direction = 1.0f; // ������ ����������� ���� �� �����

	}
	else if (m_en_x >= 42.0f) {
		m_en_x = 42.0f;
		m_en_direction = -1.0f; // ������ ����������� ���� �� ��������

	}
}



void Enemy::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_en_x + m_state->m_global_offset_x, m_en_y + m_state->m_global_offset_y, 1.0f, 1.0f, debug_brush);

	
}


