/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Knight.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 4, 2023
*/

#pragma once
#include "..\Engine\Input.h"
#include "../Engine/Matrix.h"
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectTypes.h"
#include "../Engine/Timer.h"
#include "Hp.h"



class Knight : public CS230::GameObject {
public:
    Knight(Math::vec2 position, GameObject* standing_on);
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    //const Math::vec2& GetPosition() const { return position; };
    GameObjectTypes Type() override { return GameObjectTypes::Knight; }
    std::string TypeName() override { return "Knight"; }
    void Draw(Math::TransformationMatrix camera_matrix);
    void ResolveCollision(GameObject* other_object) override;
    //void Load() override;
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes);
    bool Exploded() { return exploded; }
    // void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    enum class Animations {
        Idle,
        Jumping,
        Dead,
        Attack,
        Falling
    };

    CS230::Timer* shot_timer;
    CS230::Timer* dead_timer;
    static constexpr double dead_time = 2.0;
    static constexpr double shot_time = 2.0;
    bool exploded = false;
    // CS230::Sprite sprite;
    //// Math::vec2 start_position;
    // Math::vec2 position;
    // Math::vec2 velocity;
     //const double speed = 140;
    double check_y = 0.0;
    static constexpr double x_acceleration = 150;//between 100 - 600
    static constexpr double x_drag = 450; //between 1 - 200
    static constexpr double max_velocity = 300; //between 100 - 600
    static constexpr double jump_velocity = 800;

    static constexpr double hurt_time = 2.0;
    static constexpr double hurt_velocity = 350;
    static constexpr double hurt_acceleration = 300;
    static constexpr double bounce_velocity = 700;
    static constexpr double pop_velocity = 400;
    static constexpr double LargeFallHeight = 250.0;

    CS230::Hp* knight_hp;
    GameObject* standing_on = nullptr;
    // bool flipped = false;

     //Math::TransformationMatrix object_matrix;
    // const CS230::Camera& camera;

     //object state machines
    void update_x_velocity(double dt);

    //class State {
    //public:
    //    virtual void Enter(Cat* cat) = 0;
    //    virtual void Update(Cat* cat, double dt) = 0;
    //    virtual void CheckExit(Cat* cat) = 0;
    //    virtual std::string GetName() = 0;
    //};

    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Dead : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    class State_Attack : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    State* check_state;
    State_Dead state_dead;
    State_Jumping state_jumping;
    State_Attack state_attack;
    State_Idle state_idle;
    State_Falling state_falling;

    //virtual void change_state(State* new_state);
   // State* current_state = nullptr;

};
