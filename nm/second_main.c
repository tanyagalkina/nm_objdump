/*
** EPITECH PROJECT, 2020
** nm
** File description:
** src
*/

#include "../include/nm.h"

static int error_handling64(prop_t *f)
{
    if (((f->form64.shdr = (Elf64_Shdr *)(f->form64.bytes \
+ f->form64.ehdr->e_shoff)) == NULL) || \
((f->form64.itself = (char *)(f->form64.bytes \
+ f->form64.shdr[f->form64.ehdr->e_shstrndx].sh_offset)) == NULL)) {
        fprintf(stderr, "nm: %s: file format not recognized\n", f->name);
        return (84);
    }
    if (((void *)f->form64.shdr >= (void *)f->form64.end) ||
        ((void *)f->form64.itself >= (void *)f->form64.end)) {
        fprintf(stderr, "nm: %s: file truncated\n", f->name);
        return (84);
    }
    if (f->form64.itself && f->form64.shdr && f->form64.ehdr)
        return (0);
    fprintf(stderr, "mn: %s: file format not recognized\n", f->name);
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
        fprintf(stderr, "nm: %s: file format not recognized\n", in_file->name);
        return (84);
    }
    return error_handling64(in_file);
}

int error32(prop_t *f)
{
    if (f->form64.ehdr->e_machine == EM_386)
        return (0);
    fprintf(stderr, "nm: %s: file format not recognized\n", f->name);
    return (84);
}

int print_advanced(unsigned char *id, prop_t *f)
{
    if (id[EI_CLASS] == ELFCLASSNONE) {
        fprintf(stderr, "nm: %s: file format not recognized\n", f->name);
        return (84);
    }
    if (id[EI_DATA] != ELFDATA2LSB) {
        fprintf(stderr, "nm: %s: file format not recognized\n", f->name);
        return (84);
    }
    if (id[EI_VERSION] != EV_CURRENT) {
        fprintf(stderr, "nm: %s: file format not recognized\n", f->name);
    }
    return (0);
}

int type_check(prop_t *f)
{
    unsigned char *id = f->form64.ehdr->e_ident;

    if (id[EI_CLASS] == ELFCLASS64
        && id[EI_DATA] == ELFDATA2LSB && id[EI_VERSION == EV_CURRENT])
        return error64(f);
    else if (id[EI_CLASS] == ELFCLASS32 && \
id[EI_DATA] != ELFDATANONE && id[EI_VERSION == EV_CURRENT]) {
        return error32(f);
    }
    fprintf(stderr, "nm: %s: file format not recognized\n", f->name);
    return (84);
}