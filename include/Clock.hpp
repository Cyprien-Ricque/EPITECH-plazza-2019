/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#ifndef CCP_PLAZZA_2019_CLOCK_HPP
#define CCP_PLAZZA_2019_CLOCK_HPP

#include <chrono>
#include <cstdio>
#include <iostream>
#define LIMIT 0.10

class Clock {
    public:
        Clock();
        void mark();
        static double _limit;

        double getElapsedTime();
        double getElapsedTimeFromStart();
        bool timePassed(double limit = LIMIT);
        void wait(double limit = LIMIT);

    private:
        std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> _start;
        std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> _prev;
        std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> _current;
};

#endif //CCP_PLAZZA_2019_CLOCK_HPP
