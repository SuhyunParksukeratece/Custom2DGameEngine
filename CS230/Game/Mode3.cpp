/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode3.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/


#include "Mode3.h"
#include "States.h"
#include "../Engine/Engine.h"
#include "../Game/thornenemy.h"
#include "../Game/Crates.h"
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
#include "../Engine/Timer.h"
#include "Spear.h"
#include "Floor_block.h"
#include "Pony.h"
#include "Archer.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Hp.h"
#include "Mission.h"
#include "Item.h"
#include "resize_window.h"


Mode3::Mode3() : knight_ptr(nullptr)

{

    make_time = 3;
}



void Mode3::Update(double dt) {


    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<CS230::Camera>()->Update(knight_ptr->GetPosition());


    if (GetGSComponent<CS230::Timer>()->RemainingInt() == 0) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadGameState();
    }
    make_resizable();

    make_time -= dt;
    int i = 0;
    if (make_time <= 0) {
        i++;
       
        CreateRandomObject();
        make_time = next_time - i; // 다음 생성까지의 시간을 3초로 설정합니다.
    }
    timer_text = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(GetGSComponent<CS230::Timer>()->RemainingInt()), 0xFFFFFFFF);
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(GetGSComponent<CS230::Score>()->Value()), 0xFFFFFFFF);
    mission_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Mission 25: " + std::to_string(GetGSComponent<CS230::Mission>()->Value()), 0xFFFFFFFF);
    hp_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Hp: " + std::to_string(GetGSComponent<CS230::Hp>()->Value()), 0xFFFFFFFF);
}

void Mode3::Unload() {

    ClearGSComponents();
    knight_ptr = nullptr;
    //mole_ptr = nullptr;
}


void Mode3::Load() {
    std::srand(std::time(nullptr));
    make_time = 3;

#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision);
#endif
    AddGSComponent(new Gravity(gravity));
    AddGSComponent(new CS230::GameObjectManager);
    AddGSComponent(new Background());
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());
    AddGSComponent(new CS230::ParticleManager<Particles::fall_particle>());
    AddGSComponent(new CS230::ParticleManager<Particles::sparkle>());
    AddGSComponent(new CS230::ParticleManager<Particles::dead_particle>());

    AddGSComponent(new CS230::Camera({ {0, 0 }, { 800, 600 } }));
    GetGSComponent<Background>()->Add("Assets/back3.png", 1.0);

    

    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 692, static_cast<int>(floor) } });
    GetGSComponent<CS230::GameObjectManager>()->Add(starting_floor_ptr);


    knight_ptr = new Knight({ 150, floor }, starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(knight_ptr);


    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor_block(Math::irect{ { 650, -150 }, { 1010, static_cast<int>(floor) } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor_block(Math::irect{ { 650, 50 }, { 1010, static_cast<int>(floor) } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor_block(Math::irect{ { 650, 250 }, { 1010, static_cast<int>(floor) } }));

    GetGSComponent<CS230::Camera>()->SetPosition({ 0 , 0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0 , 0 } , { 800, 600 } });

    AddGSComponent(new CS230::Timer(timer_max));
    AddGSComponent(new CS230::Score());
    AddGSComponent(new CS230::Hp(10));
    AddGSComponent(new CS230::Mission());


}

void Mode3::Draw() {

    Engine::GetWindow().Clear(0x000000FF);


    GetGSComponent<Background>()->Draw();
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());


    timer_text.Draw(Math::TranslationMatrix(Math::ivec2{ 0, Engine::GetWindow().GetSize().y - 5 - timer_text.GetSize().y }));
    score_texture.Draw(Math::TranslationMatrix(Math::ivec2{ timer_text.GetSize().x + 50 , Engine::GetWindow().GetSize().y - 5 - timer_text.GetSize().y }));
    mission_texture.Draw(Math::TranslationMatrix(Math::ivec2{ 50 + hp_texture.GetSize().x, Engine::GetWindow().GetSize().y - 530 - hp_texture.GetSize().y }));
    hp_texture.Draw(Math::TranslationMatrix(Math::ivec2{ 10 , Engine::GetWindow().GetSize().y - 530 - hp_texture.GetSize().y }));
    
}

void Mode3::CreateRandomObject() {
    double object1_y = floor + 400;
    int objectType1 = std::rand() % 3; // 0, 1, 2 중에서 랜덤하게 선택
    if (objectType1 == 0) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Spear({ 1010, object1_y }, first_turn, 1350));
    }
    else if (objectType1 == 1) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Pony({ 1010, object1_y }, first_turn, 1350));
    }
    else {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Archer({ 1010, object1_y }, first_turn, 1350));
    }


    // 두 번째 오브젝트 생성
    double object2_y = floor + 200;
    int objectType2 = std::rand() % 3; // 0, 1, 2 중에서 랜덤하게 선택
    if (objectType2 == 0) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Spear({ 1010, object2_y }, first_turn, 1350));
    }
    else if (objectType2 == 1) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Pony({ 1010, object2_y }, first_turn, 1350));
    }
    else {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Archer({ 1010, object2_y }, first_turn, 1350));
    }

    // 세 번째 오브젝트 생성
    double object3_y = floor;
    int objectType3 = std::rand() % 3; // 0, 1, 2 중에서 랜덤하게 선택
    if (objectType3 == 0) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Spear({ 1010, object3_y }, first_turn, 1350));
    }
    else if (objectType3 == 1) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Pony({ 1010, object3_y }, first_turn, 1350));
    }
    else {
        GetGSComponent<CS230::GameObjectManager>()->Add(new Archer({ 1010, object3_y }, first_turn, 1350));
    }
    //GetGSComponent<CS230::Timer>()->Reset();

    int Type = std::rand() % 2;
    int position_Type = std::rand() % 3;
    GetGSComponent<CS230::GameObjectManager>()->Add(new Item({ (double)Engine::GetWindow().GetSize().x - (150 * (position_Type + 1)), (double)Engine::GetWindow().GetSize().y }, Type));

}

