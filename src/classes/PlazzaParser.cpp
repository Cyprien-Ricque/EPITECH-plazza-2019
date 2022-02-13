/*n
** EPITECH PROJECT, 2023
** CCP_Plazza_2019
** File description:
** Created by Paul Surrans
*/

#include "PlazzaParser.hpp"

PlazzaParser::PlazzaParser(int ac, STR cookingTimeMultiplier, STR numberOfCooks, STR replaceIngredientsMultiplier)
{
    if (ac != 4) {
        this->displayUsage();
        throw ArgumentError("./plazza", "Invalid number of arguments.");
    }
    setCookingTimeMultiplier(cookingTimeMultiplier);
    setNumberOfCooks(numberOfCooks);
    setReplaceIngredientsMultiplier(replaceIngredientsMultiplier);
}

void PlazzaParser::displayUsage() const
{
    std::cout << "Usage: ./plazza x y z" << std::endl << std::endl;
    std::cout << "\tx\t\ta multiplier for the cooking time of the pizzas (> 0). It can be between 0 and 1 to obtain a divisor of the pizzas cooking time." << std::endl;
    std::cout << "\ty\t\tthe number of cooks per kitchen." << std::endl;
    std::cout << "\tz\t\tthe time in milliseconds, used by the kitchen stock to replace ingredients." << std::endl << std::endl;
}

float PlazzaParser::getCookingTimeMultiplier() const
{
    return this->_cookingTimeMultiplier;
}

int PlazzaParser::getNumberOfCooks() const
{
    return this->_numberOfCooks;
}

int PlazzaParser::getReplaceIngredientsMultiplier() const
{
    return this->_replaceIngredientsMultiplier;
}

void PlazzaParser::setCookingTimeMultiplier(std::string &multiplier)
{
    if (multiplier.back() == '.')
        multiplier.push_back('0');
    if (!this->myIsFloat(multiplier)) {
        this->displayUsage();
        throw ArgumentError("./plazza","First argument (x) is not a valid number (it must be a positive float).");
    }
    else {
        this->_cookingTimeMultiplier = std::stof(multiplier);
        if (this->_cookingTimeMultiplier == 0) {
            this->displayUsage();
            throw ArgumentError("./plazza","First argument (x) is not a valid number (it must be a positive float).");
        }
    }
}

void PlazzaParser::setNumberOfCooks(const std::string &cooksNumber)
{
    if (!this->myIsInt(cooksNumber)) {
        this->displayUsage();
        throw ArgumentError("./plazza","Second argument (y) is not a valid number (it must be a positive integer).");
    } else {
        this->_numberOfCooks = std::stoi(cooksNumber);
        if (this->_numberOfCooks == 0) {
            this->displayUsage();
            throw ArgumentError("./plazza","Second argument (y) is not a valid number (it must be a positive integer).");
        }
    }
}

void PlazzaParser::setReplaceIngredientsMultiplier(const std::string &multiplier)
{
    if (!this->myIsInt(multiplier)) {
        this->displayUsage();
        throw ArgumentError("./plazza","Third argument (z) is not a valid number (it must be a positive integer).");
    } else {
        this->_replaceIngredientsMultiplier = std::stoi(multiplier);
        if (this->_replaceIngredientsMultiplier == 0) {
            this->displayUsage();
            throw ArgumentError("./plazza","Third argument (z) is not a valid number (it must be a positive integer).");
        }
    }
}

bool PlazzaParser::myIsFloat(const std::string &string) const
{
    std::regex floatRegex("([0-9]*[.])?[0-9]+");

    return regex_match(string, floatRegex);
}

bool PlazzaParser::myIsInt(const std::string &string) const
{
    std::regex intRegex("[0-9]*");

    return regex_match(string, intRegex);
}