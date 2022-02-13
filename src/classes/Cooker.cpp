/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#include "Cooker.hpp"
#include <iostream>

Cooker::Cooker(float multiplier) : _multiplier(multiplier)
{
    this->ready = true;
}

bool Cooker::newPizza(APizza *new_pizza)
{
    this->_pizza = new_pizza;
    this->cookerThread.startThread(Cooker::taskCook, this);
    this->cookerThread.detach();
    this->cookerThread.yield();
    return true;
}

void *Cooker::taskCook(void *in)
{
    auto *cook = static_cast<Cooker *>(in);
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> current;
    int microsToWait = (int)(cook->_pizza->getBakedTime() * cook->_multiplier * 1000);

    cook->m.lock();
    cook->_pizza->_status = COOKING;
    cook->m.unlock();
    start = std::chrono::system_clock::now();
    current = start;
    while (std::chrono::duration_cast<std::chrono::microseconds>(current-start).count() < microsToWait)
        current = std::chrono::system_clock::now();
    cook->m.lock();
    cook->_pizza->_status = COOKED;
    cook->m.unlock();
    cook->ready = true;
    pthread_exit(nullptr);
}