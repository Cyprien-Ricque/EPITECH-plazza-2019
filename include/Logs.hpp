/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#ifndef CCP_PLAZZA_2019_LOGS_HPP
#define CCP_PLAZZA_2019_LOGS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

#include "APizza.hpp"
#include "dataPizza.hpp"
#include "PlazzaErrors.hpp"
#include "Clock.hpp"

#define PROMPT "\rVOUS AVEZ LE SANS CONTACT ? $> "

class Logs {
    public:
        Logs();
        ~Logs();
        void addCookedPizza(std::pair<APizza::ptrPizza, size_t> &pizza);
        void addRawPizza(std::pair<APizza::ptrPizza, size_t> &pizza);
        bool flush(int);
        bool fflush();
        static std::string enumToSize(PizzaSize);

    private:
        std::ofstream _logsFile;
        std::vector<std::string> _toPrint;
        time_t _time;
        struct tm *_aTime;
        Clock _clock;
};

template <typename T>
int getElemIdx(std::vector<T> v, T e)
{
    auto it = std::find(v.begin(), v.end(), e);

    return it == v.end() ? -1 : std::distance(v.begin(), it);
}

#endif //CCP_PLAZZA_2019_LOGS_HPP