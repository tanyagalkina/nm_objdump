/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** src
*/

#include "../include/obj.h"

int corrupted(prop_t *in_file, size_t size)
{
    void *end = (char *)in_file->form64.bytes + size;
    in_file->form64.end = end;
    if ((in_file->form64.ehdr = (Elf64_Ehdr *)in_file->form64.bytes) == NULL) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", in_file->name);
        return (84);
    }
    if ((void *)in_file->form64.ehdr >= (void *)end) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", in_file->name);
        return (84);
    }
    return (0);
}

int error32(prop_t *in_file)
{
    if (in_file->form64.ehdr->e_machine == EM_386) {
            printf("%s:     file format elf32-i386\n", in_file->name);
            printf("architecture: i386, flags 0x%08x:\n", \
in_file->form64.ehdr->e_flags);
            return (0);
        }
        fprintf(stderr, "objdump: %s: file format not recognized\n", in_file->name);
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

static int print_strerror(char *path)
{
    struct stat s;

    if (errno == ENOENT) {
        fprintf(stderr, "objdump: '%s': %s\n", path, "No such file");
        return (84);
    }
    stat(path, &s);
    if (!S_ISREG(s.st_mode)) {
        fprintf(stderr, "objdump: Warning: '%s' is not an ordinary file\n", path);
        return (84);
    }
    fprintf(stderr, "objdump: %s: %s\n", path, strerror(errno));
    return (84);
}

int read_file(char *path, prop_t *in_file)
{
    struct stat s;

    in_file->fd = open(path, O_RDONLY);
    if (in_file->fd != -1) {
        fstat (in_file->fd, &s);
        if (S_ISDIR(s.st_mode)) {
            fprintf(stderr, "objdump: Warning: '%s' is a directory\n", path);
            return (84);
        }
        in_file->form64.bytes = mmap ( NULL , s.st_size , PROT_READ , MAP_PRIVATE , in_file->fd , 0) ;
        if (in_file->form64.bytes == (void *) -1) {
            perror ("mmap");
            return (84);
        }
        close (in_file->fd);
        return corrupted(in_file, s.st_size);
    } else
        return (print_strerror(path));
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