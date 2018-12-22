#ifndef MAIN_LOOP_DATA_H
#define MAIN_LOOP_DATA_H

#include <chrono>

struct MainLoopData
{
    int input;

    unsigned frames_counter;

    // bool main_loop_state;

    std::chrono::steady_clock::time_point start;

    bool pause;

    float game_time;

    float frame_time;

    MainLoopData()
        : input(0),
          frames_counter(0u),
          // main_loop_state(true),
          start(std::chrono::steady_clock::now()),
          pause(false),
          game_time(0.0f),
          frame_time(0.25f)
    {}
};

#endif // MAIN_LOOP_DATA_H
