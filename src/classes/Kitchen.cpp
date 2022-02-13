/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(int id, float multiplier, int cookerNb, int restockTimer) : _ipc(id), _multiplier(multiplier), _cookerNb(cookerNb), _restockTimer(restockTimer)
{
    this->_ingrdts = {{DOE, 5}, {TOMATO, 5}, {GRUYERE, 5},
                      {HAM, 5}, {MUSHROOM, 5}, {STEAK, 5},
                      {EGGPLANT, 5}, {GOAT_CHEESE, 5}};
    while (cookerNb--)
        this->_cookers.push_back(new Cooker(this->_multiplier));
    proc.newProcess();
}

// Parent

void Kitchen::sendPizza(APizza::ptrPizza &pizza)
{
    _ipc.sendData(pack(pizza), getObjSize(), PIZZA_PS);
}

int Kitchen::getFreePlaces()
{
    _ipc.sendData(nullptr, 0, FREE_PLACES_PS);
    return *(static_cast<int *>(static_cast<void *>(_ipc.receiveDataWait(FREE_PLACES_SP))));
}

bool Kitchen::isUseless()
{
    _ipc.sendData(nullptr, 0, IS_USELESS_PS);
    return (static_cast<char *>((static_cast<int>(IS_USELESS_SP) << _ipc))[0]);
}

bool Kitchen::isCookedPizza()
{
    char *pizza = _ipc.receiveData(PIZZA_SP);

    if (!pizza)
        return false;
    _cookedOne = pizza;
    return (true);
}

void *Kitchen::getCookedPizza()
{
    return (_cookedOne);
}

void Kitchen::printStatus()
{
    _ipc.sendData(nullptr, 0, STATUS_PS);
    std::cout << std::string(static_cast<char *>((static_cast<int>(STATUS_SP) << _ipc)));
}

// Son

[[noreturn]] void Kitchen::run()
{
    while (true) {
        restock();
        manageCookers();
        sendPizzaCooked();
        getPizza();
        comUseless();
        comFreePlaces();
        comStatus();
        comDead();
    }
}

void Kitchen::getPizza()
{
    char *dt = _ipc.receiveData(PIZZA_PS);

    while (dt) {
        _pizzaQueue.push_back(unpack(dt));
        dt = _ipc.receiveData(PIZZA_PS);
    }
}

void Kitchen::comUseless()
{
    char *dt = _ipc.receiveData(IS_USELESS_PS);
    bool st;

    if (!_pizzaQueue.empty())
        _clockUseless.mark();
    if (!dt)
        return;
    st = _clockUseless.timePassed(5);
    _ipc.sendData(static_cast<void *>(&st), sizeof(bool), IS_USELESS_SP);

}

void Kitchen::comDead()
{
    char *dt = _ipc.receiveData(KILL_YOURSELF_PS);

    if (!dt)
        return;
    _ipc.sendData(nullptr, 0, KILL_YOURSELF_SP);
    exit(0);
}

void Kitchen::comFreePlaces()
{
    char *dt = _ipc.receiveData(FREE_PLACES_PS);
    int freePlaces = (_cookerNb * 2) - static_cast<int>(_pizzaQueue.size());

    if (dt)
        _ipc.sendData(static_cast<void *>(&freePlaces), sizeof(int),
            FREE_PLACES_SP);
}

void Kitchen::comStatus()
{
    std::string msg = std::string("Pizzas:");

    if (_ipc.receiveData(STATUS_PS)) {
        for (auto &p : _pizzaQueue)
            msg += SEP + std::string(p->getPizzaName());
        msg += std::string("\n");
        _ipc.sendData(const_cast<void *>(static_cast<const void *>(msg.data())),
            msg.size(), STATUS_SP);
    }
}

void Kitchen::sendPizzaCooked()
{
    auto end = std::remove_if(_pizzaQueue.begin(), _pizzaQueue.end(),
      [this](APizza::ptrPizza &p) {
            if (p->_status == COOKED)
                _ipc.sendData(pack(p), getObjSize(), PIZZA_SP);
            return p->_status == COOKED;
        });
    _pizzaQueue.erase(end, _pizzaQueue.end());
}

bool Kitchen::stockOk(APizza *pizza)
{
    std::vector<Ingrdt> neededIngrdt = pizza->getPizzaIngrdt();

    for (auto &a : neededIngrdt)
        for (auto &b : this->_ingrdts)
            if (b.first == a && b.second <= 0)
                return (false);
    return (true);
}

void Kitchen::updateStock(APizza *pizza)
{
    std::vector<Ingrdt> neededIngrdt = pizza->getPizzaIngrdt();

    for (auto &a : neededIngrdt)
        for (auto &b : this->_ingrdts)
            if (b.first == a)
                --b.second;
}

void Kitchen::manageCookers()
{
    if (this->_pizzaQueue.empty())
        return;
    for (auto &a : this->_cookers) {
        if (a->ready) {
            for (auto &b : this->_pizzaQueue) {
                if (b->_status == RAW && stockOk(b.get())) {
                    updateStock(b.get());
                    a->ready = false;
                    b->_status = COOKING;
                    a->newPizza(b.get());
                    break;
                }
            }
        }
    }
}

void Kitchen::upgradeStock()
{
    for (auto &e : _ingrdts)
        e.second += 1;
    _clockIgrdts.mark();
}

void Kitchen::restock()
{
    if (_clockIgrdts.timePassed((_restockTimer / 1000)))
        upgradeStock();
}

// Both

bool Kitchen::isSonKitchen()
{
    return proc.isSon();
}

Kitchen::~Kitchen()
{
    _ipc.sendData(nullptr, 0, KILL_YOURSELF_PS);
    while (!_ipc.receiveData(KILL_YOURSELF_SP));
}
