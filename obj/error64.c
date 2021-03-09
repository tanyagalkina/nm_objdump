//
// Created by tag43 on 3/9/21.
//

#include "../include/obj.h"

int error64(prop_t *in_file)
{
    in_file->bits = 64;
    if (in_file->form64.el->e_ident[EI_MAG0] != ELFMAG0
        || in_file->form64.el->e_ident[EI_MAG1] != ELFMAG1
        || in_file->form64.el->e_ident[EI_MAG2] != ELFMAG2
        || in_file->form64.el->e_ident[EI_MAG3] != ELFMAG3
        || in_file->form64.el->e_ident[EI_CLASS] != ELFCLASS64) {
        printf("my_objdump: %s: file format not recognized\n", in_file->name);
        return (84);
    }

    return (0);

}