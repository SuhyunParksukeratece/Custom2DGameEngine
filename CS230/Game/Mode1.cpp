/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/


#include "Mode1.h"
#include "States.h"
#include "../Engine/Engine.h"
#include "../Game/Asteroid.h"
#include "../Game/Cat.h"
#include "../Game/Crates.h"
#include "../Game/Robot.h"
#include "Fonts.h"
#include "../Game/Gravity.h"
#include "../Game/Background.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/ShowCollision.h"
#include "Floor.h"
#include "Portal.h"
#include "Score.h"
#include <vector>
#include "Particles.h"
//#include "../Engine/GameObjectManager.h"

Mode1::Mode1() : cat_ptr(nullptr)
//cat_ptr(new Cat({ 300, floor }, camera)),
//camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } })
{
    //gameobjectmanager = new CS230::GameObjectManager();
    //cat_ptr = new Cat(Math::vec2{ 100, 100 }, camera);
    //asteroids.push_back(Asteroid({ 600, floor }));
    //asteroids.push_back(Asteroid({ 1800, floor }));
    //asteroids.push_back(Asteroid({ 2400, floor }));
}



void Mode1::Update(double dt) {
    // cat_ptr->Update(dt);
     //asteroids[0].Update(dt);
     //asteroids[1].Update(dt);
     //asteroids[2].Update(dt);
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<CS230::Camera>()->Update(cat_ptr->GetPosition());

    //GetGSComponent<CS230::Timer>()->Update(dt);

    //if (static_cast<int>(GetGSComponent<CS230::Timer>()->GetTimer()) < GetGSComponent<CS230::Timer>()->GetLastTimer()) {
    //    GetGSComponent<CS230::Timer>()->GetLastTimer() = static_cast<int>(GetGSComponent<CS230::Timer>()->GetTimer());
    //    GetGSComponent<CS230::Timer>()->update_timer_text(GetGSComponent<CS230::Timer>()->GetLastTimer());
    //   // update_timer_text(last_timer);
    //}
    if (GetGSComponent<CS230::Timer>()->RemainingInt() == 0) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadGameState();
    }

    timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(GetGSComponent<CS230::Timer>()->RemainingInt()), 0xFFFFFFFF);
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(GetGSComponent<CS230::Score>()->Value()), 0xFFFFFFFF);
}

void Mode1::Unload() {
    //GetGSComponent<Background>()->Unload();
    //GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
    cat_ptr = nullptr;
}


void Mode1::Load() {

    //timer = timer_max;
    //last_timer = static_cast<int>(timer_max);
    //update_timer_text(last_timer);
    //Áú¹® (22 page)
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision);
#endif
    AddGSComponent(new Gravity(gravity));
    AddGSComponent(new CS230::GameObjectManager);
    AddGSComponent(new Background());
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());
    //AddGSComponent(new Score());
    AddGSComponent(new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));
    GetGSComponent<Background>()->Add("Assets/Foreground.png", 1.0);
    GetGSComponent<Background>()->Add("Assets/Planets.png", 0.25);
    GetGSComponent<Background>()->Add("Assets/Ships.png", 0.5);
    GetGSComponent<Background>()->Add("Assets/Foreground.png", 1.0);
    // GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 400, 100 }, { 700, 50 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Portal(static_cast<int>(States::Menu), Math::irect{ {5750, 50}, {5850, 200} }));

    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 930, static_cast<int>(floor) } });
    GetGSComponent<CS230::GameObjectManager>()->Add(starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1014, 0 }, { 2700, static_cast<int>(floor) } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 2884, 0 }, { 4126, static_cast<int>(floor) } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 4208, 0 }, { 5760, static_cast<int>(floor) } }));

    cat_ptr = new Cat({ 300, floor }, starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(cat_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Asteroid({ 600, floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Asteroid({ 1800, floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Asteroid({ 2400, floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 900, floor }, 2));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 1400, floor }, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 2000, floor }, 5));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 4000, floor }, 3));

    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 5200, floor }, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 5400, floor }, 3));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 5600, floor }, 5));
    //GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 1200, Mode1::floor }));
    //GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 2200, Mode1::floor }));
    //GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 3400, Mode1::floor }));
    //GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 4200, Mode1::floor }));
    //GetGSComponent<CS230::Timer>()->GetTimer() = GetGSComponent<CS230::Timer>()->GetTimerMax();
    //GetGSComponent<CS230::Timer>()->GetLastTimer() = GetGSComponent<CS230::Timer>()->GetTimerMax();
   // GetGSComponent<CS230::Timer>()->update_timer_text(GetGSComponent<CS230::Timer>()->GetLastTimer());
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 1025, floor }, cat_ptr, 1025, 1350));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 2050, floor }, cat_ptr, 2050, 2325));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 3400, floor }, cat_ptr, 3400, 3800));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 4225, floor }, cat_ptr, 4225, 4800));
    GetGSComponent<CS230::Camera>()->SetPosition({ 0 , 0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0 , 0 } , { GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize() } });
    //AddGSComponent(new CS230::Timer(timer_max));
    AddGSComponent(new CS230::Timer(timer_max));
    AddGSComponent(new CS230::Score());
    //AddGSComponent(new CS230::Score(value));

}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0x000000FF);

    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::Camera>()->GetMatrix();

    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
    //cat_ptr->Draw(camera_matrix);
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);
    /* CS230::Texture hello = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Hello!", 0x000000FF);
     hello.Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));*/
     /*for (Asteroid& asteroid : asteroids) {
         asteroid.Draw(camera_matrix);
     }*/

    timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - 5 - timer_texture.GetSize().y }));
    score_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - score_texture.GetSize().x, Engine::GetWindow().GetSize().y - 70 - score_texture.GetSize().y }));
    //timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0}));
    //timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 5 }));

}