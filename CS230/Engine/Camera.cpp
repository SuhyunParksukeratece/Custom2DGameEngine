/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 12, 2023
Updated:    May 20, 2023
*/

#include "Camera.h"
#include "Engine.h"
#include "../Game/Cat.h"
#include "../Game/Asteroid.h"

CS230::Camera::Camera(Math::rect player_zone) :
    player_zone(player_zone), position({ 0,0 }) {}

void CS230::Camera::SetPosition(Math::vec2 new_position) {
    position = new_position;
}

const Math::vec2& CS230::Camera::GetPosition() const
{
    return position;
}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    return Math::TranslationMatrix(-position);
}

void CS230::Camera::SetLimit(Math::irect new_limit) {
    limit = new_limit;
}

void CS230::Camera::Update(const Math::vec2& player_position) {

    if (player_position.x > player_zone.point_2.x + position.x) {
        position.x = player_position.x - player_zone.point_2.x;
    }
    if (player_position.x - position.x < player_zone.point_1.x) {
        position.x = player_position.x - player_zone.point_1.x;
    }

    if (position.x < limit.point_1.x) {
        position.x = limit.point_1.x;
    }
    if (position.x > limit.point_2.x) {
        position.x = limit.point_2.x;
    }
    if (position.y < limit.point_1.y) {
        position.y = limit.point_1.y;
    }
    if (position.y > limit.point_2.y) {
        position.y = limit.point_2.y;
    }
}
