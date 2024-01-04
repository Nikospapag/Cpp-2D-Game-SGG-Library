#pragma once
#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>


class Enemy : public GameObject, public Box {
    float m_en_x;
    float m_en_y;
    float m_en_width;
    float m_en_height;
    const float en_accel_horizontal = 1.0f;
    const float en_max_velocity = 1.0f;
    //float m_initial_x;
    //float m_initial_y;
    graphics::Brush m_brush_enemy;
    float m_movement_timer;

    void moveEnemy(float dt);
    
    //void resetMovementTimer();

public:


    Enemy(float initialPosX, float initialPosY);
    virtual void update(float dt) override;
    virtual void init() override;
    virtual void draw() override;
    
    
};