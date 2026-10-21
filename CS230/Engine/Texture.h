/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/

#pragma once
#include <doodle/image.hpp>
#include "Vec2.h"
#include "Matrix.h"

namespace CS230 {
    class Texture {
    public:
        // Texture();
         //void Load(const std::filesystem::path& file_path);
        friend class Font;
        void Draw(Math::vec2 location);
        void Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size);
        Math::ivec2 GetSize();
        void Draw(Math::TransformationMatrix display_matrix);
        //void Draw(Math::vec2 location);
        friend class TextureManager;
        Texture() {}
    private:
        doodle::Image image;
        Texture(const std::filesystem::path& file_path);
        Texture(doodle::Image&& doodle_image);
        unsigned int GetPixel(Math::ivec2 texel);
    };
}

