/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#ifndef CCP_PLAZZA_2019_PROCESS_HPP
#define CCP_PLAZZA_2019_PROCESS_HPP

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <wait.h>
#include <sys/types.h>
#include <csignal>
#include <stdlib.h>

#define HANDLE_P_ERROR(msg, exception) do { perror(msg); throw exception; } while (0);
#define HANDLE_ERROR(msg, exception) do { std::cerr << msg << std::endl; throw exception; } while (0);

class Process {
    public:
        Process();
        void newProcess();
        bool isSon();
        void waitForSon();
        void killSon();
        bool isSonEnded();
        int getStatus();

    private:
        pid_t _pid;
        int _status;
        bool _running;
};

#endif //CCP_PLAZZA_2019_PROCESS_HPP
