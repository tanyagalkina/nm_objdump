/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

int type_check(prop_t *in_file)
{
    if (in_file->form64.ehdr->e_ident[EI_CLASS] == ELFCLASS64)
        return error64(in_file);
    else if (in_file->form64.ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
        if (in_file->form64.ehdr->e_machine == EM_386) {
            printf("I am nice 32 bit data))\n");
            printf("I have found the Intel 80386!\n");
            printf("%s:     file format elf32-i386\n", in_file->name);
            printf("architecture: i386, flags 0x%08x:\n", \
in_file->form64.ehdr->e_flags);
                   return (0);
        }
        printf("my_objdump: %s: file format not recognized\n", in_file->name);
        return (84);
    }
    else return (84);
}

int read_file(char *path, prop_t *in_file)
{
    struct stat s;
    in_file->fd = open (path, O_RDONLY);
    if (in_file->fd != -1) {
        fstat (in_file->fd, &s);
        if (S_ISDIR(s.st_mode)) {
            printf("my_objdump: Warning: '%s' is a directory\n", path);
            return (84);
        }
        in_file->form64.bytes = mmap ( NULL , s . st_size , PROT_READ , MAP_PRIVATE , in_file->fd , 0) ;
        if (in_file->form64.bytes == (void *) -1) {
            perror ("mmap");
            return (84);
        }
        close (in_file->fd);
        in_file->form64.ehdr = (Elf64_Ehdr *)in_file->form64.bytes;
        return (0);
    } else {
        printf("my_objdump: %s: %s\n", path, strerror(errno));
        return (84);
    }
}

int my_dump(char *path)
{
    prop_t in_file;
    in_file.name = path;

    if (read_file(path, &in_file) == 84)
        return (84);
    if (type_check(&in_file) == 84)
        return (84);
    return show_file(&in_file);
}