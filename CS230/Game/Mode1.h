/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include "../Game/Background.h"
#include <vector>

class Cat;
class Asteroid;
//class CS230::GameObjectManager;

class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    // const Math::vec2& GetPosition() const { return camera; };
    std::string GetName() override { return "Mode1"; }
    static constexpr double gravity = 800;
    static constexpr double floor = 80;
    static constexpr double timer_max = 60;
    static constexpr double value = 0;

private:
    Cat* cat_ptr;
    CS230::Texture timer_texture;
    CS230::Texture score_texture;
    //CS230::GameObjectManager gameobjectmanager;
    //Asteroid* asteroid;
    //Background background;
    //CS230::Camera camera;
    //Math::vec2 cat_position;

    //void update_timer_text(int value);

    //Cat cat;
    //std::vector<Asteroid> asteroids;
    //const double cat_speed = 140.0;
};