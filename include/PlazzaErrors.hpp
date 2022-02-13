/*
** EPITECH PROJECT, 2023
** CCP_Plazza_2019
** File description:
** Created by Paul Surrans
*/

#ifndef CCP_PLAZZA_2019_PLAZZAERRORS_HPP
#define CCP_PLAZZA_2019_PLAZZAERRORS_HPP

#include <exception>
#include <string>
#include <utility>
#define STR std::string

#define FAILURE 84

class PlazzaError : public std::exception
{
    public:
        explicit PlazzaError(std::string message,
            std::string component = "Unknown") : _component(std::move(component)), _message(std::move(message)) {};

        std::string const &getComponent() const { return this->_component; };
        const char* what() const noexcept override {
            return this->_message.c_str();
        };

    private:
        std::string _component;
        std::string _message;
};

class ArgumentError : public PlazzaError
{
    public:
        explicit ArgumentError(const std::string &component = "./plazza",
            const std::string &message = "Error in command line.") : PlazzaError(message, component) {};
};

class CommandError : public PlazzaError
{
    public:
    explicit CommandError(const std::string &component = "Command",
        const std::string &message = "Error when submitted command.") : PlazzaError(message, component) {};
};

#endif //CCP_PLAZZA_2019_PLAZZAERRORS_HPP
