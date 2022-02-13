/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** Created by emilien
*/

#include "Mutex.hpp"

Mutex::Mutex()
{
    this->mutex = PTHREAD_MUTEX_INITIALIZER;
}

void Mutex::lock()
{
    pthread_mutex_lock(&this->mutex);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&this->mutex);
}
