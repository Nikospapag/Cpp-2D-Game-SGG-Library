#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h"
#include "gamestate.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>



void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	/*std::string& name = m_block_names[i];*/

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);

	graphics::drawRect(x, y, 1.0f * m_block_size, 1.0f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
}

void Level::checkColissions()
{
	

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectUp(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}



			
		

	}


	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
		
	}

	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			
			break;
		}
	}


}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	checkColissions();
	GameObject::update(dt);

	for (auto enemy : m_enemies) {
		if (enemy) {
			enemy->update(dt);
		}
	}
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("forestt.png");

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();


	std::ifstream levelFile(m_state->getFullAssetPath("level1.txt"));
	if (!levelFile) {
		std::cerr << "Unable to open level file!" << std::endl;
		return;
	}

	std::string line;
	int y = 0; // Current line number
	while (std::getline(levelFile, line)) {
		for (int x = 0; x < line.length(); ++x) {
			if (line[x] == '1') { // Assuming '1' represents a block
				m_blocks.push_back(Box(x * m_block_size, y * m_block_size, m_block_size, m_block_size));
				m_block_names.push_back("ground.png");
			}
		}
		++y;
	}

	m_enemies.push_back(new Enemy(37.0f, 3.0f));
	m_enemies.push_back(new Enemy(32.0f, 3.0f));
	m_enemies.push_back(new Enemy(31.0f, 3.0f));
	m_enemies.push_back(new Enemy(23.0f, 5.0f));
	m_enemies.push_back(new Enemy(23.0f, 5.0f));
	m_enemies.push_back(new Enemy(23.0f, 5.0f));
	m_enemies.push_back(new Enemy(23.0f, 7.0f));
	m_enemies.push_back(new Enemy(23.0f, 7.0f));
	m_enemies.push_back(new Enemy(23.0f, 7.0f));
	m_enemies.push_back(new Enemy(23.0f, 11.0f));
	m_enemies.push_back(new Enemy(23.0f, 11.0f));
	m_enemies.push_back(new Enemy(23.0f, 11.0f));

	for (auto enemy : m_enemies) {
		if (enemy) {
			enemy->init();
		}
	}


	//.push_back(new Enemy("Enemy1", 0.0f, 5.0f));  // Δεύτερη σειρά, έκτη στήλη
	//m_enemies.push_back(new Enemy("Enemy2", 1.0f, 4.0f));   // Τέταρτη σειρά, έβδομη στήλη


	//for (auto enemy : m_enemies)
		//if (enemy) enemy->init();
	//m_enemies.push_back(new Enemy("Enemy2", 8.0f, 8.0f));



	levelFile.close();


	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);


}




void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;
 
	//draw background
	graphics::drawRect(offset_x, offset_y, 2.0f * w, 12.0f * w, m_brush_background);

	

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
		
	}


	for (auto enemy : m_enemies) {
		if (enemy) {
			enemy->draw();
		}
	}
	
}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;

	for (auto enemy : m_enemies) {
		if (enemy) delete enemy;
	}

}

