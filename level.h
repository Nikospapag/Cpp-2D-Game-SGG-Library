#pragma once
#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include "enemy.h"
#include "Coins.h"
#include "Hearts.h"
#include "gate.h"


class Level : public GameObject
{
	graphics::Brush m_brush_background;
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	int ScoreLevel;
	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	std::list<Hearts*> hearts;
	std::list<Enemy*> m_enemies;
	std::list<Coins*> coins;
	

	Gate* gate1;
	Enemy* enemyToDelete;
	Coins* coinToDelete;
	Hearts* heartToDelete;
	
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	
	
	
	void checkPlayerGate();
	void drawBlock(int i);
	void checkColissions();
	void checkPlayerHeartscoll();
	void checkPlayerEnemyCollision();

	void checkPlayerCoinsCollision();
	void effect();



public:
	
	virtual void update(float dt) override;
	void init2();
	virtual void init() override;
	virtual void draw() override;
	
	

	Level(const std::string& name = "Level0");
	~Level() override;
};
