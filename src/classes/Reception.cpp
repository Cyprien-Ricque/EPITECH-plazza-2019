/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by Paul Surrans
*/

#include "Reception.hpp"

std::atomic<char *> AsyncGetline::_com;

Reception::Reception(int ac, STR cookingTimeMultiplier, STR numberOfCooks, STR replaceIngredientsMultiplier) : _parser(ac, std::move(cookingTimeMultiplier), std::move(numberOfCooks), std::move(replaceIngredientsMultiplier)), _lastPizzaId(0)
{
    _multiplier = _parser.getCookingTimeMultiplier();
    _cookerNb = _parser.getNumberOfCooks();
    _restockTimer = _parser.getReplaceIngredientsMultiplier();
    std::ofstream("progfile").close();
    _uniqueIdKitchen = rand();
}

Reception::~Reception()
{
    closeKitchens();
    remove("progfile");
}

commandType Reception::takeCommands()
{
    _command = _asyncGetline.GetLine();

    if (_command == "exit")
        return END;
    if (_command.empty())
        return BACK;
    return COMMAND;
}

void Reception::parseCommands()
{
    std::vector<std::string> allCommands;
    this->_command = std::regex_replace(this->_command,std::regex("\\s+"), " ");
    allCommands = Reception::separate(this->_command);

    try {
        if (this->_command == " ")
            throw CommandError("\n\tCommand", "Command cannot be empty.\n");
        if (allCommands[0] == "status") {
            this->displayKitchensStatus();
            return;
        }
    } catch (PlazzaError &error) {
        std::cerr << std::endl;
        this->displayUsage();
        std::cerr << std::endl;
        std::cerr << error.getComponent() << ": " << error.what() << std::endl;
        return;
    }
    verifyIfExistingPizzaSizeMultiplier(allCommands);
}

void Reception::verifyIfExistingPizzaSizeMultiplier(std::vector<std::string> &allCommands)
{
    std::regex multiplierRegex("[x][1-9]([0-9]+)?");
    bool validPizza;
    bool validSize;

    for (auto & command : allCommands) {
        try {
            command = std::regex_replace(command, std::regex("^ +| +$"), "");
            int nbSpace = std::count(command.begin(), command.end(), ' ');
            if (nbSpace == 0)
                throw CommandError("\n\t" + command, "Missing SIZE of the desired pizza.\n");
            else if (nbSpace == 1)
                throw CommandError("\n\t" + command, "Missing NUMBER to define the desired number of pizzas.\n");
            else if (nbSpace > 2)
                throw CommandError("\n\t" + command, "Useless information submitted.\n");
            validPizza = false;
            validSize = false;
            std::string pizza = command.substr(0, command.find(' '));
            for (auto &existingPizza : availablePizzas) {
                if (pizza == existingPizza)
                    validPizza = true;
            }
            if (!validPizza)
                throw CommandError("\n\t" + command, pizza + ": not a valid TYPE.\n");
            std::string pizzaOut = command.substr(command.find(' ') + 1);
            std::string size = pizzaOut.substr(0, pizzaOut.find(' '));
            for (auto &existingSize : availableSizes) {
                if (size == existingSize)
                    validSize = true;
            }
            if (!validSize)
                throw CommandError("\n\t" + command, size + ": not a valid SIZE.\n");
            std::string multiplier = pizzaOut.substr(pizzaOut.find(' ') + 1);
            if (!regex_match(multiplier, multiplierRegex))
                throw CommandError("\n\t" + command, multiplier + ": not a valid NUMBER.\n");
            addPizzas(pizza, convertSizeToEnum(size), std::atoi(multiplier.substr(1).c_str()));
        } catch (PlazzaError &error) {
            std::cerr << std::endl;
            this->displayUsage();
            std::cerr << std::endl;
            std::cerr << error.getComponent() << ": " << error.what() << std::endl;
        }
    }
    // * DEBUG * //
    /*std::cout << std::endl;
    std::cout << "Total: " << this->_pizzas.size() << " pizzas ordered." << std::endl;
    for (auto & PIZZA : this->_pizzas) {
        std::cout << std::endl;
        std::cout << "PizzaType is: " << PIZZA->getPizzaType() << std::endl;
        std::cout << "PizzaSize is: "  << PIZZA->getPizzaSize() << std::endl;
        std::cout << "PizzaIngrdt are: ";
        for (auto & f : PIZZA->getPizzaIngrdt())
            std::cout << f << ", ";
        std::cout << std::endl;
        std::cout << "PizzaBakedTime is (in ms): ";
        std::cout << PIZZA->getBakedTime() << std::endl;
    }
    std::cout << std::endl;*/
    // * DEBUG * //
}

