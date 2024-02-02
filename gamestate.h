#pragma once
#include "sgg/graphics.h"
#include <string>


class GameState
{
private:

	std::string m_asset_path = "assets\\";
	float m_canvas_width = 17.0f;
	float m_canvas_height = 17.0f;

	static GameState* m_unique_instance;

	GameState();
	
	
	class Player* m_player = 0;
	bool inEndGame;
	bool showWallpaper;
	int score;
	std::string grade;
	
public:
	class Level* m_level2 = 0;
	//bool win = false;
	bool win;
	class Level* m_current_level = 0;
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;
	
	void drawScore();
	void updateScore(int amount);
	int playerLife;
	void decreasePlayerLife();
	void increasePlayerLife();
	void drawLife();
	void init();
	void draw();
	void update(float dt);
	void initLevel2();
	

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer() {
		return m_player;
	}

	void EndGame();


};
