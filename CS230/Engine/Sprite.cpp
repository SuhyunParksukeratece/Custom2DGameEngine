/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#include "Sprite.h"
#include "Engine.h"
#include "Collision.h"

CS230::Sprite::Sprite(const std::filesystem::path& sprite_file, GameObject* object) : current_animation(0), texture(texture) {
    Load(sprite_file, object);
}

//CS230::Sprite::Sprite() : current_animation(0) {}

CS230::Sprite::~Sprite()
{
    for (auto animation : animations)
    {
        delete animation;
    }
    animations.clear();
}

void CS230::Sprite::Update(double dt)
{
    animations[current_animation]->Update(dt);
}

void CS230::Sprite::Load(const std::filesystem::path& sprite_file, GameObject* object) {
    if (sprite_file.extension() != ".spt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .spt file");
    }
    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    hotspots.clear();
    frame_texels.clear();


    std::string text;
    in_file >> text;
    texture = Engine::GetTextureManager().Load(text);
    //texture.Load(text);
    //Engine::GetTextureManager().
    frame_size = texture->GetSize();

    in_file >> text;
    while (in_file.eof() == false) {
        if (text == "FrameSize") {
            in_file >> frame_size.x;
            in_file >> frame_size.y;
        }
        else if (text == "NumFrames") {
            int frame_count;
            in_file >> frame_count;
            for (int i = 0; i < frame_count; i++) {
                frame_texels.push_back({ frame_size.x * i, 0 });
            }
        }
        else if (text == "Frame") {
            int frame_location_x, frame_location_y;
            in_file >> frame_location_x;
            in_file >> frame_location_y;
            frame_texels.push_back({ frame_location_x, frame_location_y });
        }
        else if (text == "HotSpot") {
            int hotspot_x, hotspot_y;
            in_file >> hotspot_x;
            in_file >> hotspot_y;
            hotspots.push_back({ hotspot_x, hotspot_y });
        }
        //질문하기
        else if (text == "Anim") {
            std::string animation_string;
            in_file >> animation_string;
            animations.push_back(new Animation(animation_string));

        }
        else if (text == "RectCollision") {
            Math::irect boundary;
            in_file >> boundary.point_1.x >> boundary.point_1.y >> boundary.point_2.x >> boundary.point_2.y;
            if (object == nullptr) {
                Engine::GetLogger().LogError("Cannot add collision to a null object");
            }
            else {
                object->AddGOComponent(new RectCollision(boundary, object));
            }
        }
        else if (text == "CircleCollision") {
            double radius;
            in_file >> radius;
            if (object == nullptr) {
                Engine::GetLogger().LogError("Cannot add collision to a null object");
            }
            else {
                object->AddGOComponent(new CircleCollision(radius, object));
            }
        }
        else {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
    if (frame_texels.empty() == true) {
        frame_texels.push_back({ 0,0 });
    }
    if (animations.empty() == true) {

        //    animations.emplace_back(default_animation);
        animations.push_back(new Animation());
        PlayAnimation(0);
    }
}

int CS230::Sprite::CurrentAnimation() {
    return current_animation;
}
//void CS230::Load(const std::filesystem::path& sprite_file) {
//	texture.Load(sprite_file);
//	Math::ivec2 hotspot_c = texture.GetSize() / 2;
//	hotspots.push_back({ Math::ivec2( hotspot_c.x, hotspot_c.y ) });
//}

//void CS230::Sprite::Load(const std::filesystem::path& texture_path, Math::ivec2 hotspot_position) {
//	texture.Load(texture_path);
//	hotspots.push_back(hotspot_position);
//}
//
//void CS230::Sprite::Load(const std::filesystem::path& texture_path, std::initializer_list<Math::ivec2> spots) {
//	texture.Load(texture_path);
//	for (Math::ivec2 spot : spots) {
//		hotspots.push_back(spot);
//	}
//}


//void CS230::Sprite::Draw(Math::vec2 position) {
//	//Math::vec2 sprite_position = position - Math::vec2(hotspot.x, hotspot.y);
//	Math::vec2 sprite_position = position - Math::vec2(hotspot);
//	Math::ivec2 texture_size = GetTextureSize();
//	texture.Draw(static_cast<Math::vec2>(sprite_position));
//}

void CS230::Sprite::Draw(Math::TransformationMatrix display_matrix) {
    texture->Draw(display_matrix * Math::TranslationMatrix(-GetHotSpot(0)), GetFrameTexel(animations[current_animation]->CurrentFrame()), GetFrameSize());
}



Math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
    if (index < 0 || index >= hotspots.size()) {
        //std::cout << "Error: Invalid hotspot index\n";
        return Math::ivec2(0, 0);
    }
    return hotspots[index];
}

Math::ivec2 CS230::Sprite::GetFrameSize()
{
    return frame_size;

    //return Math::ivec2();
}

//질문하기
void CS230::Sprite::PlayAnimation(int animation)
{
    if (animations.empty() == false && animation < animations.size())
    {
        current_animation = animation;
        animations[current_animation]->Reset();
    }
    else {
        Engine::GetLogger().LogError("Animation Error");
    }
}

//질문하기
bool CS230::Sprite::AnimationEnded()
{
    if (animations[current_animation]->Ended()) {
        return true;
    }
    else {
        return false;
    }
}

Math::ivec2 CS230::Sprite::GetFrameTexel(int index) const
{
    if (index < 0 || index > frame_texels.size() - 1) {
        Engine::GetLogger().LogError("GetFrameTexel Error");
        return { 0,0 };

    }
    else {
        return frame_texels[index];
    }
    //return Math::ivec2();
}
//void CS230::Sprite::Draw(Math::vec2 position) {
//	texture.Draw(position - static_cast<Math::vec2>(hotspot));
//}


//Math::ivec2 CS230::Sprite::GetTextureSize() {
//	return{
//	 texture.GetSize()
//	};
//}
