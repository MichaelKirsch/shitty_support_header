#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <queue>

namespace ShittySupportLib {
    //simple clock

    class SimpleClock {
    public:
        SimpleClock() {
            time_point = std::chrono::steady_clock::now();
            start_time = time_point;
        }

        std::chrono::milliseconds get_duration() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time);
        }

        long long get_duration_long() {
            return get_duration().count();
        }

        std::chrono::milliseconds tick() {
            auto old = time_point;
            time_point = std::chrono::steady_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(time_point - old);
        }

        int tick_int() {
            return tick().count();
        }


        void reset_timepoint_and_restart() {
            time_point = std::chrono::steady_clock::now();
            start_time = time_point;
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> time_point;
        std::chrono::time_point<std::chrono::steady_clock> start_time;
    };

    //bitshift stuff
    namespace bitshifter {
        template<class T>
        void setbit(T &data, int whichbit) {
            data |= 1UL << whichbit;
        }

        template<class T>
        void clearbit(T &data, int whichbit) {
            data &= ~(1UL << whichbit);
        }
    }


    //Debugger and logger
    class Debugger {
    public:
        enum Short{
            SUCCESS,FAIL
        };
        static Debugger &instance() {
            static Debugger _instance;
            return _instance;
        }

        ~Debugger() {}

        void log(std::string name, std::string message) {
            m_log.emplace_back(name, message);
        };

        void log(std::string name, Short shrt) {
            if(shrt)
                m_log.emplace_back(name, "Success");
            else
                m_log.emplace_back(name, "Fail");
        }



        void set_max_log_size(int new_size) {
            if (new_size < m_max_log_size) {
                m_log.pop_front();
            }
            m_max_log_size = new_size;
        }

        void debug(std::string name, std::string data) {
            if (m_debugged_values.find(name) == m_debugged_values.end()) {
                m_debugged_values.insert(std::make_pair(name, data));
            } else {
                m_debugged_values.at(name) = std::move(data);
            }
        }

        void clear_debug() {
            m_debugged_values.clear();
        }

        void clear_log() {
            while (!m_log.empty())
                m_log.pop_front();
        }

        void print_log() {
            int counter = 0;
            std::cout << "**********" << m_log.size() << " Logged Values***********" << std::endl;
            for (auto &x:m_log) {
                std::cout << counter << "|" << x.first << "|" << x.second << "\n";
                counter++;
            }
            std::cout << std::endl;
        }

        void print_debug() {
            int counter = 0;
            std::cout << "**********" << m_debugged_values.size() << " Debugged Values***********" << std::endl;
            for (auto &x:m_debugged_values) {
                std::cout << counter << "|" << x.first << "|" << x.second << "\n";
                counter++;
            }
            std::cout << std::endl;
        };

    private:
        Debugger() {

        }

        Debugger(const Debugger &);

        Debugger &operator=(const Debugger &);

        int m_max_log_size = 50;
        std::deque<std::pair<std::string, std::string>> m_log;
        std::map<std::string, std::string> m_debugged_values;
    };
};



