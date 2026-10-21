/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    April 7, 2023
Updated:    May 12, 2023
*/

#include "Matrix.h"
#include <cmath>

Math::TransformationMatrix::TransformationMatrix() : matrix{}
{
    Reset();
}

void Math::TransformationMatrix::Reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}


Math::TransformationMatrix Math::TransformationMatrix::operator * (TransformationMatrix m) const {

    TransformationMatrix result;

    result.matrix[0][0] = matrix[0][0] * m[0][0] + matrix[0][1] * m[1][0] + matrix[0][2] * m[2][0];
    result.matrix[0][1] = matrix[0][0] * m[0][1] + matrix[0][1] * m[1][1] + matrix[0][2] * m[2][1];
    result.matrix[0][2] = matrix[0][0] * m[0][2] + matrix[0][1] * m[1][2] + matrix[0][2] * m[2][2];
    result.matrix[1][0] = matrix[1][0] * m[0][0] + matrix[1][1] * m[1][0] + matrix[1][2] * m[2][0];
    result.matrix[1][1] = matrix[1][0] * m[0][1] + matrix[1][1] * m[1][1] + matrix[1][2] * m[2][1];
    result.matrix[1][2] = matrix[1][0] * m[0][2] + matrix[1][1] * m[1][2] + matrix[1][2] * m[2][2];
    result.matrix[2][0] = matrix[2][0] * m[0][0] + matrix[2][1] * m[1][0] + matrix[2][2] * m[2][0];
    result.matrix[2][1] = matrix[2][0] * m[0][1] + matrix[2][1] * m[1][1] + matrix[2][2] * m[2][1];
    result.matrix[2][2] = matrix[2][0] * m[0][2] + matrix[2][1] * m[1][2] + matrix[2][2] * m[2][2];

    return result;
}

Math::vec2 Math::TransformationMatrix::operator * (vec2 v) const {
    Math::vec2 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2];
    return result;
}

Math::TransformationMatrix& Math::TransformationMatrix::operator *= (Math::TransformationMatrix m) {
    (*this) = (*this) * m;
    return (*this);
}


Math::TranslationMatrix::TranslationMatrix(ivec2 translate)
{
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = static_cast<float>(translate.x);

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = static_cast<float>(translate.y);

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;

    //밑의 방식도 가능
    //Reset();

    //matrix[0][2] = translate.x;  // tx
    //matrix[1][2] = translate.y;  // ty
}
Math::TranslationMatrix::TranslationMatrix(vec2 translate)
{
    matrix[0][0] = 1.0;
    matrix[0][1] = 0.0;
    matrix[0][2] = static_cast<float>(translate.x);

    matrix[1][0] = 0.0;
    matrix[1][1] = 1.0;
    matrix[1][2] = static_cast<float>(translate.y);

    matrix[2][0] = 0.0;
    matrix[2][1] = 0.0;
    matrix[2][2] = 1.0;


    //Reset();

    //matrix[0][2] = translate.x;  // tx
    //matrix[1][2] = translate.y;  // ty
}

Math::ScaleMatrix::ScaleMatrix(double scale)
{
    matrix[0][0] = scale;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[1][0] = 0;
    matrix[1][1] = scale;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
}

Math::ScaleMatrix::ScaleMatrix(vec2 scale)
{
    matrix[0][0] = scale.x;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[1][0] = 0;
    matrix[1][1] = scale.y;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
}

Math::RotationMatrix::RotationMatrix(double theta)
{
    matrix[0][0] = cos(theta);
    matrix[0][1] = sin(theta);
    matrix[1][0] = -sin(theta);
    matrix[1][1] = cos(theta);
    matrix[0][2] = 0;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
}
