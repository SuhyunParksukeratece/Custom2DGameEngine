#pragma once
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Thornenemy.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "../Engine/Animation.h"
#include "../Engine/GameObject.h"

class Thornenemy : public CS230::GameObject {
public:
    Thornenemy(Math::vec2 start_position);
    bool CanCollideWith(GameObjectTypes);
    GameObjectTypes Type() override { return GameObjectTypes::Thorneenemy; }
    std::string TypeName() override { return "Thorneenemy"; }
    void ResolveCollision(GameObject* other_object) override;

private:

    static constexpr double bounce_velocity = 500;

};
