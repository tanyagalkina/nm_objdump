/*
** EPITECH PROJECT, 2020
** obj
** File description:
** src
*/

#include "../include/obj.h"
#include "../include/flags.h"

char *get_arch(char e_machine)
{
    if (e_machine == EM_386)
        return "i386";
    if (e_machine == EM_X86_64)
        return "i386:x86-64";
    return "unknown";
}

int get_flags(int type)
{
    switch (type) {
        case (ET_NONE):
            return (0);
        case (ET_REL):
            return (HAS_RELOC +  HAS_SYMS);
        case (ET_EXEC):
            return (EXEC_P + HAS_SYMS + D_PAGED);
        case (ET_DYN):
            return (HAS_SYMS + DYNAMIC + D_PAGED);
        default:
            return (0);
    }
}

char *get_type(int type)
{
    switch (type) {
        case (ET_NONE):
            return "";
        case (ET_REL):
            return "HAS_RELOC, HAS_SYMS";
        case (ET_EXEC):
            return "EXEC_P, HAS_SYMS, D_PAGED";
        case (ET_DYN):
            return "HAS_SYMS, DYNAMIC, D_PAGED";
        default:
            return "";
    }
}

void show_header64(prop_t *in_file)
{
    printf("%s:     file format elf64-x86-64\n", in_file->name);
    printf("architecture: %s, flags 0x%08x:\n", \
get_arch(in_file->form64.ehdr->e_machine), get_flags(in_file->form64.ehdr->e_type));
    printf("%s\n", get_type(in_file->form64.ehdr->e_type));
    printf("start address 0x%016lx\n\n", in_file->form64.ehdr->e_entry);
}

int show_file(prop_t *in_file)
{
    if (in_file->bits == 64) {
        in_file->form64.shdr = (Elf64_Shdr *)(in_file->form64.bytes +\
in_file->form64.ehdr->e_shoff);
        in_file->form64.itself = (char *)(in_file->form64.bytes +\
in_file->form64.shdr[in_file->form64.ehdr->e_shstrndx].sh_offset);
        write(1, "\n", 1);
        show_header64(in_file);
        show_dump64(&in_file->form64);
        return (0);
    }
    return (84);
}