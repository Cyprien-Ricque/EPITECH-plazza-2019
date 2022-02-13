/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#ifndef CCP_PLAZZA_2019_RECEPTION_HPP
#define CCP_PLAZZA_2019_RECEPTION_HPP

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <regex>
#include <cmath>
#include <climits>
#include <utility>

#include "PlazzaParser.hpp"
#include "APizza.hpp"
#include "PizzaFactory.hpp"
#include "Kitchen.hpp"
#include "Logs.hpp"
#include "AsyncGetline.hpp"

enum commandType {
    BACK,
    COMMAND,
    END
};

class Reception {
    public:
        Reception(int ac, STR cookingTimeMultiplier, STR numberOfCooks, STR replaceIngredientsMultiplier);
        ~Reception();
        commandType takeCommands();
        void parseCommands();
        void manageCommands();
        void closeKitchens();
        bool flush();
        bool fflush();
        bool commandTyping() const;
        static std::string getCommandTyping() ;

    private:
        std::vector<std::string> separate(const std::string &);
        void verifyIfExistingPizzaSizeMultiplier(std::vector<std::string> &);
        void displayUsage() const;
        void displayAvailablePizzas() const;
        void displayAvailableSizes() const;
        void displayKitchensStatus() const;
        void addPizzas(const std::string&, PizzaSize, int);
        PizzaSize convertSizeToEnum(const std::string &size) const;
        PizzaType convertTypeToEnum(const std::string &type) const;
        void sendToKitchens(APizza::ptrPizza &);
        void createNewKitchen();
        int getFirstIdxCooking(APizza::ptrPizza pizza);

        std::string _tmpLine;

        PlazzaParser _parser;
        std::vector<std::pair<APizza::ptrPizza, size_t>> _pizzas;
        std::vector<Kitchen *> _kitchens;

        AsyncGetline _asyncGetline;
        std::string _command;
        Logs _logs;

        float _multiplier;
        int _cookerNb;
        int _restockTimer;
        int _uniqueIdKitchen;
        size_t _lastPizzaId;
 };

#endif //CCP_PLAZZA_2019_RECEPTION_HPP
