/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** Created by emilien
*/

#include "Thread.hpp"
#include <pthread.h>

void Thread::startThread(void *fct(void *), void *data)
{
    pthread_create(&this->_thread, nullptr, fct, data);
}

void Thread::join() const
{
    pthread_join(this->_thread, nullptr);
}

void Thread::detach() const
{
    pthread_detach(this->_thread);
}

void Thread::yield() const
{
    pthread_yield();
}