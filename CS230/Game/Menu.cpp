/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Menu.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Menu.h"
#include "../Engine/Window.h"
#include "Fonts.h"

Menu::Menu() {
}

void Menu::Load() {
    // name = Engine::GetTextureManager().Load("Assets/DigiPen.png");

    name = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("CS230 Engine Test", 0x8b00ffFF);
    select1 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", 0x008000FF);
    select2 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", 0x008000FF);
    select3 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Knight Defender", 0x008000FF);
    exit = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", 0x008000FF);

}

void Menu::Update(double dt) {
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
        color_num++;
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        color_num--;
    }
    if (color_num == -1) {
        color_num = 3;
    }
    if (color_num % 4 == 0) {
        exit = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", 0x008000FF);
        select1 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", 0xFFFFFFFF);
        select2 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", 0x008000FF);
        select3 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Knight Defender", 0x008000FF);
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
        }
    }
    if (color_num % 4 == 1) {
        select1 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", 0x008000FF);
        select2 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", 0xFFFFFFFF);
        select3 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Knight Defender", 0x008000FF);
        exit = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", 0x008000FF);
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
        }
    }
    if (color_num % 4 == 3) {
        select1 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", 0x008000FF);
        select2 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", 0x008000FF);
        select3 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Knight Defender", 0x008000FF);
        exit = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", 0xFFFFFFFF);
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().ClearNextGameState();
        }
    }
    if (color_num % 4 == 2) {
        select1 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Side Scroller", 0x008000FF);
        select2 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Space Shooter", 0x008000FF);
        select3 = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Knight Defender", 0xFFFFFFFF);
        exit = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", 0x008000FF);
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode3));
        }
    }
}

void Menu::Draw() {
    Engine::GetWindow().Clear(0x000000FF);
    // CS230::Texture Name = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("CS230 Engine Test", 0x000000FF);
    //for (int i = 1; i < 5; i++) {
    name.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - name.GetSize().x / 2, (Engine::GetWindow().GetSize().y / 12) * 10 }));
    select1.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - select1.GetSize().x / 2, (Engine::GetWindow().GetSize().y / 12) * 7 }));
    select2.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - select2.GetSize().x / 2, (Engine::GetWindow().GetSize().y / 12) * 5 }));
    select3.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - select2.GetSize().x / 2, (Engine::GetWindow().GetSize().y / 12) * 3 }));
    exit.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - exit.GetSize().x / 2,  (Engine::GetWindow().GetSize().y / 12) * 1 }));
    //}
}

void Menu::Unload() {
    // background.Unload();
}

