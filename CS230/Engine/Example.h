/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Example.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    March 24, 2023
*/

#pragma once

namespace CS230 {
    class ExampleService {
    public:
        ExampleService();
        ~ExampleService();

        void Start();
        void Update();
        void Stop();

        void NiceFunction();
        void CoolFunction();
        void CuteFunction();

    private:
        int private_variable_1;
        int private_variable_2;
    };
}
