/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"
#include "Ship.h"
#include "../Engine/GameObjectManager.h"

//class Ship;

class Mode2 : public CS230::GameState {
public:
    Mode2();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Mode2"; }

private:
    Ship* ship_pointer;
    CS230::Texture gameover;
    CS230::Texture restart;
    CS230::Texture score_texture;
    static constexpr double meteor_timer = 4.5;
    // Cat* cat_ptr;
 //CS230::GameObjectManager gameobjectmanager;
 //const float SHIP_SPEED = 300.0f;
// CS230::Sprite ship;
 //Math::vec2 ship_position;
};