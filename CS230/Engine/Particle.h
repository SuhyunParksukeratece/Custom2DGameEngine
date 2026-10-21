/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particle.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 4, 2023
*/


#pragma once
#include "GameObject.h"
#include <string>
#include "Texture.h"
#include "Vec2.h"
#include "Rect.h"
#include "Engine.h"
#include "GameObjectManager.h"
#include <vector>

namespace CS230 {
    class Particle : public GameObject {
    public:
        Particle(const std::filesystem::path& sprite_file);
        void Start(Math::vec2 position, Math::vec2 velocity, double max_life);
        void Update(double dt) override;
        void Draw(Math::TransformationMatrix camera_matrix) override;
        bool Alive() {
            return  life > 0;
        }
        GameObjectTypes Type() { return GameObjectTypes::Particle; }
    private:
        double life;
    };

    template<typename T>
    class ParticleManager : public Component {
    public:
        ParticleManager();
        ~ParticleManager();
        void Emit(int count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread);
    private:
        std::vector<T*> particles;
        int index;
    };
}

template<typename T>
CS230::ParticleManager<T>::ParticleManager()
{
    for (int i = 0; i < T::MaxCount; i++)
    {
        T* particle = new T();
        particles.push_back(particle);
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(particle);
    }
    index = 0;
}

template<typename T>
CS230::ParticleManager<T>::~ParticleManager()
{
    for (T* particle : particles)
    {
        delete particle;
    }
    particles.clear();
}

template<typename T>
void CS230::ParticleManager<T>::Emit(int count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread)
{
    for (int i = 0; i < count; i++)
    {
        if (particles[index]->Alive())
        {
            Engine::GetLogger().LogDebug("Particle overwritten");
        }


        double angle_variation = 0.0;

        if (spread != 0.0)
        {
            angle_variation = ((rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2;
        }

        Math::vec2 random_magnitude = direction * (((rand() % 1024) / 2048.0f) + 0.5f);
        Math::vec2 particle_velocity = Math::RotationMatrix(angle_variation) * random_magnitude + emitter_velocity;

        particles[index]->Particle::Start(emitter_position, particle_velocity, T::MaxLife);

        index++;

        if (index >= particles.size())
        {
            index = 0;
        }
    }
}

