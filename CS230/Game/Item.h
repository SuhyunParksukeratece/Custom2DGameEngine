/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Item.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "../Engine/Animation.h"
#include "../Engine/GameObject.h"
#include "Cat.h"
#include "Hp.h"
#include "enemyhp.h"
#include "../Engine/Timer.h"
#include "ItemFall.h"


class Item : public CS230::GameObject {
public:
    //Robot(Math::vec2 position);
    Item(Math::vec2 position, int type);
    //Robot(Math::vec2 position, Mole* cat, double left_boundary, double right_boundary);
    void ResolveCollision(GameObject* other_object) override;
    void Update(double dt) override;
    GameObjectTypes Type() override { return GameObjectTypes::Item; }
    std::string TypeName() override { return "Item"; }

private:
    CS230::ItemFall* itemfall;
    bool check_type = false;
    Math::vec2 stay_1 = { 600, 280 };
    Math::vec2 stay_2 = { 600, 480 };
    Math::vec2 stay = { 600, 80 };

};