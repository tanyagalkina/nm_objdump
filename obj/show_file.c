//
// Created by tag43 on 3/9/21.
//

#include "../include/obj.h"

void show_header(prop_t *in_file)
{
    printf("I am header\n");
}

void show_dump(prop_t *in_file)
{
    printf("I am dump\n");
}

void show_class(prop_t *in_file)
{

    /*int	ftypes[ET_NUM];
    char	*types[ET_NUM];

    types[ET_NONE] = "";
    ftypes[ET_NONE] = 0x0;
    types[ET_REL] = "HAS_RELOC, HAS_SYMS";
    ftypes[ET_REL] = 0x11;
    types[ET_EXEC] = "EXEC_P, HAS_SYMS, D_PAGED";
    ftypes[ET_EXEC] = 0x112;
    types[ET_DYN] = "HAS_SYMS, DYNAMIC, D_PAGED";
    ftypes[ET_DYN] = 0x150;
    types[ET_CORE] = "";
    ftypes[ET_CORE] = 0x0;
    if (data->elf->e_type < ET_NUM)
    {
        printf("architecture: i386:x86-64, flags 0x%08x:\n",
               ftypes[data->elf->e_type]);
        printf("%s\n", types[data->elf->e_type]);
        printf("start address 0x%016lx\n", data->elf->e_entry);
    }*/

    printf("%s:\tfile format elf64-x86-64\n", in_file->name);
    printf("architecture: %x, flags 0x%08x:\n",
           in_file->form64.el->e_machine, in_file->form64.el->e_flags);
}

int show_file(prop_t *in_file)
{
    if (in_file->bits == 64) {
         in_file->form64.sh = (Elf64_Shdr *)(in_file->form64.bytes +\
         in_file->form64.el->e_shoff);
         in_file->form64.itself = (char *)(in_file->form64.bytes +\
         in_file->form64.sh[in_file->form64.el->e_shstrndx].sh_offset);
         write(1, "\n", 1);
         show_class(in_file);
         show_header(in_file);
         show_dump(in_file);
         return (0);
    }
    return (84);

}