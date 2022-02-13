/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by paul,
*/

#include <iostream>
#include "AsyncGetline.hpp"
#include <fcntl.h>
#include <asm/ioctls.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <memory.h>

AsyncGetline::AsyncGetline() : sendOverNextLine(true), commandEmpty(true)
{
    _thread.startThread(AsyncGetline::asyncGetline, this);
    _thread.detach();
}

std::string AsyncGetline::GetLine()
{
    if (sendOverNextLine) {
        usleep(1);
        return "";
    } else {
        inputLock.lock();
        std::string returnInput = input;
        inputLock.unlock();
        sendOverNextLine = true;
        return returnInput;
    }
}

void *AsyncGetline::asyncGetline(void *data)
{
    auto *Async = static_cast<AsyncGetline *>(data);
    std::string synchronousInput;
    char nextCharacter;
    struct termios init;
    struct termios getc;
    int flags = fcntl(0, F_GETFL, 0);

    fcntl(0, F_SETFL, flags | O_NONBLOCK);
    ioctl(0, TCGETS, &init);
    ioctl(0, TCGETS, &getc);
    getc.c_lflag &= ~ICANON;
    getc.c_lflag &= ~ECHO;
    getc.c_cc[VMIN] = 1;
    getc.c_cc[VTIME] = 0;

    while (Async->input != "exit") {
        synchronousInput = "";
        while (true) {
            int flags = fcntl(0, F_GETFL, 0);
            fcntl(0, F_SETFL, flags | O_NONBLOCK);
            ioctl(0, TCSETS, &getc);
            nextCharacter = getchar();
            ioctl(0, TCSETS, &init);
            if (nextCharacter == 0 || nextCharacter == -1)
                continue;
            if (nextCharacter != 127)
                putc(nextCharacter, stdout);
            if (nextCharacter == 127 and !synchronousInput.empty()) {
                synchronousInput.pop_back();
                _com = strdup(synchronousInput.data());
                printf("\b \b");
                fflush(stdout);
            }
            if (nextCharacter != 127) {
                synchronousInput += nextCharacter;
                _com = strdup(synchronousInput.data());
            }
            if (nextCharacter == 4) {
                Async->inputLock.lock();
                Async->input = "exit";
                Async->inputLock.unlock();
                printf("exit\n");
                break;
            }
            if (nextCharacter == '\n') {
                fflush(stdout);
                printf("\b\b  \b\b");
                fflush(stdout);
                if (synchronousInput.empty())
                    synchronousInput = '\n';
                _com = strdup(synchronousInput.data());
                break;
            }
            Async->commandEmpty = synchronousInput.empty();
            _com = strdup(synchronousInput.data());
        }
        Async->commandEmpty = true;
        while (!Async->sendOverNextLine)
            Async->_thread.yield(); // other threads can push work to the queue now
        Async->inputLock.lock();
        if (Async->input != "exit")
            Async->input = synchronousInput;
        Async->inputLock.unlock();
        Async->sendOverNextLine = false;
    }
    return nullptr;
}
