/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#pragma once
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Component.h"


class Background : public CS230::Component {
public:
    void Add(const std::filesystem::path& texturePath, double speed);
    void Unload();
    void Draw(const CS230::Camera& camera);
    void Draw();
    Math::ivec2 GetSize();
private:
    struct ParallaxLayer {
        CS230::Texture* texture;
        //texture = Engine::GetTextureManager().Load(text);
        double speed = 1;
    };

    std::vector<ParallaxLayer> backgrounds;
};

