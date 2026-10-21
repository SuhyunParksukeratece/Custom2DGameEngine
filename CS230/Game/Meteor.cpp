/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/


#include "Meteor.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Constants.h"
#include "Particles.h"
#include "Score.h"
//Meteor::Meteor()
//{
//	SetVelocity(rand(-defalut_velocity, defalut_velocity));
//}

//Meteor::Meteor(Math::vec2 position) : GameObject(position)
//{
//    SetVelocity({ rand() % (2 * static_cast<int>(default_velocity) + 1) - default_velocity,
//                  rand() % (2 * static_cast<int>(default_velocity) + 1) - default_velocity });
//    SetRotation(rand()%(RAND_MAX + 1));
//    SetPosition({ (double)(rand() % Engine::GetWindow().GetSize().x), (double)(rand() % Engine::GetWindow().GetSize().y)});
//    sprite.Load("Assets/Meteor.spt");
//    //velocity.x = (2.0 * rand() / RAND_MAX - 1.0) * default_velocity;
//    //velocity.y = (2.0 * rand() / RAND_MAX - 1.0) * default_velocity;
//
//    //// Set the rotation to a random angle between 0 and 2 * PI
//    //rotation = 2.0 * PI() * rand() / RAND_MAX;
//}

//Meteor::Meteor() :
//    GameObject({ 0,0 })
//{
//    SetVelocity({ rand() % (2 * static_cast<int>(default_velocity) + 1) - default_velocity,
//                  rand() % (2 * static_cast<int>(default_velocity) + 1) - default_velocity });
//    SetRotation(rand() % (RAND_MAX + 1));
//    SetPosition({ (double)(rand() % Engine::GetWindow().GetSize().x), (double)(rand() % Engine::GetWindow().GetSize().y) });
//    AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));
//    //AddGOComponent(new CS230::Sprite("Assets/Meteor.spt"));
//    //sprite.Load("Assets/Meteor.spt");
//    //sprite.Load("Assets/Meteor.spt");
//}
Meteor::Meteor() : Meteor(nullptr) {}


Meteor::Meteor(Meteor* parent) : CS230::GameObject({ 0, 0 }) {
    AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));
    if (parent == nullptr) {
        SetVelocity(Math::vec2{
            ((double)rand() / RAND_MAX) * default_velocity * 2 - default_velocity,
            ((double)rand() / RAND_MAX) * default_velocity * 2 - default_velocity
            });
        SetPosition({
            ((double)rand() / RAND_MAX) * (Engine::GetWindow().GetSize().x * 2) - Engine::GetWindow().GetSize().x,
            ((double)rand() / RAND_MAX) * (Engine::GetWindow().GetSize().y * 2) - Engine::GetWindow().GetSize().y
            });
        SetRotation(((double)rand() / RAND_MAX) * 2 * Math::PI);

        size = default_size;
    }
    else {
        SetVelocity(parent->GetVelocity());
        SetPosition(parent->GetPosition());
        SetRotation(parent->GetRotation());

        size = parent->size - 1;
    }
    health = default_healths[size];
    SetScale(Math::vec2{ default_scales[size], default_scales[size] });
}


void Meteor::Update(double dt) {
    GameObject::Update(dt);
    UpdatePosition({ dt * GetVelocity().x, dt * GetVelocity().y });

    if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Fade) && GetGOComponent<CS230::Sprite>()->AnimationEnded())
    {
        Destroy();
    }

    Engine::GetLogger().LogDebug("Rotation: " + std::to_string(GetRotation()));

    if (GetPosition().x < -GetGOComponent<CS230::Sprite>()->GetFrameSize().x) {
        SetPosition({ Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / (2.0), GetPosition().y });
    }
    if (GetPosition().y < -GetGOComponent<CS230::Sprite>()->GetFrameSize().y) {
        SetPosition({ GetPosition().x ,Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / (2.0) });
        //ship_position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / (2.0);
    }
    if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / (2.0)) {
        SetPosition({ -(double)GetGOComponent<CS230::Sprite>()->GetFrameSize().x , GetPosition().y });
        //ship_position.x = - sprite.GetFrameSize().x;
    }
    if (GetPosition().y > Engine::GetWindow().GetSize().y + (GetGOComponent<CS230::Sprite>()->GetFrameSize().y / (2.0))) {
        SetPosition({ GetPosition().x , 0 - (double)GetGOComponent<CS230::Sprite>()->GetFrameSize().y });
        //ship_position.y = - sprite.GetFrameSize().y ;
    }
}

void Meteor::ResolveCollision(GameObject* other_object) {
    switch (other_object->Type())
    {
    case GameObjectTypes::Laser:


        Math::vec2 point1 = other_object->GetPosition();
        //Math::vec2 point2 = point1 - GetPosition();
        //point2.Normalize();

        Math::vec2 particle_postion = GetPosition();
        particle_postion -= point1;
        particle_postion.Normalize();
        particle_postion *= GetGOComponent<CS230::CircleCollision>()->GetRadius();


        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Hit>>()
            ->Emit(1, -particle_postion + GetPosition(), GetVelocity(), { 0, 0 }, 0);
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::MeteorBit>>()
            ->Emit(5, -particle_postion + GetPosition(), GetVelocity(), { (-1 * other_object->GetVelocity().x) / 4, -1 * (other_object->GetVelocity().y) / 4 }, Math::PI / 3);

    }

    UpdateVelocity({ 0.01 * other_object->GetVelocity().x, 0.01 * other_object->GetVelocity().y });
    health -= 1;
    if (health < 0) {
        CS230::Score* score = Engine::GetGameStateManager().GetGSComponent<CS230::Score>();
        score->Add(10);
        //Destroy();
        RemoveGOComponent<CS230::Collision>();
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Fade));
        if (size > 0) {
            Meteor* meteor_1 = new Meteor(this);
            meteor_1->SetVelocity(Math::RotationMatrix(Math::PI / 6) * GetVelocity());

            Meteor* meteor_2 = new Meteor(this);
            meteor_2->SetVelocity(Math::RotationMatrix(-Math::PI / 6) * GetVelocity());

            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(meteor_1);
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(meteor_2);
        }
    }

}
