/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/

#include "Font.h"
#include <doodle/drawing.hpp>
#include "Engine.h"

CS230::Font::Font(const std::filesystem::path& file_name) : texture(file_name) {
    const unsigned int white = 0xFFFFFFFF;

    // The top left pixel MUST be white (0xFFFFFFFF)
    unsigned int color = texture.GetPixel({ 0, 0 });
    if (color != white) {
        Engine::GetLogger().LogError("Font " + file_name.string() + " could not be loaded");
        return;
    }
    else {
        FindCharRects();
    }
}

void CS230::Font::FindCharRects() {
    unsigned int check_color = texture.GetPixel({ 0, 0 });
    unsigned int next_color;

    int height = texture.GetSize().y;

    int x = 1;
    for (int index = 0; index < num_chars; index++) {
        int width = 0;

        do {
            width++;
            next_color = texture.GetPixel({ x + width, 0 });
        } while (check_color == next_color);

        check_color = next_color;

        char_rects[index].point_2 = { x + width - 1, 1 };
        char_rects[index].point_1 = { x, char_rects[index].point_2.y + height - 1 };
        x += width;
    }
}

Math::irect& CS230::Font::GetCharRect(char c) {
    if (c >= ' ' && c <= 'z') {
        return char_rects[c - ' '];
    }
    else {
        Engine::GetLogger().LogError("Char '" + std::to_string(c) + "' not found");
        return char_rects[0];
    }
}

//Áú¹®
Math::ivec2 CS230::Font::MeasureText(std::string text)
{
    //  = text.c_str();
     //GetCharRect(*text.c_str()).top_right.x = text.size();
    int sum_x = 0;
    int sum_y = 0;
    for (char c : text) {
        sum_x += GetCharRect(c).Size().x;
        if (sum_y < GetCharRect(c).Size().y) {
            sum_y = GetCharRect(c).Size().y;
        }
    }
    return Math::ivec2({ sum_x , sum_y });
}

void CS230::Font::DrawChar(Math::TransformationMatrix& matrix, char c) {
    Math::irect& display_rect = GetCharRect(c);
    Math::ivec2 top_left = { display_rect.point_1.x, display_rect.point_2.y };
    if (c != ' ') {
        texture.Draw(matrix, top_left, display_rect.Size());
    }
    matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
}

CS230::Texture CS230::Font::PrintToTexture(std::string text, unsigned int color) {
    Math::ivec2 text_size = MeasureText(text);

    doodle::begin_drawing_to_image(text_size.x, text_size.y, true);

    Math::TransformationMatrix matrix;

    doodle::set_tint_color(doodle::HexColor(color));
    for (char c : text) {
        DrawChar(matrix, c);
    }

    doodle::set_tint_color(doodle::HexColor(0xFFFFFFFF));
    return CS230::Texture(doodle::end_drawing_to_image());
}

