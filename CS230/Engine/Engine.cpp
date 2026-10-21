/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#pragma once
#include "Engine.h"
#include <chrono>
#include <string.h>

Engine::Engine() :
#ifdef _DEBUG				
    logger(CS230::Logger::Severity::Debug, true, last_tick)
#else 						
    logger(CS230::Logger::Severity::Event, false, last_tick)
#endif
{ }

Engine::~Engine() {}

void Engine::Stop() {
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Start(std::string window_title) {
    logger.LogEvent("Engine Started");
    window.Start(window_title);
    // Create an unsigned int seed in Engine::Start() from time(NULL)
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    // Seed the random number generator with srand() and that seed
    srand(seed);
    // Immediately log that seed as an event. Make sure that you appropriately label the log.
    // You should clearly specify in the logged message what the number represents.
    logger.LogEvent("Random number generator seeded with " + std::to_string(seed));
    last_test = last_tick;
}

void Engine::Update() {
    auto now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();

    if (dt > 1.0 / FPSTargetFrames) {
        logger.LogVerbose("Engine Update");
        last_tick = now;
    }
    frame_count++;
    if (FPSTargetFrames <= frame_count) {
        double actual_time = std::chrono::duration<double>(now - last_test).count();
        logger.LogDebug("FPS: " + std::to_string(frame_count / actual_time));
        frame_count = 0;
        last_test = now;
    }

    gameStateManager.Update(dt);
    input.Update();
    window.Update();
}

//Áú¹®
void Engine::AddFont(const std::filesystem::path& file_name)
{
    fonts.push_back(file_name);
}

bool Engine::HasGameEnded() {
    return gameStateManager.HasGameEnded();
}


