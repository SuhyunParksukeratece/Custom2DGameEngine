/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Timer.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#pragma once

namespace CS230 {
    class Timer : public Component {
    public:
        Timer(double time_remaining) {
            Set(time_remaining);
            pendulum = false;
        }
        void Set(double time_remaining) {
            pendulum = false;
            timer_max = time_remaining;
            Reset();
        }
        void Update(double dt) override {
            if (timer > 0) {
                timer -= dt;
                pendulum = !pendulum;
            }
            if (timer <= 0) {
                timer = 0;
            }
        }
        void Reset() {
            timer = timer_max;
            pendulum = false;
        }
        double Remaining() {
            return timer;
        }
        int RemainingInt() {
            return static_cast<int>(timer);
        }
        bool TickTock() {
            return pendulum;
        }
    private:
        double timer;
        double timer_max;
        bool pendulum;
    };
}