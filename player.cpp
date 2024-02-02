#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "enemy.h"
#include "box.h"  ///αν χρειαζεται
#include <list>
#include <iostream>
#include "util.h"
#include <cmath>

//Ορίζουμε την κίνηση του player στον αξονα X και Y
void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;

	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A)) 
		move -= 1.0f;
		
	
	if (graphics::getKeyState(graphics::SCANCODE_D))
		move += 1.0f;
		
	//X
	m_vx = std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max(-m_max_velocity, m_vx);

	if (move > 0)
		last_direction = 1;
	else if (move < 0)
		last_direction = -1;

	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;
		
	m_pos_x += m_vx * delta_time;

	//Y



	if (graphics::getKeyState(graphics::SCANCODE_W) && m_vy == 0.0f) {
		m_vy -= m_accel_vertical;
		m_is_jumping = true;
	}

	if (m_is_jumping && !graphics::getKeyState(graphics::SCANCODE_W)) {
		m_is_jumping = false; // Το άλμα ολοκληρώθηκε
	}

	

	m_vy += delta_time * 1.2f * m_gravity;

	m_pos_y += m_vy * delta_time;
}
	
//Οριζουμε την update της player και το m_player_box για τα collision
void Player::update(float dt)
{
	

	m_player_box.m_pos_x = m_pos_x;
	m_player_box.m_pos_y = m_pos_y;
	m_player_box.m_width = m_width;
	m_player_box.m_height = m_height;

	movePlayer(dt);
	
	


	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}
//Η init της player και το φορτωμα στην m_sprites και m_sprites2 των εικόνων που θέλουμε να εναλλάσονται κατά τη κινηση του player
void Player::init()
{
	m_pos_x = 2.0f;
	m_pos_y = 1.0f;
	m_width /= 2.0f;
	m_is_jumping = false;
	last_direction = 1;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("run-0000.png");


	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;


	
	m_sprites.push_back(m_state->getFullAssetPath("run-0001.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0002.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0003.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0004.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0005.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0006.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0007.png"));
	m_sprites.push_back(m_state->getFullAssetPath("run-0008.png"));
	
	
	m_sprites2.push_back(m_state->getFullAssetPath("run-0021.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0022.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0023.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0024.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0025.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0026.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0027.png"));
	m_sprites2.push_back(m_state->getFullAssetPath("run-0028.png"));



}
//Η draw της player και αναλογα τη κινηση του παικτη οι εικονες που πρεπει να εχει
void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);


	//int s = 0;
	if (m_pos_x == 0.0f)
	{
		m_brush_player.texture = m_state->getFullAssetPath("run-0000.png");
	}
	else
	{
		if (m_is_jumping) // Εαν πηδαει ο παικτης
		{
			if (m_vx > 0) // κινηση προς τα δεξια
			{

				m_brush_player.texture = m_state->getFullAssetPath("jump.png");
			}
			else if (m_vx < 0) // Κίνηση προς τα αριστερα
			{
				m_brush_player.texture = m_state->getFullAssetPath("jump_left.png");
			}

			if (m_vx == 0)
			{
				if (last_direction > 0) // Προς τα δεξια
				{
					m_brush_player.texture = m_state->getFullAssetPath("jump.png");
				}
				else if (last_direction < 0) // Προς τα αριστερα
				{
					m_brush_player.texture = m_state->getFullAssetPath("jump_left.png");
				}
			}

		}

		else if (m_vx > 0) 
		{

			s = (int)fmod(1000.0f - m_pos_x * 2.0f, m_sprites.size());

			m_brush_player.texture = m_sprites[s];


		}

		else if (m_vx < 0) 
		{
			s = (int)fmod(1000.0f - m_pos_x * 2.0f, m_sprites2.size());

			m_brush_player.texture = m_sprites2[s];





		}


		else
		{

			if (m_vx == 0) // Αν ο παίκτης δεν κινείται βλεπουμε ποια ηταν η τελευταια κινηση του και βαζουμε την αντιστοιχη φωτογραφια
			{
				if (last_direction > 0) 
				{

					m_brush_player.texture = m_state->getFullAssetPath("run-0000.png");
				}
				else if (last_direction < 0) 
				{

					m_brush_player.texture = m_state->getFullAssetPath("run-0020.png");

				}
			}
		}
	}

	if (m_state->m_debugging)
		debugDraw();
	

}

//Καλουμε την decreasePlayerLife() της gamestate για να μειωσουμε τη ζωη
void Player::decreaseLife() {
	
	m_state->decreasePlayerLife();
}
//Καλουμε την increasePlayerLife() της gamestate για να αυξησουμε τη ζωη
void Player::increaseLife() {
	m_state->increasePlayerLife();
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}

