
/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

int error32(prop_t *in_file)
{
    if (in_file->form64.ehdr->e_machine == EM_386) {
        printf("%s:     file format elf32-i386\n", in_file->name);
        printf("architecture: i386, flags 0x%08x:\n", \
in_file->form64.ehdr->e_flags);
        return (0);
    }
    fprintf(stderr, \
"objdump: %s: file format not recognized\n", in_file->name);
    return (84);
}

int print_advanced(unsigned char *id, prop_t *f)
{
    if (id[EI_CLASS] == ELFCLASSNONE) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", f->name);
        return (84);
    }
    if (id[EI_DATA] != ELFDATA2LSB) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", f->name);
        return (84);
    }
    if (id[EI_VERSION] != EV_CURRENT) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", f->name);
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
    if (print_advanced(id, f) == 0)
        fprintf(stderr, "objdump: %s: file format not recognized\n", f->name);
    return (84);
}