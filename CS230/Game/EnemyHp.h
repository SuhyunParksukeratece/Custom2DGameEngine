
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  EnemyHp.h
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
    class EnemyHp : public Component {
    public:
        EnemyHp(double set) {
            Set(set);
        }
        int Value() {
            return hp;
        }
        void Update(double dt) override {
            if (hp <= 0) {
                hp = 0;
            }
        }
        void Set(int value) {
            hp = value;
        }
        void Damage(int value) {
            hp -= value;
        }
    private:
        int hp;
        double set;
    };
}