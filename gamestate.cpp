#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "enemy.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();

	//m_enemy = new Enemy("Enemy1", 5.0f, 5.0f);
	//m_enemy->init();


	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");

}

void GameState::draw()
{
	if (!m_current_level)
		return;

	m_current_level->draw();
}

void GameState::update(float dt)
{
	/* Για κεραυνους αν θελουμε
	float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 1500.0f));
	SETCOLOR(state.m_brush_bkgnd.fill_color, p, p, p);
	*/

	if (dt > 500) // ms
		return;

	float sleep_time = std::max(0.0f, 17.0f - dt);
	
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	


	if (!m_current_level)
		return;

	m_current_level->update(dt);
	
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();
	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
	//if (m_enemy)
		//delete m_enemy;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path+asset;
}


GameState* GameState:: m_unique_instance=nullptr;
