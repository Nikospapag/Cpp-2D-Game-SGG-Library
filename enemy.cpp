#include "enemy.h"
#include <iostream>
#include "util.h"


Enemy::Enemy(float initialX, float initialY)
	: GameObject("Enemy"), m_en_width(0.9f), m_en_height(0.9f) {
	m_en_x = initialX;
	m_en_y = initialY;
	

	init();
}

//Η init της Enemy και το φορτωμα ολων των διαφορετικων κινησεων των enemy στην enemy_sprites
void Enemy::init() {


	
	float m_en_direction = -1.0f;	//Ορίζουμε και direction για να ξερουμε προς τα που κινειται
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

//Η update της Enemy και το m_enemy_box για ελεγχο των collision
void Enemy::update(float dt) {
	
	
	moveEnemy(dt);

	m_enemy_box.m_pos_x = m_en_x;
	m_enemy_box.m_pos_y = m_en_y;
	m_enemy_box.m_width = m_en_width;
	m_enemy_box.m_height = m_en_height;


	GameObject::update(dt);
	


	
}

//H draw της enemy και ο ορισμος των εικονων που αντιστοιχουν αναλογα με την κατευθυνση που κινειται ο enemy χρησιμοποιωντας την s
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

//Οριζουμε την κινηση των enemies και ποτε να αλλαζουν κατευθυνση 
void Enemy::moveEnemy(float dt) {
	float delta_time = dt / 1000.0f;
	m_en_x += m_en_direction * m_en_speed * delta_time;

	// Έλεγχος αν ο εχθρος έχει φτάσει στο οριο του χωρου
	if (m_en_x <= 0.0f) {
		m_en_x = 0.0f;
		m_en_direction = 1.0f; // Αλλαγη κατεύθυνσης προς τα δεξια

	}
	else if (m_en_x >= 42.0f) {
		m_en_x = 42.0f;
		m_en_direction = -1.0f; // Αλλαγη κατεύθυνσης προς τα αριστερα

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


