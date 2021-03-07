#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

namespace ShittySupportLib{
    //simple clock

    class SimpleClock{
        SimpleClock(){
            time_point = std::chrono::steady_clock::now();
            start_time = time_point;
        }

        std::chrono::milliseconds get_duration_since_start(){
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start_time);
        }

        long long get_duration_since_start_long(){
            return get_duration_since_start().count();
        }

        std::chrono::milliseconds elapsed_millis(){
            auto old = time_point;
            time_point = std::chrono::steady_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(time_point-old);
        }

        int elapsed_millis_int(){
            return elapsed_millis().count();
        }


        void reset_timepoint_and_restart(){
            time_point = std::chrono::steady_clock::now();
            start_time = time_point;
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> time_point;
        std::chrono::time_point<std::chrono::steady_clock> start_time;
    };

    //bitshift stuff
    namespace bitshifter{
        template <class T>
        void setbit (T& data, int whichbit) {
            data |= 1UL << whichbit;
        }

        template <class T>
        void clearbit (T& data, int whichbit) {
            data &= ~(1UL << whichbit);
        }
    }


    //Simple Statemaschine
    namespace CrudeStateMaschine{


            }
}
