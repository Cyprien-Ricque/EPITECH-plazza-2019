/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#include "Process.hpp"

Process::Process()
{
    _pid = -1;
    _status = -1;
    _running = false;
}

void Process::newProcess()
{
    if (_running)
        HANDLE_ERROR("newProcess(): process already running", std::exception());
    _pid = fork();
    if (_pid == -1)
        HANDLE_P_ERROR("fork()", std::exception());
    _running = true;
}

bool Process::isSon()
{
    if (!_running)
        return (false);
    return _pid == 0;
}

void Process::waitForSon()
{
    if (isSon())
        HANDLE_ERROR("waitForSon(): Son can't wait for himself", std::exception())
    if (!_running)
        HANDLE_ERROR("waitForSon(): No son", std::exception())
    _status = waitpid(_pid, &_status, 0);
    if (_status == -1)
        HANDLE_P_ERROR("waitpid()", std::exception())
    _running = false;
}

void Process::killSon()
{
    if (!isSonEnded())
        kill(_pid, SIGQUIT);
}

bool Process::isSonEnded()
{
    if (isSon())
        HANDLE_ERROR("Error: Son can't wait for himself", std::exception())
    if (!_running)
        return (true);
    _status = waitpid(_pid, &_status, WNOHANG);
    if (_status != 0)
        _running = false;
    return _status != 0;
}

int Process::getStatus()
{
    return _status;
}
