/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#include "TextureManager.h"
#include "Texture.h"

//static CS230::Window& GetWindow() {
//    return Instance().window;
//}

namespace CS230 {

    Texture* TextureManager::Load(const std::filesystem::path& file_path)
    {
        // Check if texture is already loaded
        if (textures.find(file_path) != textures.end())
        {
            // Texture is already loaded, return it
            return textures[file_path];
        }
        else
        {
            // Texture is not loaded, load it and insert it into map
            Texture* newTexture = new Texture(file_path);
            textures[file_path] = newTexture;
            return newTexture;
        }
    }

    void TextureManager::Unload()
    {
        // Deallocate all memory and clear map
        for (auto& texture : textures)
        {
            delete texture.second;
        }
        textures.clear();
    }

}
