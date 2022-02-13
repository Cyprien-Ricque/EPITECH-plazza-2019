/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#include "Logs.hpp"

Logs::Logs() : _time(time(nullptr)), _aTime(localtime(&_time))
{
    _logsFile.open("logs.txt");
}

Logs::~Logs()
{
    _logsFile.close();
}

void Logs::addCookedPizza(std::pair<APizza::ptrPizza, size_t> &pizza)
{
    char buf[200];

    _time = time(nullptr);
    _aTime = localtime(&_time);
    sprintf(buf, "[%02d:%02d:%02d] \033[;1mPizza %05lu\033[0m: %s %s \033[32;1mdelivered\033[0m.\n", _aTime->tm_hour, _aTime->tm_min, _aTime->tm_sec, pizza.second, pizza.first->getPizzaName().data(), Logs::enumToSize(pizza.first->getPizzaSize()).c_str());
    _toPrint.emplace_back(std::string(buf));
    _logsFile << _toPrint.at(_toPrint.size() - 1);
    _logsFile.flush();
}

void Logs::addRawPizza(std::pair<APizza::ptrPizza, size_t> &pizza)
{
    char buf[200];

    _time = time(nullptr);
    _aTime = localtime(&_time);
    sprintf(buf, "[%02d:%02d:%02d] \033[;1mPizza %05lu\033[0m: %s %s \033[31;1msent to kitchen\033[0m.\n", _aTime->tm_hour, _aTime->tm_min, _aTime->tm_sec, pizza.second, pizza.first->getPizzaName().c_str(), Logs::enumToSize(pizza.first->getPizzaSize()).c_str());
    _toPrint.emplace_back(std::string(buf));
    _logsFile << _toPrint.at(_toPrint.size() - 1);
    _logsFile.flush();
}

std::string Logs::enumToSize(PizzaSize size)
{
    return availableSizes.at(getElemIdx(availableSizesEnum, size));
}

bool Logs::flush(int wait)
{
    if (!_clock.timePassed(wait) || _toPrint.empty())
        return (false);
    printf("\r");
    for (auto &p : _toPrint)
        printf("\r%s", p.data());
    std::cout.flush();
    _toPrint.clear();
    _clock.mark();
    return (true);
}

bool Logs::fflush()
{
    if (_toPrint.empty())
        return (false);
    printf("\r\n");
    for (auto &p : _toPrint)
        printf("\r%s", p.data());
    std::cout.flush();
    _toPrint.clear();
    _clock.mark();
    return (true);
}
