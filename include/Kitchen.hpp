/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/
#ifndef CCP_PLAZZA_2019_KITCHEN_HPP
#define CCP_PLAZZA_2019_KITCHEN_HPP

#include <fcntl.h>
#include <algorithm>
#include "Cooker.hpp"
#include "MessageQueue.hpp"
#include "PlazzaErrors.hpp"
#include "Clock.hpp"
#include "Process.hpp"
#include "Thread.hpp"

#define SEP std::string("\n- ")

enum messageType {
    UNKNOWN = 1,
    PIZZA_PS = 12,
    PIZZA_SP = 13,
    FREE_PLACES_SP = 14,
    FREE_PLACES_PS = 15,
    IS_USELESS_PS = 16,
    IS_USELESS_SP = 17,
    STATUS_SP = 18,
    STATUS_PS = 19,
    KILL_YOURSELF_PS = 20,
    KILL_YOURSELF_SP = 21
};

class Kitchen {
    public:
        Kitchen(int id, float multiplier, int cookerNb, int restockTimer);
        ~Kitchen();

        // Both
        bool isSonKitchen();

        // Parent
        void sendPizza(APizza::ptrPizza &pizza);
        bool isCookedPizza();
        void *getCookedPizza();
        int getFreePlaces();
        bool isUseless();
        void printStatus();

        // Son
        [[noreturn]] void run();

    private:
        // Son
        void getPizza();
        void sendPizzaCooked();
        void comUseless();
        void comFreePlaces();
        void comStatus();
        void restock();
        void upgradeStock();
        void manageCookers();
        void comDead();
        bool stockOk(APizza *);
        void updateStock(APizza *);

        Clock _clockIgrdts;
        Clock _clockUseless;
        std::vector<Cooker *> _cookers;
        std::vector<APizza::ptrPizza> _pizzaQueue;
        std::map<Ingrdt, size_t> _ingrdts;

        // Parent
        void *_cookedOne;
        Clock _clock;

        // Both
        MessageQueue _ipc;
        Process proc;
        float _multiplier;
        int _cookerNb;
        int _restockTimer;

        /* /!\ Timer + ingrédients */
};

#endif //CCP_PLAZZA_2019_KITCHEN_HPP
