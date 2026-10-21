/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Splash.h"
#include "../Engine/Window.h"

Splash::Splash() {
}

void Splash::Load() {


    counter = 0;
    texture = Engine::GetTextureManager().Load("Assets/DigiPen.png");


}

void Splash::Update(double dt) {

    Engine::GetLogger().LogDebug(std::to_string(counter));



    //count
    if (counter >= 3) {
        Engine::GetGameStateManager().ClearNextGameState();
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
    }
    counter += dt;

}

void Splash::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));


}
void Splash::Unload() {

}

