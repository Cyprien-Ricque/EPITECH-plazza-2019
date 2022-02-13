/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#include <Kitchen.hpp>
#include "MessageQueue.hpp"

MessageQueue::MessageQueue(int id) : _transferFile("progfile"), _projID(65), _msg({})
{
    _key = ftok(_transferFile.data(), id);
    _msgID = msgget(_key, 0666 | IPC_CREAT);
}

MessageQueue::~MessageQueue()
{
    msgctl(_msgID, IPC_RMID, NULL);
}

void MessageQueue::sendData(void *data, size_t dataSize, int type)
{
    if (type < 1)
        HANDLE_ERROR("Message Queue : _msg type must be greater than 0", std::exception())
    _msg.msg_type = type;
    memset(_msg.msg_text, 0, MSG_SIZE);
    if (data)
        memcpy(_msg.msg_text, static_cast<const char *>(data), dataSize);
    if (msgsnd(_msgID, &_msg, sizeof(_msg), 0) < 0)
        HANDLE_P_ERROR("msgsnd()", std::exception())
}

char *MessageQueue::receiveData(int type)
{
    if (msgrcv(_msgID, &_msg, sizeof(_msg), type, IPC_NOWAIT) < 0) {
        if (errno != ENOMSG)
            HANDLE_P_ERROR("msgrcv()", std::exception())
        return (nullptr);
    }
    return (_msg.msg_text);
}

char *MessageQueue::receiveDataWait(int type)
{
    if (msgrcv(_msgID, &_msg, sizeof(_msg), type, 0) < 0)
        HANDLE_P_ERROR("msgrcv()", std::exception())
    return (_msg.msg_text);
}

void operator<<(MessageQueue &mq, const std::string &str)
{
    mq.sendData(const_cast<void *>(static_cast<const void *>(str.data())), str.size(), UNKNOWN);
}

void *operator<<(int type, MessageQueue &mq)
{
    return (mq.receiveDataWait(type));
}

void operator>>(const std::string &str, MessageQueue &mq)
{
    mq.sendData(const_cast<void *>(static_cast<const void *>(str.data())), str.size(), UNKNOWN);
}

void *operator>>(MessageQueue &mq, int type)
{
    return (mq.receiveDataWait(type));
}
