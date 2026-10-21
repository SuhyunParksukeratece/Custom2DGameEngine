/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particle.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 4, 2023
*/


#include "Particle.h"
#include "../Engine/GameObjectManager.h"


CS230::Particle::Particle(const std::filesystem::path& sprite_file) : GameObject({ 0,0 })
{
    AddGOComponent(new CS230::Sprite(sprite_file, this));
    life = 0.0;
}


void CS230::Particle::Start(Math::vec2 position, Math::vec2 velocity, double max_life)
{
    SetPosition(position);
    SetVelocity(velocity);
    life = max_life;
    Particle::GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(0));
}

void CS230::Particle::Update(double dt)
{
    if (Alive())
    {
        life -= dt;

        GameObject::Update(dt);
    }
}

void CS230::Particle::Draw(Math::TransformationMatrix camera_matrix)
{
    if (Alive())
    {
        CS230::GameObject::Draw(camera_matrix);
    }
}

