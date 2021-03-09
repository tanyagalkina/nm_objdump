//
// Created by tag43 on 2/28/21.
//
#include "../include/obj.h"

int main(int ac, char **av)
{
    int ret = 0;

    if (ac == 1) {
        write(0, "At least one arg must be given\n", 31);
        return (84);
    }
    if (ac == 2)
        return (my_dump ("a.out"));
    for (int i = 2; i < ac ; ++i) {
        ret = my_dump(av[i]);
    }
    return (ret);
}
