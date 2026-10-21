/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particles.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 4, 2023
*/

#include "../Engine/Particle.h"

namespace Particles {
    class Smoke : public CS230::Particle {
    public:
        Smoke() : Particle("Assets/Smoke.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    };

    class Hit : public CS230::Particle {
    public:
        Hit() : Particle("Assets/Hit.spt") { };
        std::string TypeName() override { return "Hit Particle"; }
        static constexpr int MaxCount = 10;
        static constexpr int MaxLife = 1.0;
    };

    class MeteorBit : public CS230::Particle {
    public:
        MeteorBit() : Particle("Assets/MeteorBit.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr int MaxLife = 1.25;
    };

    class sparkle : public CS230::Particle {
    public:
        sparkle() : Particle("Assets/sparkle.spt") { };
        std::string TypeName() override { return "sparkle Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr int MaxLife = 5.0;
    };

    class fall_particle : public CS230::Particle {
    public:
        fall_particle() : Particle("Assets/fall_particle.spt") { };
        std::string TypeName() override { return "fall_particle Particle"; }
        static constexpr int MaxCount = 10;
        static constexpr int MaxLife = 1.25;
    };

    class dead_particle : public CS230::Particle {
    public:
        dead_particle() : Particle("Assets/dead_particle.spt") { };
        std::string TypeName() override { return "dead_particle Particle"; }
        static constexpr int MaxCount = 2;
        static constexpr int MaxLife = 3.0;
    };
}
