
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Floor_block.h
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

class Floor_block : public CS230::GameObject {
public:
    Floor_block(Math::irect boundary);
    std::string TypeName() override { return "Floor_block"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Floor_block; }
};
