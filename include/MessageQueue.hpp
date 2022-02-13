/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#ifndef CCP_PLAZZA_2019_MESSAGEQUEUE_HPP
#define CCP_PLAZZA_2019_MESSAGEQUEUE_HPP

#include <cstdio>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <cstring>
#include "APizza.hpp"

#define HANDLE_P_ERROR(msg, exception) do { perror(msg); throw exception; } while (0);
#define HANDLE_ERROR(msg, exception) do { std::cerr << msg << std::endl; throw exception; } while (0);
#define MSG_SIZE 100

class MessageQueue {
    public:
        MessageQueue(int id);
        ~MessageQueue();

        void sendData(void *data, size_t dataSize, int type = 1);
        char *receiveData(int type = 0);
        char *receiveDataWait(int type = 0);

        friend void operator<<(MessageQueue& mq, const std::string &str);
        friend void *operator<<(int type, MessageQueue& mq);
        friend void operator>>(const std::string &str, MessageQueue& mq);
        friend void *operator>>(MessageQueue& mq, int type);

    private:
        std::string _transferFile;
        int _projID;
        key_t _key;
        int _msgID;

        struct {
            long msg_type;
            char msg_text[MSG_SIZE];
        } _msg;
};

#endif //CCP_PLAZZA_2019_MESSAGEQUEUE_HPP
