/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** Created by emilien
*/

#ifndef CCP_PLAZZA_2019_THREAD_HPP
#define CCP_PLAZZA_2019_THREAD_HPP

#include <thread>
#include "Mutex.hpp"
#include "ConditionalVariables.hpp"

class Thread {
public:
    explicit Thread() = default;
    void startThread(void *fct(void *), void *data);
    void detach() const;
    void join() const;
    void yield() const;
    //static void task(std::string *, bool *, Mutex *);
private:
    pthread_t _thread;
};

#endif //CCP_PLAZZA_2019_THREAD_HPP
