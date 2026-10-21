/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode3.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include "../Game/Background.h"
#include "Knight.h"
#include <vector>

//class Mole;
class Asteroid;
//class CS230::GameObjectManager;

class Mode3 : public CS230::GameState {
public:
    Mode3();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void CreateRandomObject();
    // const Math::vec2& GetPosition() const { return camera; };
    std::string GetName() override { return "Mode3"; }
    static constexpr double gravity = 800;
    static constexpr double floor = 80;
    static constexpr double timer_max = 300;
    double make_time = 5;
    double next_time = 15;
    static constexpr double value = 0;
    int first_turn = 440;

private:
    CS230::Timer* make_timer;
    Knight* knight_ptr;
    CS230::Texture timer_text;
    CS230::Texture score_texture;
    CS230::Texture mission_texture;
    CS230::Texture hp_texture;

};