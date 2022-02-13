/*
** EPITECH PROJECT, 2019
** CCP_Plazza_2019
** File description:
** CCP_Plazza_2019,
*/

#include "APizza.hpp"
#include "PizzaFactory.hpp"

typedef struct pizza_opaque_object {
    PizzaType type;
    PizzaSize size;
} pizzaCO;

APizza::ptrPizza unpack(void *pizza)
{
    auto *pizzaObj = static_cast<pizzaCO *>(pizza);
    auto factory = new PizzaFactory;

    return (factory->createPizza(pizzaObj->type, pizzaObj->size));
}

void *pack(APizza::ptrPizza &pizza)
{
    auto *pizzaObj = new pizzaCO;

    pizzaObj->type = pizza->getPizzaType();
    pizzaObj->size = pizza->getPizzaSize();
    return (static_cast<void *>(pizzaObj));
}

size_t getObjSize()
{
    return (sizeof(struct pizza_opaque_object));
}

//Margarita XL x2