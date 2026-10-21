/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "../Engine/Animation.h"
#include "../Engine/GameObject.h"

class Ship : public CS230::GameObject {
public:
    enum class Flame_Animations
    {
        None,
        Flame
    };

    enum class Ship_Animations
    {
        None,
        Explosion
    };


    Ship(Math::vec2 position);
    //const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    //void Load();
    GameObjectTypes Type() override { return GameObjectTypes::Ship; }
    std::string TypeName() override { return "Ship"; }
    void Update(double dt) override;
    void Draw([[maybe_unused]] Math::TransformationMatrix camera_matrix) override;
    void ResolveCollision(GameObject* other_object) override;
    bool CanCollideWith(GameObjectTypes);
    bool Exploded() { return exploded; }

private:

    //CS230::Sprite sprite;
    CS230::Sprite flame_left;
    CS230::Sprite flame_right;
    //Math::vec2 start_position;
    //Math::vec2 ship_position;
    //static constexpr double SHIP_SPEED = 140;

    //Math::vec2 velocity;
   // Math::TransformationMatrix object_matrix;
    static constexpr double speed = 700;
    static constexpr double drag = 1;
    bool current_W = false;
    bool previous_W = false;
    //bool flame_loop = true;
    static constexpr double scale = 0.75;
    double angle = 0;
    bool exploded = false;
    static constexpr double rotation_speed = 5;

    //State* current_state = nullptr;
};