#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct f32_bits
{
    char *name;
    Elf32_Ehdr *el;
    Elf32_Shdr *sh;
} f32bits_t;

typedef struct f64_bits
{
    char *name;
    void *bytes;
    Elf64_Ehdr *el;
    Elf64_Shdr *sh;
} f64bits_t;

typedef struct prop
{
    char *name;
    int fd;
    int bits;
    f32bits_t form32;
    f64bits_t form64;
} prop_t;


int my_dump(char *path);


//#define MAGIC_NUMBER	"\177ELF"

#endif /* !OBJDUMP_H_ */
