//
// Created by tag43 on 2/28/21.
//


#include "../include/nm.h"

int main(int ac, char **av)
{
    (void) ac;
    (void) av;
    write(1, "Hello, I am nm!\n", 16);
    write(1, "\n", 1);
    return (0);

}