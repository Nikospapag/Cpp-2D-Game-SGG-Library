#include "enemy.h"
#include "sgg/graphics.h"
#include "gamestate.h"


#include "Enemy.h"

Enemy::Enemy(float initialX, float initialY)
	: GameObject("Enemy"), m_en_width(1.0f), m_en_height(1.0f) {
	m_en_x = initialX;
	m_en_y = initialY;
	
	// Αρχικοποίηση χρονομέτρου
	//resetMovementTimer();
	init();
}


void Enemy::init() {
	m_en_width /= 2.0f;

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");
	//resetMovementTimer();


}


void Enemy::update(float dt) {
	// Καλούμε την update της βάσης (GameObject)
	GameObject::update(dt);
	moveEnemy(dt);

	//m_movement_timer += dt;
	//if (m_movement_timer >= 4.0f) {  // Κάθε 4 δευτερόλεπτα
		
		//resetMovementTimer();
	//}
}


void Enemy::draw() {
	float x = m_en_x + m_state->m_global_offset_x;
	float y = m_en_y + m_state->m_global_offset_y;

	graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_enemy);
}


void Enemy::moveEnemy(float dt) {

	float delta_time = dt / 1000.0f;
	float en_move = -1.0f;

	m_en_x = std::max(-en_max_velocity, m_en_x + delta_time * en_move * en_accel_horizontal);
	m_en_x -= 0.03f * m_en_x / (0.01f + fabs(m_en_x));

	if (fabs(m_en_x) < 0.01f)
		m_en_x = 0.0f;

	//m_pos_x += m_en_x * delta_time;




	/*if (m_move_left) {
		en_move -= 1.0f;
	}
	else {
		en_move += 1.0f;
	}*/

	//m_en_x = std::min(en_max_velocity, m_en_x + delta_time * en_move * en_accel_horizontal);
	//m_en_x = std::max(-en_max_velocity, m_en_x);

	//m_en_x -= 0.2f * m_en_x / (0.1f + fabs(m_en_x));
	//if (fabs(m_en_x) < 0.01f)
		//m_en_x = 0.0f;
	//m_en_x += m_en_x * delta_time;
}


//void Enemy::resetMovementTimer() {
	//m_movement_timer = 0.0f;
//}











/*Enemy::Enemy(float initialX, float initialY)
	: GameObject("Enemy"), m_en_x(initialX), m_en_y(initialY), m_en_width(1.0f), m_en_height(1.0f) //m_initial_x(initialX), m_initial_y(initialY)
{


}



void Enemy::init() {
	m_width /= 2.0f;

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_en_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_en_y;
}




void Enemy::moveEnemy(float dt)
{
	//m_en_x += m_max_en_velocity * dt;
}




void Enemy::update(float dt)
{
	//m_en_x += m_max_en_velocity * dt;
	//GameObject::update(dt);


	//moveEnemy(dt);


	//GameObject::update(dt);
}




void Enemy::draw()
{
	graphics::drawRect(m_en_x, m_en_y, 1.0f, 1.0f, m_brush_enemy);
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");


}*/









/*Enemy::Enemy(float initialX, float initialY)
	: GameObject("Enemy"), m_en_x(initialX), m_en_y(initialY),
	m_en_width(1.0f), m_en_height(1.0f) {
	init();
}

void Enemy::init() {
	m_en_width /= 2.0f;
	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");
	// Προσθέστε άλλες αρχικοποιήσεις αν απαιτούνται
}

void Enemy::moveEnemy(float dt) {
	// Υλοποίηση κίνησης εχθρού, αν απαιτείται
}

void Enemy::update(float dt) {
	GameObject::update(dt);
	// Προσθέστε κωδικά για ενημέρωση του εχθρού, αν απαιτείται
}

void Enemy::draw() {
	float x = m_en_x;
	float y = m_en_y;
	float width = m_en_width;
	float height = m_en_height;

	// Σχεδιάζουμε τον εχθρό
	graphics::drawRect(x, y, width, height, m_brush_enemy);
	// Προσθέστε κωδικά για σχεδίαση του εχθρού
}
*/
















/*Enemy::Enemy(float initialX, float initialY)
	: GameObject("Enemy"), m_en_x(initialX), m_en_y(initialY), m_en_width(1.0f), m_en_height(1.0f), m_initial_x(initialX), m_initial_y(initialY)
{
	
	
}



void Enemy::init() {
	m_en_x = 4.0f;
	m_en_y = 8.0f;
	m_width /= 2.0f;

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");

	//m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_initial_x;
	//m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_initial_y;
}




void Enemy::moveEnemy(float dt)
{
	//m_en_x += m_max_en_velocity * dt;
}




void Enemy::update(float dt)
{
	//m_en_x += m_max_en_velocity * dt;
	//GameObject::update(dt);


	//moveEnemy(dt);
	

	//GameObject::update(dt);
}




void Enemy::draw()
{
	graphics::drawRect(m_en_x, m_en_y, 1.0f, 1.0f, m_brush_enemy);
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("bee_hurt.png");
	

}
*/