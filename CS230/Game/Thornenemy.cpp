/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Thornenemy.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#pragma once
#include "thornenemy.h"
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

Thornenemy::Thornenemy(Math::vec2 start_position) :
    GameObject(start_position)
    //current_state(&state_landling)
{
    SetScale({ 0.5, 0.5 });

    SetPosition(start_position);
    AddGOComponent(new CS230::Sprite("Assets/thornenemy.spt", this));


}

bool Thornenemy::CanCollideWith(GameObjectTypes) {
    return true;
}

void Thornenemy::ResolveCollision(GameObject* other_object)
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
    }
    if (dynamic_cast<Thornenemy*>(other_object) == nullptr) {
        other_object->ResolveCollision(this);
    }
}