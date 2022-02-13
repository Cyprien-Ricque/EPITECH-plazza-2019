/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/
#ifndef CCP_PLAZZA_2019_IPC_HPP
#define CCP_PLAZZA_2019_IPC_HPP

#include <sys/types.h>
#include <unistd.h>

class IPC {
    public:
        pid_t newProcess();
        void sendData(void *, int);
        void *reveiveData();
};

#endif //CCP_PLAZZA_2019_IPC_HPP
