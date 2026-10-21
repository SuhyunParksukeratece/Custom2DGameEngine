
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ItemFall.h
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

namespace CS230 {
    class ItemFall : public Component {
    public:
        ItemFall(Math::vec2 delta) {
            Set(delta);
        }
        Math::vec2 Value() {
            return delta;
        }
        void Set(Math::vec2 newPosition) {
            delta = newPosition;
        }
    private:
        Math::vec2 position;
        Math::vec2 delta;
    };
}