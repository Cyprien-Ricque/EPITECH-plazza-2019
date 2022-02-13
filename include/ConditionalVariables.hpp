/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** Created by emilien
*/

#ifndef CCP_PLAZZA_2019_CONDITIONALVARIABLES_HPP
#define CCP_PLAZZA_2019_CONDITIONALVARIABLES_HPP

#include "Mutex.hpp"
#include <condition_variable>

class ConditionalVariable {
public:
    explicit ConditionalVariable();
    ~ConditionalVariable();
    void wait();
    void notify();
private:
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

#endif //CCP_PLAZZA_2019_CONDITIONALVARIABLES_HPP
