/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#pragma once
#include "Ship.h"
#include "../Engine/Engine.h"
#include "ScreenWrap.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "Laser.h"

//이 부분 물어보기
Ship::Ship(Math::vec2 position) :
    GameObject(position, 0.0, { scale, scale }), flame_left("Assets/Flame.spt", this), flame_right("Assets/Flame.spt", this)
    //ship_position(ship_position)
   // ship_position(start_position)
{
    AddGOComponent(new ScreenWrap(*this));
    AddGOComponent(new CS230::Sprite("Assets/Ship.spt", this));
    //AddGOComponent(new CS230::Sprite("Assets/Ship.spt"));
    //sprite.Load("Assets/Ship.spt");
 /*   flame_left.Load("Assets/Flame.spt", this);
    flame_right.Load("Assets/Flame.spt", this);*/
    //SetRotation(rotation);
    //SetScale(scale);
    exploded = false;
    // GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
    flame_right.PlayAnimation(static_cast<int>(Flame_Animations::None));
    flame_left.PlayAnimation(static_cast<int>(Flame_Animations::None));
    //velocity = { 0, 0 };
}

//void Ship::Load() {
//    sprite.Load("Assets/Ship.spt");
//    flame_left.Load("Assets/Flame.spt");
//    flame_right.Load("Assets/Flame.spt");
//    velocity = { 0, 0 };
//}



void Ship::Update(double dt) {
    //current_state->Update(this, dt);
    //sprite.Update(dt);

    flame_left.Update(dt);
    flame_right.Update(dt);
    if (Exploded() == false) {
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::W))
        {
            //rotation matrix 질문 있음
            UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0.0, speed * dt });
            //GetMatrix()
            // velocity += Math::RotationMatrix(angle) * Math::vec2{ 0, speed * dt };
            current_W = true;
        }
        else
        {
            current_W = false;
        }

        if (current_W && !previous_W)
        {
            flame_left.PlayAnimation(static_cast<int>(Flame_Animations::Flame));
            flame_right.PlayAnimation(static_cast<int>(Flame_Animations::Flame));
        }
        else if (!current_W && previous_W)
        {
            flame_left.PlayAnimation(static_cast<int>(Flame_Animations::None));
            flame_right.PlayAnimation(static_cast<int>(Flame_Animations::None));
        }

        previous_W = current_W;

        if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
            UpdateRotation(-rotation_speed * dt);
            //angle -= rotation_speed * dt;
        }
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
            UpdateRotation(rotation_speed * dt);
            //angle += rotation_speed * dt;
        }
    }
    UpdateVelocity({ -GetVelocity().x * drag * dt , -GetVelocity().y * drag * dt });

    //velocity -= velocity * drag * dt;

    Engine::GetLogger().LogDebug("Velocity: " + std::to_string(GetVelocity().x) + ", " + std::to_string(GetVelocity().y));

    UpdatePosition({ GetVelocity().x * dt, GetVelocity().y * dt });
    //position += velocity * dt;
    if (Exploded() == false) {
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(3)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(4)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
        }
    }
    //if (GetPosition().x < -GetGOComponent<CS230::Sprite>()->GetFrameSize().x) {
    //    SetPosition({Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / (2.0), GetPosition().y});
    //}
    //if (GetPosition().y < -GetGOComponent<CS230::Sprite>()->GetFrameSize().y) {
    //    SetPosition({ GetPosition().x ,Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / (2.0) });
    //    //ship_position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / (2.0);
    //}
    //if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x/(2.0)) {
    //    SetPosition({ -(double)GetGOComponent<CS230::Sprite>()->GetFrameSize().x , GetPosition().y});
    //    //ship_position.x = - sprite.GetFrameSize().x;
    //}
    //if (GetPosition().y > Engine::GetWindow().GetSize().y + (GetGOComponent<CS230::Sprite>()->GetFrameSize().y / (2.0))) {
    //    SetPosition({ GetPosition().x , 0 - (double)GetGOComponent<CS230::Sprite>()->GetFrameSize().y });
    //    //ship_position.y = - sprite.GetFrameSize().y ;
    //}
    UpdateGOComponents(dt);

    //object_matrix = Math::TranslationMatrix(ship_position);
  //  object_matrix = Math::TranslationMatrix(ship_position) * Math::RotationMatrix(angle) * Math::ScaleMatrix(scale);
}


void Ship::Draw(Math::TransformationMatrix camera_matrix) {

    //camera_matrix = GetMatrix();

    GetGOComponent<CS230::Sprite>()->Draw(GetMatrix());
    if (Exploded() == false) {
        flame_left.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
        flame_right.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
        //camera_matrix = GetMatrix();


        CS230::ShowCollision* show_collision = Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>();
        if (show_collision != nullptr && show_collision->Enabled() == true) {
            // get the RectCollision component and draw the collision box
            CS230::Collision* collision = GetGOComponent<CS230::Collision>();
            if (collision != nullptr) {
                collision->Draw(camera_matrix);
            }

        }

    }

}

void Ship::ResolveCollision(GameObject* other_object)
{

    if (Ship::GetGOComponent<CS230::Collision>()->IsCollidingWith(other_object) && exploded == false) {

        exploded = true;
        Ship::GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Animations::Explosion));
    }

}

bool Ship::CanCollideWith(GameObjectTypes) {
    return true;
}
