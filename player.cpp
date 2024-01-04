#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"




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

	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;
	m_pos_x += m_vx * delta_time;

	//Y

	if (m_vy == 0.0f)
		m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;
	m_vy += delta_time * m_gravity;

	m_pos_y += m_vy * delta_time;
}
	

void Player::update(float dt)
{
	



	movePlayer(dt);


	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = 2.0f;
	m_pos_y = 0.0f;
	m_width /= 2.0f;

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

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);
	
	
	int s=0;
	if ( m_pos_x == 0.0f)
	{
		m_brush_player.texture = m_state->getFullAssetPath("run-0000.png");
	}
	else
	{
		if (m_vx > 0) // Προς τα δεξιά
		{
			s = (int)fmod(1000.0f - m_pos_x * 2.0f, m_sprites.size());
			m_brush_player.texture = m_sprites[s];
		}
		else if (m_vx < 0) // Προς τα αριστερά
		{
			s = (int)fmod(1000.0f -m_pos_x * 2.0f, m_sprites2.size());
			m_brush_player.texture = m_sprites2[s];
		}

		
		
	}
	

	

	
}

