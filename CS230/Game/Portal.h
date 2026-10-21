/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Portal.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "../Engine/Animation.h"
#include "../Engine/GameObject.h"


class Portal : public CS230::GameObject {
public:
    Portal(int to_state, Math::irect boundary);
    std::string TypeName() override { return "Portal"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal; }

    void GoToState();
private:
    int to_state;
};
