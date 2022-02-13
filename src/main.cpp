/*
** EPITECH PROJECT, 2023
** CCP_Plazza_2019
** File description:
** Created by Paul Surrans
*/

#include "Reception.hpp"

void checkArgs(int ac)
{
    if (ac != 4) {
        std::cout << "Usage: ./plazza x y z" << std::endl << std::endl;
        std::cout << "\tx\t\ta multiplier for the cooking time of the pizzas (> 0). It can be between 0 and 1 to obtain a divisor of the pizzas cooking time." << std::endl;
        std::cout << "\ty\t\tthe number of cooks per kitchen." << std::endl;
        std::cout << "\tz\t\tthe time in milliseconds, used by the kitchen stock to replace ingredients." << std::endl << std::endl;
        throw ArgumentError("./plazza", "Invalid number of arguments.");
    }
}

void promptManager(Reception &reception, commandType &r)
{
    if (r == COMMAND)
        reception.fflush();
    if ((reception.flush()) || r == COMMAND) {
        printf(PROMPT);
        fflush(stdout);
        if (reception.commandTyping()) {
            printf("%s", Reception::getCommandTyping().data());
            fflush(stdout);
        }
    }
}

int main(int ac, char **av)
{
    try {
        checkArgs(ac);
        printf(PROMPT);
        fflush(stdout);
        Reception reception(ac, STR(av[1]), STR(av[2]), STR(av[3]));

        for (auto r = reception.takeCommands(); r != END; r = reception.takeCommands()) {
            if (r == COMMAND)
                reception.parseCommands();
            reception.manageCommands();
            promptManager(reception, r);
        }
    } catch (PlazzaError &error) {
        std::cerr << error.getComponent() << ": " << error.what() << std::endl;
        return (FAILURE);
    }
    return (0);
}