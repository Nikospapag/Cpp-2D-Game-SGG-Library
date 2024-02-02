#pragma once
#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>


class Enemy : public GameObject, public Box {
    
    const float en_accel_horizontal = 2.0f;

    float m_en_direction=-1.0f; // 1.0f για κινηση προς τα δεξια, -1.0f για κινηση προς τα αριστερα
    float m_en_speed=3.6f;
   // float m_movement_timer;
    std::vector<std::string> enemy_sprites;
    std::vector<std::string> enemy_sprites2;
    int s = 0;
    void moveEnemy(float dt);
    

    
    
    void debugDraw();
public:
    graphics::Brush m_brush_enemy;
    Box m_enemy_box;
    float m_en_x;
    float m_en_y;
    float m_en_width;
    float m_en_height;

    Enemy(float initialPosX, float initialPosY);
    virtual void update(float dt) override;
    virtual void init() override;
    virtual void draw() override;



    void setActive(bool active) {
        GameObject::setActive(active);
        
    }

    
    
};

