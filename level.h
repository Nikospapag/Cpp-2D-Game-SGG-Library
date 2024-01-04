#pragma once
#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include "enemy.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;


	std::list<Enemy*> m_enemies;

	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;

	void drawBlock(int i);
	void checkColissions();

public:
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	


	Level(const std::string& name = "Level0");
	~Level() override;
};
