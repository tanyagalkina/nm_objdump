/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

void print_sections(const Elf64_Shdr shdr, char *bytes)
{
    unsigned int i = 0;
    unsigned int tmp;
    char ch;
    tmp = shdr.sh_addr;
    unsigned width = get_hex_width(tmp, shdr.sh_size);
    while (i < shdr.sh_size) {
        if (i % 16 == 0) {
            print_addr(width, tmp);
            tmp += 16;
            print_hex(shdr, bytes, i);
        }
        ch = (bytes + shdr.sh_offset)[i];
        print_char(ch);
        i += 1;
        if (i % 16 == 0)
            printf("\n");
    }
    if (i >= shdr.sh_size && i % 16 != 0)
        print_space(i, 1);
}