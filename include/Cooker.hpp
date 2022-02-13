/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#ifndef CCP_PLAZZA_2019_COOKER_HPP
#define CCP_PLAZZA_2019_COOKER_HPP

#include "APizza.hpp"
#include "Thread.hpp"
#include <string>

class Cooker
{
public:
    explicit Cooker(float);
    bool newPizza(APizza *);
    static void *taskCook(void *);

    Mutex m;
    bool ready;
private:
    ConditionalVariable cv;
    Thread cookerThread;
    APizza *_pizza;
    float _multiplier;
};

#endif //CCP_PLAZZA_2019_COOKER_HPP
