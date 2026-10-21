/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sword.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/


#include "Sword.h"
#include "../Engine/Engine.h"
#include "Mode3.h"
#include "../Engine/Collision.h"
#include "Particles.h"
#include "../Engine/Constants.h"

Sword::Sword(Math::vec2 pos, Math::vec2 scale, Math::vec2 vel)
    : GameObject(pos)
{
    AddGOComponent(new CS230::Sprite("Assets/Swords.spt", this));
    //AddGOComponent(new CS230::Sprite("Assets/Asteroid.spt", this));
    SetVelocity(vel);
    SetRotation(45.0);
}

void Sword::Update(double dt)
{
    double speed = 100.0; 
    SetVelocity(Math::vec2(speed, 0.0)); 

    //GameObject::Update(dt);
    UpdatePosition({ dt * GetVelocity().x, 0 });


    if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x) {
        Destroy();
    }
}

bool Sword::CanCollideWith(GameObjectTypes other_object_type)
{
    if (other_object_type == GameObjectTypes::Spear) {
        return true;
    }
    if (other_object_type == GameObjectTypes::Pony) {
        return true;
    }
    if (other_object_type == GameObjectTypes::Archer) {
        return true;
    }
    if (other_object_type == GameObjectTypes::Item) {
        return true;
    }
    //return false;
}

void Sword::ResolveCollision(GameObject* other_object)
{

    switch (other_object->Type())
    {

    case GameObjectTypes::Spear:
        Destroy();
        break;
    case GameObjectTypes::Pony:
        Destroy();
        break;
    case GameObjectTypes::Archer:
        Destroy();
        break;
    case GameObjectTypes::Item:
        Destroy();
        break;
    case GameObjectTypes::Thorneenemy:
        break;
    }

    if (dynamic_cast<Sword*>(other_object) == nullptr) {
        other_object->ResolveCollision(this);
    }
}