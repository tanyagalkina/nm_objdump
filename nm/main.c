/*
** EPITECH PROJECT, 2020
** nm
** File description:
** src
*/

#include "../include/nm.h"

int error64(prop_t *in_file)
{
    in_file->bits = 64;
    if (in_file->form64.ehdr->e_ident[EI_MAG0] != ELFMAG0
        || in_file->form64.ehdr->e_ident[EI_MAG1] != ELFMAG1
        || in_file->form64.ehdr->e_ident[EI_MAG2] != ELFMAG2
        || in_file->form64.ehdr->e_ident[EI_MAG3] != ELFMAG3
        || in_file->form64.ehdr->e_ident[EI_CLASS] != ELFCLASS64) {
        printf("my_nm: %s: file format not recognized\n", in_file->name);
        return (84);
    }
    return (0);
}

int type_check(prop_t *in_file)
{
    if (in_file->form64.ehdr->e_ident[EI_CLASS] == ELFCLASS64)
        return error64(in_file);
    else if (in_file->form64.ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
        if (in_file->form64.ehdr->e_machine == EM_386) {
            return (0);
        }
        printf("my_nm: %s: file format not recognized\n", in_file->name);
        return (84);
    } else {
        printf("my_nm: %s: file format not recognized\n", in_file->name);
        return (84);
    }
}

int corrupted(prop_t *in_file, size_t size)
{
    void *end = (char *)in_file->form64.bytes + size;
    if ((in_file->form64.ehdr = (Elf64_Ehdr *)in_file->form64.bytes) == NULL)
        return (84);
    if ((void *)in_file->form64.ehdr >= (void *)end)
        return (84);
    return (0);
}

int read_file(char *path, prop_t *in_file)
{
    struct stat s;
    in_file->fd = open (path, O_RDONLY);
    if (in_file->fd != -1) {
        fstat (in_file->fd, &s);
        if (S_ISDIR(s.st_mode)) {
            printf("my_nm: Warning: '%s' is a directory\n", path);
            return (84);
        }
        in_file->form64.bytes = mmap ( NULL , s.st_size, PROT_READ, MAP_PRIVATE, in_file->fd, 0) ;
        if (in_file->form64.bytes == (void *) -1) {
            perror ("mmap");
            return (84);
        }
        close (in_file->fd);
        return corrupted(in_file, s.st_size);
    } else {
        printf("my_nm: '%s': %s\n", path, strerror(errno));
        return (84);
    }
}

int my_nm(char *path)
{
    prop_t in_file;
    in_file.name = path;
    if (read_file(path, &in_file) == 84)
        return (84);
    if (type_check(&in_file) == 84)
        return (84);
    printf("my_nm : %s: no symbols\n", path);
    return (0);
}

int main(int ac, char **av)
{
    int ret = 0;

    if (ac == 1) {
            return (my_nm ("a.out"));
        } else {
        for (int i = 1; i < ac; ++i) {
            ret = my_nm(av[i]);
        }
        return (ret);
    }
}