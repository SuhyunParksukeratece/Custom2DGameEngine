/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameStateManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 20, 2023
*/

#include "GameStateManager.h"
#include "Engine.h"
#include "GameState.h"
#include "GameObjectManager.h"


CS230::GameStateManager::GameStateManager() { }

void CS230::GameStateManager::AddGameState(GameState& gamestate) {
    gamestates.push_back(&gamestate);
}

void CS230::GameStateManager::SetNextGameState(int index) {
    next_gamestate = gamestates[index];
}

void CS230::GameStateManager::ReloadGameState() {
    status = Status::UNLOADING;
}

void CS230::GameStateManager::ClearNextGameState() {
    next_gamestate = nullptr;
}


void CS230::GameStateManager::Update(double dt) {
    switch (status) {
    case Status::STARTING:
        if (gamestates.empty()) {
            status = Status::STOPPING;
        }
        else {
            next_gamestate = gamestates[0];
            status = Status::LOADING;
        }
        break;
    case Status::LOADING:
        current_gamestate = next_gamestate;
        Engine::GetLogger().LogEvent("Load " + current_gamestate->GetName());
        current_gamestate->Load();
        Engine::GetLogger().LogEvent("Load Complete");
        status = Status::UPDATING;
        break;
    case Status::UPDATING:
        if (current_gamestate != next_gamestate) {
            status = Status::UNLOADING;
        }
        else {
            current_gamestate->Update(dt);

            CS230::GameObjectManager* object = GetGSComponent<CS230::GameObjectManager>();
            if (object != nullptr)
            {
                object->CollisionTest();
            }
            current_gamestate->Draw();
        }
        break;
    case Status::UNLOADING:
        if (next_gamestate == nullptr) {
            status = Status::STOPPING;
        }
        else {
            status = Status::LOADING;
        }
        TextureManager().Unload();
        Engine::GetLogger().LogEvent("Unload " + current_gamestate->GetName());
        Engine::GetLogger().LogEvent("Unload Complete");
        current_gamestate->Unload();
        Engine::GetTextureManager().Unload();
        break;
    case Status::STOPPING:
        status = Status::EXIT;
        break;
    case Status::EXIT:
        break;
    }
}

