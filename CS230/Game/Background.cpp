/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#include "Background.h"
#include <doodle/drawing.hpp>
#include "../Engine/Engine.h"

void Background::Add(const std::filesystem::path& texturePath, double speed) {
    //texture = Engine::GetTextureManager().Load(texturePath);
    backgrounds.push_back(ParallaxLayer({ Engine::GetTextureManager().Load(texturePath), speed }));

    //backgrounds.push_back(ParallaxLayer({ texturePath, speed }));
}

void Background::Unload() {
    backgrounds.clear();
}



void Background::Draw(const CS230::Camera& camera) {
    for (ParallaxLayer& background : backgrounds) {
        Math::TranslationMatrix translate = Math::vec2{ 0 - camera.GetPosition().x * background.speed, camera.GetPosition().y * background.speed };
        background.texture->Draw(translate);
    }
}

void Background::Draw() {
    for (auto& background : backgrounds)
    {
        background.texture->Draw(Math::TranslationMatrix(Math::vec2({ 0 - Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x,
                                                                      0 - Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y * background.speed })));
    }
}

Math::ivec2 Background::GetSize() {
    return backgrounds[0].texture->GetSize();
}