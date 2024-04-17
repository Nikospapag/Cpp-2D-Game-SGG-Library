#include "gamestate.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
#include "util.h"
using namespace std::chrono_literals;

GameState::GameState()
	
{
}
//������������ ��� Level1 ��� ��� player �������� ��� init ��� ����������� ������� ����, ��������� ��� �� ������� ��� ������� ��� wallpaper , ��� ������������� ��� ��� ���� ��� ������
void GameState::init()
{

	showWallpaper = true;
	inEndGame = false;
	win = false;
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();




	if (showWallpaper) {
		
		graphics::playMusic(getFullAssetPath("wall_sound.mp3"), 0.4f, true);
	}
	
	playerLife = 5;

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "waltographUI.ttf");

}

//����������� �� m_current_level ��� �� m_player ��� ������������ �� level2 �� ����� ��������� ��� m_current_level ��� ��� ������ �������� ��� ��� ���������� init ��� ������� ����

void GameState::initLevel2() {

	if (m_current_level)
	{
		delete m_current_level;
		m_current_level = nullptr;
	}

	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	m_level2 = new Level();
	m_level2->init2(); 
	m_current_level = m_level2;

	m_player = new Player("Player");
	m_player->init();
}

//������������ ���� �� wallpaper, ��� ��������� �����, �� ��������� ����� ��� �� ��� ������ ������ ��� ���� �� ���������� level ������������� ��� �� score ��� ��� ������� ���� ��� ������
void GameState::draw()
{
	if (showWallpaper) {
		graphics::Brush wallpaper;
		graphics::Brush text;
		wallpaper.outline_opacity = 0.0f;
		wallpaper.texture = getFullAssetPath("Start.png");
		graphics::drawRect(8.5, 8.5, 17, 17, wallpaper);
		SETCOLOR(text.fill_color, 0.0, 0.0, 0.0);
		return;


	}


	if (inEndGame) {
		graphics::stopMusic();
		graphics::playSound(getFullAssetPath("end.wav"), 0.2f, true);
		graphics::setFont(m_asset_path + "Montague.ttf");
		graphics::Brush end_wallpaper;
		graphics::Brush end_text;
		end_wallpaper.texture = getFullAssetPath("gameover.png");
		end_wallpaper.outline_opacity = 0.0f;
		graphics::drawRect(8, 9, 20, 20, end_wallpaper);
		SETCOLOR(end_text.fill_color, 0.0, 0.0, 0.0);
		graphics::drawText(4.0, 2.0f, 2.0f, "GAME OVER", end_text);
		graphics::drawText(4.2f, 16.5f, 2.0f, "SCORE: " + std::to_string(score), end_text);
		return;
	}




	if (win) {
		graphics::stopMusic();
		graphics::playSound(getFullAssetPath("win.mp3"), 0.1f, true);
		graphics::setFont(m_asset_path + "Montague.ttf");
		graphics::Brush win_wallpaper;
		graphics::Brush win_text;
		win_wallpaper.texture = getFullAssetPath("win2.png");
		win_wallpaper.outline_opacity = 0.0f;
		graphics::drawRect(8, 9, 20, 20, win_wallpaper);
		SETCOLOR(win_text.fill_color, 1.0, 1.0, 1.0);
		if (score<= 2500) { //��������� ����� �����
			grade = "C";
		}else if( score<=4500){
			grade = "B";
		}
		else {
			grade = "A";
		}
		graphics::drawText(1.0f, 1.2f, 1.5f, "YOU WIN WITH GRADE="+grade, win_text);
		graphics::drawText(9.8f, 2.3f, 1.4f, "SCORE: " + std::to_string(score), win_text);
		return;
	}

	if (m_current_level) {
		m_current_level->draw();
		drawScore();
		drawLife();
	}

}

//������� ��� update ��� ��������� �� ���� ��������� ������� �������� ��� ����������� ���������.�� � ��� ����� ��� �� 0 ����������� �� m_current_level ��� ��� player,���������� ��� �� �� win ����� 0.
void GameState::update(float dt)
{

	if (dt > 500) // ms
		return;

	float sleep_time = std::max(0.0f, 17.0f - dt);
	
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	

	if (showWallpaper) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			showWallpaper = false;
			graphics::stopMusic();
			graphics::playMusic(getFullAssetPath("bees_sound.wav"), 0.3f, true);
			
		}
		return;
		
	}
	
		
	if (playerLife <= 0) {
			inEndGame = true;
			delete m_current_level;
			m_current_level = nullptr;

			delete m_player;
			m_player = nullptr;
			return;
	}


	
	
	if (win){
		
		delete m_current_level;
		m_current_level = nullptr;

		

		delete m_player;
		m_player = nullptr;
		return;
	}

	if (m_current_level){
	showWallpaper = false;
	m_current_level->update(dt);


	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	}
}

//������� ������� update �� score
void GameState::updateScore(int amount) {
	score += amount;
}
//������������ �� score
void GameState::drawScore() {
	graphics::Brush text;
	text.fill_opacity = 1.0f;
	SETCOLOR(text.fill_color, 0.0f, 0.0f, 0.0f);
	graphics::drawText(0.8f, 0.6f, 0.7f, "SCORE: " + std::to_string(score), text);
}

//��������� �� ��� ��� ������
void GameState::increasePlayerLife() {
	if (playerLife < 5) {
		++playerLife;

	}
}

//��������� �� ��� ��� ������
void GameState::decreasePlayerLife()
{
	if (playerLife > 0) {
		--playerLife;
		
	}
}
//������������ �� ��� ��� ������
void GameState::drawLife()
{
	
	
	
	
	graphics::Brush lifes;
	lifes.outline_opacity = 0.0f;
	lifes.texture = getFullAssetPath("heart.png");
	float first_x = 16.5f;
	float heart_size = 0.7f;
	float space = 0.7f;

	for (int i = 0; i < playerLife; ++i) {
		float x = first_x;
		graphics::drawRect(x, 0.5f, heart_size, heart_size, lifes);
		first_x=first_x-1;
	}
}




GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();
	return m_unique_instance;
}

//����������� ��� �������������� �� new ��� ������������ ������
GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
	
	if (m_level2)
		delete m_level2;
		
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








