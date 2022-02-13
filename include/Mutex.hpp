/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** Created by emilien
*/

#ifndef CCP_PLAZZA_2019_MUTEX_HPP
#define CCP_PLAZZA_2019_MUTEX_HPP

#include <pthread.h>

class Mutex {
public:
    Mutex();
    void lock();
    void unlock();
    pthread_mutex_t mutex;
};

#endif //CCP_PLAZZA_2019_MUTEX_HPP
