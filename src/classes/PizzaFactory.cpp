/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#include "PizzaFactory.hpp"

PizzaFactory::PizzaFactory()
{
    Register(Margarita, [](PizzaSize size)-> APizza::ptrPizza {return APizza::ptrPizza{new PizzaMargarita(size)}; });
    Register(Regina, [](PizzaSize size)-> APizza::ptrPizza {return APizza::ptrPizza{new PizzaRegina(size)}; });
    Register(Americana, [](PizzaSize size)-> APizza::ptrPizza {return APizza::ptrPizza{new PizzaAmericana(size)}; });
    Register(Fantasia, [](PizzaSize size)-> APizza::ptrPizza {return APizza::ptrPizza{new PizzaFantasia(size)}; });
}

APizza::ptrPizza PizzaFactory::createPizza(PizzaType type, PizzaSize size)
{
    if (_FactoryMap.find(type) == _FactoryMap.end())
        throw std::exception();
    return _FactoryMap[type](size);
}

void PizzaFactory::Register(PizzaType type, PizzaFactory::pfnCreate lbd)
{
    _FactoryMap[type] = std::move(lbd);
}