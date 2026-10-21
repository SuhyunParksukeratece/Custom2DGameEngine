/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/


#pragma once
#include <string>
#include "Vec2.h"
#include "Matrix.h"
#include "Texture.h"
#include "Animation.h"
#include "Component.h"
#include "GameObject.h"

namespace CS230 {
    class Sprite : public Component {
    public:
        friend class GameObject;
        Sprite(const std::filesystem::path& sprite_file, GameObject* object);
        //Sprite();
        ~Sprite();
        //void Update(double dt);
        void Update(double dt) override;
        void Load(const std::filesystem::path& sprite_file, GameObject* object);
        int CurrentAnimation();
        void Draw(Math::TransformationMatrix display_matrix);
        Math::ivec2 GetHotSpot(int index);
        Math::ivec2 GetFrameSize();


        void PlayAnimation(int animation);
        bool AnimationEnded();
    private:
        Math::ivec2 GetFrameTexel(int index) const;

        Texture* texture;
        std::vector<Math::ivec2> hotspots;

        int current_animation;
        Math::ivec2 frame_size;
        std::vector<Math::ivec2> frame_texels;
        std::vector<Animation*> animations;
    };
}




