/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Floor_block.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "floor_block.h"
#include "../Engine/Collision.h"

Floor_block::Floor_block(Math::irect boundary) : GameObject(static_cast<Math::vec2>(boundary.point_1)) {
    AddGOComponent(new CS230::RectCollision({ Math::ivec2{ 0, 0 }, boundary.Size() }, this));
    AddGOComponent(new CS230::Sprite("Assets/woodwall.spt", this));
}
