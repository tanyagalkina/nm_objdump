/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

int skip_64(f64bits_t *file, int nb, int alloc, int write)
{
    if (file->shdr[nb].sh_type == SHT_PROGBITS
        || file->shdr[nb].sh_type == SHT_NOTE
        || alloc == SHF_ALLOC || write == SHF_WRITE)
        return (1);
    return (0);
}

int if_show(f64bits_t *file64, int i)
{
    int alloc;
    int write;

    alloc = file64->shdr[i].sh_flags & SHF_ALLOC;
    write = file64->shdr[i].sh_flags & SHF_WRITE;
    if (file64->shdr[i].sh_type == SHT_NOBITS)
        return (0);
    return (skip_64(file64, i, alloc, write));
}

void show_dump64(f64bits_t *type_64)
{
    for (int i = 0; i < type_64->ehdr->e_shnum; i++)
        if (if_show(type_64, i) && type_64->shdr[i].sh_size != 0) {
            printf("Contents of section %s:\n", type_64->itself + \
type_64->shdr[i].sh_name);
            print_sections(type_64->shdr[i], type_64->bytes);
        }
}