std::vector<std::string> Reception::separate(const std::string &)
{
    std::string actualCommand;
    std::vector<std::string> commands;

    for (auto c : this->_command)
        if (c == ';') {
            if (!actualCommand.empty())
                commands.insert(commands.end(), actualCommand);
            actualCommand.clear();
        } else {
            actualCommand += c;
        }
    if (!actualCommand.empty())
        commands.insert(commands.end(), actualCommand);
    else if (commands.empty() && !this->_command.empty() && !actualCommand.empty())
        commands.insert(commands.end(), this->_command);
    return commands;
}

void Reception::displayUsage() const
{
    std::cerr << "\tSyntax := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*" << std::endl;
    displayAvailablePizzas();
    displayAvailableSizes();
    std::cerr << "\tNUMBER := x[1...9][0...9]*";
}

void Reception::displayAvailablePizzas() const
{
    std::cerr << "\tTYPE := ";
    for (size_t it = 0; it < availablePizzas.size(); it++) {
        if (it == availablePizzas.size() - 1)
            std::cerr << availablePizzas[it] << std::endl;
        else
            std::cerr << availablePizzas[it] << " | ";
    }
}

void Reception::displayAvailableSizes() const
{
    std::cerr << "\tSIZE := ";
    for (size_t it = 0; it < availableSizes.size(); it++) {
        if (it == availableSizes.size() - 1)
            std::cerr << availableSizes[it] << std::endl;
        else
            std::cerr << availableSizes[it] << " | ";
    }
}

void Reception::displayKitchensStatus() const
{
    for (auto &k : _kitchens)
        k->printStatus();
}

void Reception::addPizzas(const std::string& pizzaName, PizzaSize pizzaSize, int c)
{
    PizzaFactory factory;

    for (int i = 0; i < c; i++)
        this->_pizzas.emplace_back(std::move(
            factory.createPizza(convertTypeToEnum(pizzaName), pizzaSize)), _lastPizzaId++);
}

PizzaSize Reception::convertSizeToEnum(const std::string &pizzaSize) const
{
    for (long unsigned int f = 0; f < availableSizes.size(); f++)
        if (pizzaSize == availableSizes[f])
            return availableSizesEnum[f];
    return S;
}

PizzaType Reception::convertTypeToEnum(const std::string &type) const
{
    return static_cast<PizzaType>(availablePizzasEnum.at(getElemIdx(availablePizzas, type)));
}

void Reception::manageCommands()
{
    for (auto k = _kitchens.begin(); k != _kitchens.end(); ++k)
        if ((*k)->isUseless()) {
            delete *k;
            _kitchens.erase(k--);
        }

    for (auto & _pizza : _pizzas)
        if (_pizza.first->_status == RAW) {
            sendToKitchens(_pizza.first);
            _pizza.first->_status = COOKING;
            _logs.addRawPizza(_pizza);
        }
    for (auto &k : _kitchens)
        while (k->isCookedPizza()) {
            auto idx = getFirstIdxCooking(unpack((*k).getCookedPizza()));
            (_pizzas.at(idx)).first->_status = COOKED;
            _logs.addCookedPizza(_pizzas.at(idx));
        }
}

void Reception::sendToKitchens(APizza::ptrPizza &pizza)
{
    auto bestOption = std::make_pair(_kitchens.begin(), 0);
    int freePlaces = 0;

    if (_kitchens.empty())
        createNewKitchen();
    for (auto it = _kitchens.begin(); it != _kitchens.end(); ++it) {
        freePlaces = (*it)->getFreePlaces();
        if (freePlaces > bestOption.second)
            bestOption = std::make_pair(it, freePlaces);
    }
    if (bestOption.second <= 0) {
        createNewKitchen();
        return (sendToKitchens(pizza));
    }
    (*bestOption.first)->sendPizza(pizza);
}

void Reception::createNewKitchen()
{
    ++_uniqueIdKitchen;
    _kitchens.push_back(new Kitchen(_uniqueIdKitchen, _multiplier, _cookerNb, _restockTimer));

    if ((*--_kitchens.end())->isSonKitchen())
        (*--_kitchens.end())->run();
}

void Reception::closeKitchens()
{
    for (auto &k : _kitchens)
        delete k;
}

bool Reception::flush()
{
    return (_logs.flush(1));
}

int Reception::getFirstIdxCooking(APizza::ptrPizza pizza)
{
    int i = 0;

    for (auto & e : _pizzas) {
        if (*pizza == *(e.first) and e.first->_status == COOKING) {
            return (i);
        }
        ++i;
    }
    return (0);
}

bool Reception::fflush()
{
    return _logs.fflush();
}

bool Reception::commandTyping() const
{
    return !this->_asyncGetline.commandEmpty;
}

std::string Reception::getCommandTyping()
{
    return std::string(AsyncGetline::_com);
}