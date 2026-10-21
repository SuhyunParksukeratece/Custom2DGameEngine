/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Menu.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Vec2.h"

class Menu : public CS230::GameState {
public:
    Menu();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Menu"; }
private:

    //bool color = false;
    int color_num = 0;
    CS230::Texture name;
    CS230::Texture select1;
    CS230::Texture select2;
    CS230::Texture select3;
    CS230::Texture exit;

};

