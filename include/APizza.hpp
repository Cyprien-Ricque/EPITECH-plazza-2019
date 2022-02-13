/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#ifndef CCP_PLAZZA_2019_APIZZA_HPP
#define CCP_PLAZZA_2019_APIZZA_HPP

#include <vector>
#include <string>
#include <bits/unique_ptr.h>
#include <functional>
#include <map>
#include "dataPizza.hpp"

class APizza {
    public:
        APizza(PizzaSize size, float bakedTime) : _status(RAW), _pizzaSize(size), _bakedTime(bakedTime * 1000) {}
        typedef std::unique_ptr<APizza> ptrPizza;
        PizzaSize getPizzaSize() const {
            return this->_pizzaSize;
        };
        float getBakedTime() const {
            return this->_bakedTime;
        };
        virtual std::vector<Ingrdt> getPizzaIngrdt() const = 0;
        virtual PizzaType getPizzaType() const = 0;
        virtual std::string getPizzaName() const = 0;
        enum PizzaStatus _status;
        bool operator==(const APizza& rhs) const
        { return getPizzaSize() == rhs.getPizzaSize() && getPizzaName() == rhs.getPizzaName(); }

    protected:
        PizzaSize _pizzaSize;
        float _bakedTime;
};

APizza::ptrPizza unpack(void *pizza);
void *pack(APizza::ptrPizza &pizza);
size_t getObjSize();

class PizzaMargarita : public APizza {
    public:
        PizzaMargarita(PizzaSize size) : APizza(size, FAST) {}
        std::vector<Ingrdt> getPizzaIngrdt() const override {
            return {DOE, TOMATO, GRUYERE};
        }
        PizzaType getPizzaType() const override {
            return Margarita;
        }
        std::string getPizzaName() const override {
            return "Margarita";
        }
};

class PizzaRegina : public APizza {
    public:
        PizzaRegina(PizzaSize size) : APizza(size, MEDIUM) {}
        std::vector<Ingrdt> getPizzaIngrdt() const override {
            return {DOE, TOMATO, GRUYERE, HAM, MUSHROOM};
        }
        PizzaType getPizzaType() const override {
            return Regina;
        }
        std::string getPizzaName() const override {
            return "Regina";
        }
};

class PizzaAmericana : public APizza {
    public:
        PizzaAmericana(PizzaSize size) : APizza(size, MEDIUM) {}
        std::vector<Ingrdt> getPizzaIngrdt() const override {
            return {DOE, TOMATO, GRUYERE, STEAK};
        }
        PizzaType getPizzaType() const override {
            return Americana;
        }
        std::string getPizzaName() const override {
            return "Americana";
        }
};

class PizzaFantasia : public APizza {
    public:
        PizzaFantasia(PizzaSize size) : APizza(size, SLOW) {}
        std::vector<Ingrdt> getPizzaIngrdt() const override {
            return {DOE, TOMATO, EGGPLANT, GOAT_CHEESE, /*CHIEF LOVE ???*/};
        }
        PizzaType getPizzaType() const override {
            return Fantasia;
        }
        std::string getPizzaName() const override {
            return "Fantasia";
        }
};

#endif //CCP_PLAZZA_2019_APIZZA_HPP
