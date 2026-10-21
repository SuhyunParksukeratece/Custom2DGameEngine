/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Spear.h
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
#include "Hp.h"
#include "enemyhp.h"
#include "../Engine/Timer.h"


class Spear : public CS230::GameObject {
public:
    //Robot(Math::vec2 position);
    Spear(Math::vec2 position, double left_boundary, double right_boundary);
    //Robot(Math::vec2 position, Mole* cat, double left_boundary, double right_boundary);
    void ResolveCollision(GameObject* other_object) override;
    GameObjectTypes Type() override { return GameObjectTypes::Spear; }
    std::string TypeName() override { return "Spear"; }

    enum class Animations {
        Idle,
        Running,
        Dead
    };

private:
    static constexpr double walking_speed = 75.0;
    static constexpr double angry_speed = 105.0;
    double left_boundary = 10;
    double right_boundary = 10;
    //Cat* cat_p;
    //Mole* mole_p;
    CS230::EnemyHp* enemyhp;
    CS230::Timer* dead_timer;
    static constexpr double dead_time = 4.0;

    CS230::Timer* hp_timer;
    static constexpr double hp_time = 3.0;

    bool turn = false;
    bool turn_angry = true;
    double health;
    //CS230::Hp* spear_hp;

    class State_Dead : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dead"; }
    };

    class State_Walking : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Walking"; }
    };

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Dead state_dead;
    State_Walking state_walking;
    State_Idle state_idle;
};