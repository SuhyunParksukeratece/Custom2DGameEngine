#pragma once
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#pragma once
#include <vector>
#include "GameObject.h"
#include "Matrix.h"
#include <list>

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObjectManager : public Component {
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);
        void CollisionTest();
    private:
        std::list<GameObject*> objects;
    };
}
