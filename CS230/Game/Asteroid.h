/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "../Engine/Animation.h"
#include "../Engine/GameObject.h"

class Asteroid : public CS230::GameObject {
public:
    Asteroid(Math::vec2 start_position);
    bool CanCollideWith(GameObjectTypes);
    GameObjectTypes Type() override { return GameObjectTypes::Asteroid; }
    std::string TypeName() override { return "Asteroid"; }
    void ResolveCollision(GameObject* other_object) override;
    // void Update(double dt) override;
     //void Draw(Math::TransformationMatrix camera_matrix) override;

private:

    enum class Animations {
        None,
        Land
    };

    //CS230::Sprite sprite;
    //Math::vec2 start_position;
    /*Math::vec2 position;
    Math::vec2 velocity;
    Math::TransformationMatrix object_matrix;*/
    static constexpr double bounce_velocity = 500;


    //class State {
    //public:
    //    virtual void Enter(Asteroid* asteroid) = 0;
    //    virtual void Update(Asteroid* asteroid, double dt) = 0;
    //    virtual void CheckExit(Asteroid* asteroid) = 0;
    //    virtual std::string GetName() = 0;
    //};

    class State_Bouncing : public  State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Landing : public  State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    State_Landing state_landling;
    State_Bouncing state_bouncing;

    //virtual void change_state(State* new_state);
     //State* current_state = nullptr;
};

