/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sword.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "../Engine/Animation.h"
#include "../Engine/GameObject.h"



class Sword : public CS230::GameObject {
public:
    Sword(Math::vec2 pos, Math::vec2 scale, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Sword; }
    std::string TypeName() override { return "Sword"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    static constexpr double DefaultVelocity = 600;
};

