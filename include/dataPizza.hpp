/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#ifndef CCP_PLAZZA_2019_DATAPIZZA_HPP
#define CCP_PLAZZA_2019_DATAPIZZA_HPP

enum Ingrdt {
    DOE = 0,
    TOMATO = 1,
    GRUYERE = 2,
    HAM = 3,
    MUSHROOM = 4,
    STEAK = 5,
    EGGPLANT = 6,
    GOAT_CHEESE = 7
    //chief love = 8 (???)
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaCookingTime {
    FAST = 1,
    MEDIUM = 2,
    SLOW = 4
};

enum PizzaStatus {
    RAW,
    COOKING,
    COOKED
};

const std::vector<std::string> availablePizzas = {"margarita", "regina", "americana", "fantasia"};
const std::vector<PizzaType> availablePizzasEnum = {Margarita, Regina, Americana, Fantasia};
const std::vector<std::string> availableSizes = {"S", "M", "L", "XL", "XXL"};
const std::vector<PizzaSize> availableSizesEnum = {S, M, L, XL, XXL};

#endif //CCP_PLAZZA_2019_DATAPIZZA_HPP
