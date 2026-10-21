/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Vec2.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 4, 2023
*/

#include "Vec2.h"
#include <iostream>


bool Math::vec2::operator==(const vec2& v) {
    if (x == v.x && y == v.y) {
        return true;
    }
    else {
        return false;
    }
}

bool Math::vec2::operator!=(const vec2& v) {
    if (x == v.x && y == v.y) {
        return false;
    }
    else {
        return true;
    }
}


Math::vec2 Math::vec2::operator+(const vec2& v) {
    return { x + v.x, y + v.y };
}

Math::vec2& Math::vec2::operator+=(const vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

//곱하기 -1을 해야한다.
Math::vec2 Math::vec2::operator-(const vec2& v) {
    return { x - v.x, y - v.y };
}

Math::vec2& Math::vec2::operator-=(const vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Math::vec2 Math::vec2::operator*(double scale) {
    return { x * scale, y * scale };
}

Math::vec2& Math::vec2::operator*=(double scale) {
    x *= scale;
    y *= scale;
    return *this;
}

Math::vec2 Math::vec2::operator/(double divisor) {
    return { x / divisor, y / divisor };
}

Math::vec2& Math::vec2::operator/=(double divisor) {
    x /= divisor;
    y /= divisor;
    return *this;
}

Math::vec2 Math::vec2::operator-()
{
    return vec2(-x, -y);
}

void Math::vec2::Normalize()
{
    float length = std::sqrt(x * x + y * y);
    if (length > 0.0) {
        x /= length;
        y /= length;
    }
}

//vec2와 ivec2를 뒤집는 연산자
//Math::vec2 Math::vec2::operator-() {
//    return vec2(-x, -y);
//}
//
//Math::ivec2 Math::ivec2::operator-(){
//    return ivec2(-x, -y);
//}

//ivec

bool Math::ivec2::operator==(const ivec2& v) {
    if (x == v.x && y == v.y) {
        return true;
    }
    else {
        return false;
    }
}

bool Math::ivec2::operator!=(const ivec2& v) {
    if (x == v.x && y == v.y) {
        return false;
    }
    else {
        return true;
    }
}

Math::ivec2 Math::ivec2::operator+(const ivec2& v) {
    return { x + v.x, y + v.y };
}

Math::ivec2& Math::ivec2::operator+=(const ivec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Math::ivec2 Math::ivec2::operator-(const ivec2& v) {
    return { x - v.x, y - v.y };
}

Math::ivec2 Math::ivec2::operator-()
{
    return ivec2(-x, -y);
}

Math::ivec2& Math::ivec2::operator-=(const ivec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Math::ivec2 Math::ivec2::operator*(int scale) {
    return { x * scale, y * scale };
}

Math::ivec2& Math::ivec2::operator*=(int scale) {
    x *= scale;
    y *= scale;
    return *this;
}

Math::ivec2 Math::ivec2::operator/(int divisor) {
    return { (int)x / divisor, (int)y / divisor };
}

Math::ivec2& Math::ivec2::operator/=(int divisor) {
    x /= divisor;
    y /= divisor;
    return *this;
}

Math::vec2 Math::ivec2::operator*(double scale) {
    return { x * scale, y * scale };
}
Math::vec2 Math::ivec2::operator/(double divisor) {
    return { x / divisor, y / divisor };
}