/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowCollision.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 28, 2023
Updated:    May 12, 2023
*/

#include "ShowCollision.h"
#include "Engine.h"

CS230::ShowCollision::ShowCollision() : enabled(true) {}

void CS230::ShowCollision::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Tilde) == true) {
        enabled = !enabled;
    }
}

bool CS230::ShowCollision::Enabled() {
    return enabled;
}
