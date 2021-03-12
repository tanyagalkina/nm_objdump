/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

static int error_handling64(prop_t *f)
{
    if (((f->form64.shdr = (Elf64_Shdr *)(f->form64.bytes \
+ f->form64.ehdr->e_shoff)) == NULL) || \
((f->form64.itself = (char *)(f->form64.bytes \
+ f->form64.shdr[f->form64.ehdr->e_shstrndx].sh_offset)) == NULL)) {
        printf("my_objdump: %s: invalid pointer\n", f->name);
        return (84);
    }
    if (((void *)f->form64.shdr >= (void *)f->form64.end) ||
        ((void *)f->form64.itself >= (void *)f->form64.end)) {
        printf("my_objdump: %s: file truncated\n", f->name);
        return (84);
    }
    if (f->form64.itself && f->form64.shdr && f->form64.ehdr)
        return (0);
    return (84);
}

int error64(prop_t *in_file)
{
    in_file->bits = 64;
    if (in_file->form64.ehdr->e_ident[EI_MAG0] != ELFMAG0
        || in_file->form64.ehdr->e_ident[EI_MAG1] != ELFMAG1
        || in_file->form64.ehdr->e_ident[EI_MAG2] != ELFMAG2
        || in_file->form64.ehdr->e_ident[EI_MAG3] != ELFMAG3
        || in_file->form64.ehdr->e_ident[EI_CLASS] != ELFCLASS64) {
        printf("my_objdump: %s: file format not recognized\n", in_file->name);
        return (84);
    }
    return error_handling64(in_file);
}