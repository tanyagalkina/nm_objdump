/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

void print_space(unsigned int i, char end)
{
    if (end == 1)
    {
        while (i % 16 != 0)
        {
            printf(" ");
            i += 1;
        }
        printf("\n");
        return ;
    }
    while (i % 16 != 0)
    {
        printf("  ");
        i += 1;
        if (i % 4 == 0)
            printf(" ");
        if (i % 16 == 0)
            printf(" ");
    }
}

void print_hex(const Elf64_Shdr shdr, char *bytes, \
unsigned int i)
{
    char c;

    while (i < shdr.sh_size)
    {
        c = (bytes + shdr.sh_offset)[i];
        printf("%02x", (unsigned char)c);
        i += 1;
        if (i % 16 == 0)
        {
            printf("  ");
            break ;
        }
        if (i % 4 == 0)
            printf(" ");
    }
    if (i >= shdr.sh_size && i % 16 != 0)
        print_space(i, 0);
}

void print_char(char ch)
{
    if (ch >= 32 && ch <= 126)
        printf("%c", ch);
    else
        printf(".");
}

unsigned int get_hex_width(int current, int size)
{
    unsigned int nb = 0;
    unsigned int last_address = current + size;
    while (last_address != 0) {
        last_address /= 16;
        ++nb;
    }
    return (nb);
}

void print_addr(unsigned width, unsigned tmp)
{
    if (width == 4) {
        printf(" %04x ", tmp);
        return;
    }
    if (width == 5)
        printf(" %05x ", tmp);
    else if (width == 6)
        printf(" %06x ", tmp);
    else
        printf(" %04x ", tmp);
    return;
}