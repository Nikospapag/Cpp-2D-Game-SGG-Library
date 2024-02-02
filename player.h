#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "Enemy.h"
#include <list>

class Player : public GameObject , public Box
{
	graphics::Brush m_brush_player;
	std::vector<std::string> m_sprites;
	std::vector<std::string> m_sprites2;

	const float m_accel_horizontal = 10.0f;
	const float m_accel_vertical = 7.5f;
	const float m_max_velocity = 14.0f;
	const float m_gravity = 11.0f;
	bool m_is_jumping = false;
	int last_direction=1;
	

	void movePlayer(float dt);
	void debugDraw();
	int s = 0;
	
	

public:
	Box m_player_box;
	float m_vx = 0.0f;
	float m_vy = 0.0f;

	

	Player(std::string name): GameObject(name){}

	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	

	void increaseLife();
	void decreaseLife();
	int getLife() const;

	
	
	


};

