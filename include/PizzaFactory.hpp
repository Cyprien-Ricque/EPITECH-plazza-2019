/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#ifndef CCP_PLAZZA_2019_PIZZAFACTORY_HPP
#define CCP_PLAZZA_2019_PIZZAFACTORY_HPP

#include <APizza.hpp>

class PizzaFactory {
    public:
        PizzaFactory();
        typedef std::function<APizza::ptrPizza (PizzaSize)> pfnCreate;
        APizza::ptrPizza createPizza(PizzaType type, PizzaSize size);

    private:
        void Register(PizzaType, pfnCreate);
        std::map<PizzaType, pfnCreate> _FactoryMap;
};

#endif //CCP_PLAZZA_2019_PIZZAFACTORY_HPP
