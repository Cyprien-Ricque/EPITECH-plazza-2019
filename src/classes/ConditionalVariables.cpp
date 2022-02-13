/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** Created by emilien
*/

#include "ConditionalVariables.hpp"
#include <iostream>

ConditionalVariable::ConditionalVariable()
{
    pthread_mutex_init(&this->mutex, nullptr);
    pthread_cond_init(&this->cond, nullptr);
}

void ConditionalVariable::wait()
{
    pthread_cond_wait(&this->cond, &this->mutex);
}

void ConditionalVariable::notify()
{
    pthread_cond_broadcast(&this->cond);
}

ConditionalVariable::~ConditionalVariable()
{
    pthread_cond_destroy(&this->cond);
}
