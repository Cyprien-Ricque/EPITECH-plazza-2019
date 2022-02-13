/*
** EPITECH PROJECT, 2023
** CCP_Plazza_2019
** File description:
** Created by Paul Surrans
*/

#ifndef CCP_PLAZZA_2019_PLAZZAPARSER_HPP
#define CCP_PLAZZA_2019_PLAZZAPARSER_HPP

#include <iostream>
#include <regex>
#include <string>
#include "PlazzaErrors.hpp"

class PlazzaParser {
    public:
        PlazzaParser(int ac, STR cookingTimeMultiplier, STR numberOfCooks, STR replaceIngredientsMultiplier);
        void displayUsage() const;
        float getCookingTimeMultiplier() const;
        int getNumberOfCooks() const;
        int getReplaceIngredientsMultiplier() const;
        void setCookingTimeMultiplier(std::string &);
        void setNumberOfCooks(const std::string &);
        void setReplaceIngredientsMultiplier(const std::string &);
    private:
        bool myIsInt(const std::string &) const;
        bool myIsFloat(const std::string &) const;
        float _cookingTimeMultiplier;
        int _numberOfCooks;
        int _replaceIngredientsMultiplier;
};

#endif //CCP_PLAZZA_2019_PLAZZAPARSER_HPP
