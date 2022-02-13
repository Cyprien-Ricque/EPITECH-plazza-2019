/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#ifndef CCP_PLAZZA_2019_ASYNCGETLINE_HPP
#define CCP_PLAZZA_2019_ASYNCGETLINE_HPP

#include "Thread.hpp"
#include "Mutex.hpp"
#include <unistd.h>
#include <atomic>

class AsyncGetline
{
    public:
        AsyncGetline();
        std::string GetLine();
        static void *asyncGetline(void *data);
        Thread _thread{};
        std::atomic<bool> sendOverNextLine;
        std::atomic<bool> commandEmpty;
        static std::atomic<char *> _com;
        Mutex inputLock;
        std::string input;

};

#endif