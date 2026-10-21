/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode2.h"
#include "Meteor.h"
#include <vector>
#include "../Engine/ShowCollision.h"
#include "Fonts.h"
#include "Particles.h"
#include "../Engine/Particle.h"
#include "../Engine/Timer.h"
#include "Score.h"

Mode2::Mode2() : ship_pointer(nullptr) {}

void Mode2::Load() {
    //gameobjectmanager.Add(&ship);
    //gameobjectmanager.Add(&ship);
    //gameobjectmanager.Add(&ship);
    AddGSComponent(new CS230::GameObjectManager);
    ship_pointer = new Ship({ Engine::GetWindow().GetSize().x / 2.0 , Engine::GetWindow().GetSize().y / 2.0 });
    GetGSComponent<CS230::GameObjectManager>()->Add(ship_pointer);
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision);
#endif
    //gameobjectmanager.Add(new Meteor({ 1.0, 1.0 }));
   //gameobjectmanager.Add(new Meteor({ 1.0, 1.0 }));
   //gameobjectmanager.Add(new Meteor({ 1.0, 1.0 }));
   //gameobjectmanager.Add(new Meteor({ 1.0, 1.0 }));
   //gameobjectmanager.Add(new Meteor({ 1.0, 1.0 }));
    AddGSComponent(new CS230::ParticleManager<Particles::Hit>());
    AddGSComponent(new CS230::ParticleManager<Particles::MeteorBit>());
    GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
    GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
    GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
    GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
    GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
    AddGSComponent(new CS230::Timer(meteor_timer));
    AddGSComponent(new CS230::Score());
    gameover = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Game Over", 0xFFFFFFFF);
    restart = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press R to restart!", 0xFFFFFFFF);
}


void Mode2::Update([[maybe_unused]] double dt) {
    //ship.Update(dt);

    //if (Engine::GetInput().KeyDown(CS230::Input::Keys::Q)) {
    //    Engine::GetGameStateManager().ClearNextGameState();
    //}
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R) && ship_pointer->Exploded() == true) {
        Engine::GetGameStateManager().ReloadGameState();
    }
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    UpdateGSComponents(dt);
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(GetGSComponent<CS230::Score>()->Value()), 0xFFFFFFFF);
    if (!ship_pointer->Exploded()) {
        if (GetGSComponent<CS230::Timer>()->RemainingInt() == 0) {
            GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
            GetGSComponent<CS230::Timer>()->Reset();
        }
    }

}

void Mode2::Unload() {
    //background.Unload();
    ClearGSComponents();
    //GetGSComponent<CS230::GameObjectManager>()->Unload();
}

void Mode2::Draw() {

    Engine::GetWindow().Clear(0x000000FF);
    if (GetGSComponent<CS230::ShowCollision>() != nullptr) {
        GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
        score_texture.Draw(Math::TranslationMatrix(Math::ivec2{ 0, Engine::GetWindow().GetSize().y - 5 - score_texture.GetSize().y }));
        if (ship_pointer->Exploded() == true) {
            gameover.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - gameover.GetSize().x / 2, (Engine::GetWindow().GetSize().y / 8) * 6 }));
            restart.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - restart.GetSize().x / 2,  (Engine::GetWindow().GetSize().y / 8) * 1 }));
        }
    }
    //Math::TransformationMatrix camera_matrix = ship.GetMatrix();
    ////이 부분 물어보기
    ////Math::TransformationMatrix camera_matrix = Math::TransformationMatrix::Reset();

    //gameobjectmanager.DrawAll(camera_matrix);
}
