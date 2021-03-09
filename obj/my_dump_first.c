//
// Created by tag43 on 3/8/21.
//


#include "../include/obj.h"

int type_check(prop_t *in_file)
        /*{


                    printf ("mmap (%s) : %08x\n", path , in_file->form64.bytes);
                    elf = in_file->form64.bytes;
                    if (elf->e_ident[EI_CLASS] == ELFCLASS64)
                        printf("I am 64_bits file!\n");
                    printf (" Section Header Table : addr = %08 x , nb = %d\n",
                            elf -> e_shoff , elf -> e_shnum );
        } else {*/
{

    if (in_file->form64.el->e_ident[EI_CLASS] == ELFCLASS64)
        return error64(in_file);
    else if (in_file->form64.el->e_ident[EI_CLASS] == ELFCLASS32) {
        printf("I am 32 bit data))\n");
        if (in_file->form64.el->e_machine == EM_386)
            printf("I have found the Intel 80386!\n");
        printf("%s:\tfile format elf64-x86-64\n", in_file->name);
        printf("architecture: %x, flags 0x%08x:\n",
               in_file->form64.el->e_machine, in_file->form64.el->e_flags);
        return (0);
    }
    else {
        printf("my_objdump: %s: file format not recognized\n", in_file->name);

        return (84);
    }
}

int read_file(char *path, prop_t *in_file)
{

    struct stat s;
    in_file->fd = open (path , O_RDONLY );
    if (in_file->fd != -1)
    {
        fstat (in_file->fd, &s);
        if (S_ISDIR(s.st_mode)) {
            printf("my_objdump: Warning: '%s' is a directory\n", path);
            return (84);
        }


        in_file->form64.bytes = mmap ( NULL , s . st_size , PROT_READ , MAP_PRIVATE , in_file->fd , 0) ;
        if (in_file->form64.bytes == (void *) -1)
        {
            perror ("mmap");
            return (84);
        }
        close (in_file->fd);
        //elf = in_file->form64.bytes;
        in_file->form64.el = (Elf64_Ehdr *)in_file->form64.bytes;
        if (in_file->form64.el->e_ident[EI_CLASS] == ELFCLASS64)
            printf("I am 64_bits file!\n");
        return (0);
    }
    else {

        printf("my_objdump: %s: %s\n", path, strerror(errno));
        return (84);
    }

}


int my_dump(char *path)
{
    //printf("%s :\n", path);
    prop_t in_file;
    in_file.name = path;

    if (read_file(path, &in_file) == 84)
        return (84);
    if (type_check(&in_file) == 84)
        return (84);
    return show_file(&in_file);
    //printf("%s\n", in_file.form64.bytes);
    //return (0);

}

