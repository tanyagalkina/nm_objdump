/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

int main(int ac, char **av)
{
    int ret = 0;

    if (ac == 1) {
        return (my_dump ("a.out"));
    }
    else {
        for (int i = 1; i < ac; ++i) {
            ret = my_dump(av[i]);
        }
    }
    return (ret);
}
