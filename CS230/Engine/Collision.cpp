/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 28, 2023
Updated:    May 26, 2023
*/

#include "Collision.h"
#include <doodle/drawing.hpp>
#include "Engine.h"

CS230::RectCollision::RectCollision(Math::irect boundary, GameObject* object) :
    boundary(boundary),
    object(object)
{ }

Math::rect CS230::RectCollision::WorldBoundary() {
    return {
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point_1),
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point_2)
    };
}

//질문 : 고양이가 블럭 1개짜리일 경우에는 고양이의 rect y 값이 커서 그냥 올라가진다. 괜찮은 건지 물어보기
void CS230::RectCollision::Draw(Math::TransformationMatrix display_matrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    Math::rect world_boundary = WorldBoundary();
    doodle::apply_matrix(display_matrix[0][0], display_matrix[1][0], display_matrix[0][1], display_matrix[1][1], display_matrix[0][2], display_matrix[1][2]);
    doodle::draw_rectangle(world_boundary.Left(), world_boundary.Bottom(), world_boundary.Size().x, world_boundary.Size().y);
    doodle::pop_settings();
}

CS230::CircleCollision::CircleCollision(double radius, GameObject* object) : radius(radius), object(object)
{}


double CS230::CircleCollision::GetRadius()
{
    return radius * object->GetScale().x;
}

bool CS230::CircleCollision::IsCollidingWith(GameObject* other_object)
{
    CircleCollision* other_collider = other_object->GetGOComponent<CircleCollision>();

    if (other_collider == nullptr) {
        //Engine::GetLogger().LogError("No collision component found");
        return false;
    }

    if (other_collider->Shape() != CollisionShape::Circle) {
        Engine::GetLogger().LogError("Circle vs unsupported type");
        return false;
    }

    //Math::vec2 other_position = other_object->GetPosition();
    double other_radius = other_collider->GetRadius();

    // 두 원의 중심 사이의 거리를 제곱
    Math::vec2 center1 = object->GetPosition();
    Math::vec2 center2 = other_object->GetPosition();

    double distance_x = center2.x - center1.x;
    double distance_y = center2.y - center1.y;

    double distance_distance = (distance_x * distance_x) + (distance_y * distance_y);

    // 거리 제곱과 반지름 제곱의 비교를 통해 충돌
    double radius = GetRadius() + other_radius;
    double sqrt = radius * radius;

    if (distance_distance <= sqrt) {
        //Math::vec2 collision_point = center1 + (center2 - center1) * (GetRadius() / radius);
        return true; // 충돌
    }

    return false; // 충돌 없음
}

//bool CS230::CircleCollision::IsCollidingWith(Math::vec2 point) {
//
//    Math::vec2 center = object->GetPosition(); // 원의 중심 좌표
//    double distance_X = point.x - center.x;
//    double distance_Y = point.y - center.y;
//    double distance_squared = distance_X * distance_X + distance_Y * distance_Y; // 두 점 사이의 제곱 거리
//
//    double radiusSquared = radius * radius; // 원의 반지름의 제곱
//
//    if (distance_squared <= radiusSquared) {
//        return true; // 충돌
//    }
//    else {
//        return false; // 충돌 없음
//    }
//}

bool CS230::CircleCollision::IsCollidingWith(Math::vec2 point) {

    Math::vec2 center = object->GetPosition(); // 원의 중심 좌표
    double distance_x = point.x - center.x;
    double distance_y = point.y - center.y;
    double distance_squared = distance_x * distance_y + distance_y * distance_y; // 두 점 사이의 제곱 거리

    double sqrt = radius * radius; // 원의 반지름의 제곱

    if (distance_squared <= sqrt) {
        return true; // 충돌
    }
    else {
        return false; // 충돌 없음
    }
}

void CS230::CircleCollision::Draw(Math::TransformationMatrix display_matrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(display_matrix[0][0], display_matrix[1][0], display_matrix[0][1], display_matrix[1][1], display_matrix[0][2], display_matrix[1][2]);
    doodle::draw_ellipse(object->GetPosition().x, object->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();
}

bool CS230::RectCollision::IsCollidingWith(GameObject* other_object) {
    Collision* other_collider = other_object->GetGOComponent<Collision>();


    if (other_collider == nullptr) {
        // Engine::GetLogger().LogError("No collision component found");
        return false;
    }


    if (other_collider->Shape() != CollisionShape::Rect) {
        Engine::GetLogger().LogError("Rect vs unsupported type");
        return false;
    }

    Math::rect rectangle_1 = WorldBoundary();
    Math::rect rectangle_2 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();

    //밑에 부분이 맞지 않을까 생각중
    if (rectangle_1.Left() < rectangle_2.Right() && rectangle_2.Left() < rectangle_1.Right() && rectangle_1.Bottom() < rectangle_2.Top() && rectangle_2.Bottom() < rectangle_1.Top()) {
        return true;
    }
    return false;
}


bool CS230::RectCollision::IsCollidingWith(Math::vec2 point)
{
    Math::rect worldBoundary = WorldBoundary();

    if (point.x >= worldBoundary.Left() && point.x <= worldBoundary.Right() &&
        point.y >= worldBoundary.Bottom() && point.y <= worldBoundary.Top())
    {
        return true;
    }

    return false;
}
