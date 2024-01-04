#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"

class Player : public GameObject , public Box
{
	graphics::Brush m_brush_player;
	std::vector<std::string> m_sprites;
	std::vector<std::string> m_sprites2;

	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 7.5f;
	const float m_max_velocity = 31.0f;
	const float m_gravity = 11.0f;

	void movePlayer(float dt);

public:

	float m_vx = 0.0f;
	float m_vy = 0.0f;

	Player(std::string name): GameObject(name){}

	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;



};