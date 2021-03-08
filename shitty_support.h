#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <map>

namespace ShittySupportLib{
    //simple clock for timing

    class SimpleClock{
    public:
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


    //tiny Scheduler
    namespace TinyScheduler{
        class Task{
        public:
            Task(int millis_update_rate) : m_updaterate_millis(millis_update_rate) {  };
            virtual std::chrono::milliseconds update()=0; //returns the millis count when next update is needed;
            virtual void init(){};
            virtual void end(){};

            bool done= false; //can be set by the task to get out of the scheduler

        private:
            const int m_updaterate_millis;
        };


        class Taskmanager {
        public:


            void update(){

            }

            void attach_task(Task& to_attach){
                m_tasks.push_back(&to_attach);
                to_attach.init();
            };


        private:
            void go_to_sleep(double millis){};
            std::multimap<Task*,double> m_scheduler_list;
            std::vector<Task*> m_tasks;
        };
    }
}
