/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 4, 2023
*/

#pragma once
#include "Asteroid.h"
#include "../Engine/Engine.h"
#include "Mode1.h"
#include "../Engine/Collision.h"

//Asteroid::Asteroid(Math::vec2 position)  :
//	//start_position(start_position),
//	position(position),
//    velocity(position)
//{
//    velocity = { 0, 0 };
//        //position =  start_position ;
//    	sprite.Load("Assets/Asteroid.spt");
//        current_state = &state_landling;
//        current_state->Enter(this);
//}

Asteroid::Asteroid(Math::vec2 start_position) :
    GameObject(start_position)
    //current_state(&state_landling)
{
    // SetVelocity({ 0, 0 });
     //SetPosition(start_position);
    AddGOComponent(new CS230::Sprite("Assets/Asteroid.spt", this));
    //AddGOComponent(new CS230::Sprite("Assets/Asteroid.spt"));

    current_state = &state_landling;
    current_state->Enter(this);
}

bool Asteroid::CanCollideWith(GameObjectTypes) {
    return true;
}
//void Asteroid::Update(double dt) {
//    current_state->Update(this, dt);
//    sprite.Update(dt);
//    //UpdatePosition(dt * GetVelocity());
//    UpdatePosition({ 0, dt * GetVelocity().y});
//    current_state->CheckExit(this);
//}

//void Asteroid::Load() {
//    velocity = { 0, 0 };
//    position =  start_position ;
//	sprite.Load("Assets/Asteroid.spt");
//    current_state = &state_landling;
//    current_state->Enter(this);
//    //state_landling.Enter(this);
//}



//void Asteroid::Draw(Math::TransformationMatrix camera_matrix)
//{
//    
//    sprite.Draw(camera_matrix * object_matrix);
//    //sprite.Draw(position - camera.GetPosition());
//}

//void Asteroid::change_state(State* new_state) {
//    Engine::GetLogger().LogDebug("Asteroid Leaving State: " + current_state->GetName());
//    Engine::GetLogger().LogDebug("Asteroid Entering State: " + new_state->GetName());
//    current_state = new_state;
//    current_state->Enter(this);
//}


void Asteroid::State_Bouncing::Enter(GameObject* object)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    //asteroid->sprite.PlayAnimation(static_cast<int>(Animations::None));
    asteroid->SetVelocity({ asteroid->GetVelocity().x, bounce_velocity });
    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
    //asteroid->velocity.y = bounce_velocity;
}

void Asteroid::State_Bouncing::Update(GameObject* object, double dt)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->UpdateVelocity({ 0, (-Mode1::gravity * dt) });
    //asteroid->velocity.y -= Mode1::gravity * dt;
    //asteroid->position += asteroid->velocity * dt;

    /*if (asteroid->position.y < Mode1::floor)
    {
        asteroid->position.y = Mode1::floor;
        asteroid->velocity.y = 0;

    }*/
}

//void Asteroid::State_Bouncing::CheckExit(Asteroid* asteroid)
//{
//    asteroid->sprite.PlayAnimation(static_cast<int>(Animations::None));
//    if (asteroid->position.y <= Mode1::floor)
//    {
//        asteroid->change_state(&asteroid->state_landling);
//    }
//}



void Asteroid::State_Bouncing::CheckExit(GameObject* object) {
    //Asteroid* asteroid = static_cast<Asteroid*>(object);
    //if (asteroid->GetPosition().y < Mode1::floor) {
    //    asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });
    //    asteroid->SetVelocity({ 0, 0 });
    //    asteroid->change_state(&asteroid->state_landling);
    //}
}

void Asteroid::ResolveCollision(GameObject* other_object)
{
    //Math::rect cat_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    Math::rect other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
    if (other_object->Type() == GameObjectTypes::Floor) {
        //  Asteroid* asteroid = static_cast<Asteroid*>(object);
        SetPosition({ GetPosition().x, other_rect.Top() });
        SetVelocity({ 0, 0 });
        change_state(&state_landling);
    }
}


void Asteroid::State_Landing::Enter(GameObject* object)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Land));
    // asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });
    asteroid->SetVelocity({ asteroid->GetVelocity().x, 0 });
    // asteroid->ended = false; 
}

void Asteroid::State_Landing::Update(GameObject* asteroid, double dt)
{
}

void Asteroid::State_Landing::CheckExit(GameObject* object)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    //object->change
    if (asteroid->GetGOComponent<CS230::Sprite>()->AnimationEnded())
    {
        // asteroid->ended = true;
        asteroid->change_state(&asteroid->state_bouncing);
    }
    // asteroid->change_state(&asteroid->state_bouncing);
     /*if (asteroid->position.y <= Mode1::floor)
     {
         asteroid->change_state(&asteroid->state_bouncing);
     }*/
}