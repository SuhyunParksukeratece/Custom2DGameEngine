/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Laser.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/


#include "Laser.h"
#include "../Engine/Engine.h"
#include "Mode2.h"
#include "../Engine/Collision.h"
//#include "../Engine/Particle.h"
#include "Particles.h"
#include "../Engine/Constants.h"

Laser::Laser(Math::vec2 pos, double rot, Math::vec2 scale, Math::vec2 vel)
    : GameObject(pos, rot, scale)
{
    AddGOComponent(new CS230::Sprite("Assets/Laser.spt", this));
    //AddGOComponent(new CS230::Sprite("Assets/Asteroid.spt", this));
    SetVelocity(vel);
}

void Laser::Update(double dt)
{
    //GameObject::Update(dt);
    UpdatePosition({ dt * GetVelocity().x, dt * GetVelocity().y });

    if (GetPosition().x < -GetGOComponent<CS230::Sprite>()->GetFrameSize().x) {
        Destroy();
    }
    if (GetPosition().y < -GetGOComponent<CS230::Sprite>()->GetFrameSize().y) {
        Destroy();
    }
    if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / (2.0)) {
        Destroy();
    }
    if (GetPosition().y > Engine::GetWindow().GetSize().y + (GetGOComponent<CS230::Sprite>()->GetFrameSize().y / (2.0))) {
        Destroy();
    }
}

bool Laser::CanCollideWith(GameObjectTypes other_object_type)
{
    if (other_object_type == GameObjectTypes::Meteor) {
        return true;
    }
    //return false;
}

void Laser::ResolveCollision(GameObject* other_object)
{

    Destroy();
    other_object->ResolveCollision(this);
}
