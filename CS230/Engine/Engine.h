/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#pragma once
#include "Window.h"
#include "Input.h"
#include "GameStateManager.h"
#include "logger.h"
#include <chrono>
#include "TextureManager.h"
#include "Font.h"

class Engine {
public:
    static Engine& Instance() {
        static Engine instance;
        return instance;
    }
    static CS230::Logger& GetLogger() {
        return Instance().logger;
    }
    static CS230::Window& GetWindow() {
        return Instance().window;
    }
    static CS230::TextureManager& GetTextureManager() {
        return Instance().textureManager;
    }
    static CS230::GameStateManager& GetGameStateManager() {
        return Instance().gameStateManager;
    }
    static CS230::Input& GetInput() {
        return Instance().input;
    }


    bool HasGameEnded();
    void Start(std::string window_title);
    void Stop();
    void Update();

    static CS230::Font& GetFont(int index) {
        return Instance().fonts[index];
    }

    void AddFont(const std::filesystem::path& file_name);

private:


    std::chrono::system_clock::time_point last_tick = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point last_test;


    int frame_count = 0;

    static constexpr double TargetFPS = 30.0;
    static constexpr int FPSDuration = 5;
    static constexpr int FPSTargetFrames = static_cast<int>(FPSDuration * TargetFPS);


    Engine();
    ~Engine();

    CS230::Logger logger;
    CS230::Window window;
    CS230::GameStateManager gameStateManager;
    CS230::TextureManager textureManager;
    CS230::Input input;
    //CS230::Font font;
    std::vector<CS230::Font> fonts;

};



