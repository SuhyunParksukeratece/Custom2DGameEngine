/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  logger.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 12, 2023
*/

#include <iostream>
#include "logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start_time) : min_level(severity), out_stream("Trace.log"), start_time(start_time) {
    if (use_console == true) {
        out_stream.set_rdbuf(std::cout.rdbuf());
    }
}

CS230::Logger::~Logger() {
    out_stream.flush();
    out_stream.close();
}

double CS230::Logger::seconds_since_start() {
    auto now = std::chrono::system_clock::now();
    double actual_t = std::chrono::duration<double>(now - start_time).count();

    return actual_t;
}

void CS230::Logger::log(CS230::Logger::Severity severity, std::string message) {
    if (severity >= min_level) {
        switch (severity) {
        case Severity::Error:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
            out_stream << "Error " << message << std::endl;
            break;

        case Severity::Event:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
            out_stream << "Event " << message << std::endl;
            break;

        case Severity::Debug:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
            out_stream << "Debug " << message << std::endl;
            break;

        case Severity::Verbose:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
            out_stream << "Verbose " << message << std::endl;
            break;

        }
    };
}