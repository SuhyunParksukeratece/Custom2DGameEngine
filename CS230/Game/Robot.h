/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
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


class Robot : public CS230::GameObject {
public:
    //Robot(Math::vec2 position);
    Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary);
    void ResolveCollision(GameObject* other_object) override;
    GameObjectTypes Type() override { return GameObjectTypes::Robot; }
    std::string TypeName() override { return "Robot"; }

    enum class Animations {
        None,
        Dead,
        Walking,
        Angry
    };

private:
    static constexpr double walking_speed = 75.0;
    static constexpr double angry_speed = 105.0;
    double left_boundary = 10;
    double right_boundary = 10;
    Cat* cat_p;
    bool turn = false;
    bool turn_angry = true;

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

    class State_Angry : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Dead state_dead;
    State_Walking state_walking;
    State_Angry state_angry;
};