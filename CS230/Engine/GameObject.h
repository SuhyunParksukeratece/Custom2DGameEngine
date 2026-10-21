/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#pragma once
#include "Sprite.h"
#include "ComponentManager.h"
#include "Component.h"
#include "GameObjectTypes.h"

namespace Math { class TransformationMatrix; }

//namespace Math { class TransformationMatrix; }

namespace CS230 {
    class Component;

    class GameObject {

    public:
        friend class Sprite;
        GameObject(Math::vec2 position);
        GameObject(Math::vec2 position, double rotation, Math::vec2 scale);
        virtual ~GameObject() {}
        void Destroy();
        bool Destroyed();
        virtual GameObjectTypes Type() = 0;
        virtual std::string TypeName() = 0;
        bool IsCollidingWith(GameObject* other_object);
        virtual bool CanCollideWith(GameObjectTypes);
        bool IsCollidingWith(Math::vec2 point);
        //bool IsCollidingWith(Math::vec2 point);
        virtual void ResolveCollision(GameObject* other_object) { };

        virtual void Update(double dt);
        virtual void Draw(Math::TransformationMatrix camera_matrix);

        const Math::TransformationMatrix& GetMatrix();
        const Math::vec2& GetPosition() const;
        const Math::vec2& GetVelocity() const;
        const Math::vec2& GetScale() const;
        double GetRotation() const;

        void SetPosition(Math::vec2 new_position);

        template<typename T>
        T* GetGOComponent() {
            return componentmanagers.GetComponent<T>();
        }


    protected:
        void UpdatePosition(Math::vec2 delta);
        void SetVelocity(Math::vec2 new_position);
        void UpdateVelocity(Math::vec2 delta);
        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);
        void SetRotation(double new_rotation);
        void UpdateRotation(double delta);

        //Sprite sprite;

        class State {
        public:
            virtual void Enter(GameObject* object) = 0;
            virtual void Update(GameObject* object, double dt) = 0;
            virtual void CheckExit(GameObject* object) = 0;
            virtual std::string GetName() = 0;
        };


        class State_None : public State {
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };

        State_None state_none;
        State* current_state;
        void change_state(State* new_state);
        //State* current_state = nullptr;
        //void change_state(State* new_state); ///GameObject* obj√ﬂ∞°

        void AddGOComponent(Component* component) {
            componentmanagers.AddComponent(component);
        }
        template<typename T>
        void RemoveGOComponent() {
            componentmanagers.RemoveComponent<T>();
        }
        void ClearGOComponents() {
            componentmanagers.Clear();
        }
        void UpdateGOComponents(double dt) {
            componentmanagers.UpdateAll(dt);
        }


    private:
        Math::TransformationMatrix object_matrix;
        bool matrix_outdated = false;
        double rotation;
        Math::vec2 scale;
        Math::vec2 position;
        Math::vec2 velocity;
        bool destroy = false;
        /*class State_None : public State {
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };
        State_None state_none;*/

        ComponentManager componentmanagers;

        //bool IsCollidingWith(Math::vec2 point);
    };

}

//namespace CS230 {
//    class GameObject {
//    public:
//        GameObject(Math::vec2 position);
//        GameObject(Math::vec2 position, double rotation, Math::vec2 scale);
//        virtual ~GameObject() {}
//
//        virtual void Update(double dt);
//        virtual void Draw(Math::TransformationMatrix camera_matrix);
//
//        const Math::TransformationMatrix& GetMatrix();
//        const Math::vec2& GetPosition() const;
//        const Math::vec2& GetVelocity() const;
//        const Math::vec2& GetScale() const;
//        double GetRotation() const;
//
//    protected:
//        void SetPosition(Math::vec2 new_position);
//        void UpdatePosition(Math::vec2 delta);
//        void SetVelocity(Math::vec2 new_position);
//        void UpdateVelocity(Math::vec2 delta);
//        void SetScale(Math::vec2 new_scale);
//        void UpdateScale(Math::vec2 delta);
//        void SetRotation(double new_rotation);
//        void UpdateRotation(double delta);
//
//        Sprite sprite;
//
//    private:
//    
//        class State_None : public CS230::State {
//        public:
//            void Enter(GameObject*) override {}
//            void Update(GameObject*, double) override {}
//            void CheckExit(GameObject*) override {}
//            std::string GetName() { return ""; }
//        };
//        State_None state_none;
//
//        Math::TransformationMatrix object_matrix;
//
//        double rotation;
//        Math::vec2 scale;
//        Math::vec2 position;
//        Math::vec2 velocity;
//    };
//
//    class State {
//    public:
//        virtual void Enter(GameObject* object) = 0;
//        virtual void Update(GameObject* object, double dt) = 0;
//        virtual void CheckExit(GameObject* object) = 0;
//        virtual std::string GetName() = 0;
//    };
//
//    State* current_state = nullptr;
//    void change_state(State* new_state);
//
//}

