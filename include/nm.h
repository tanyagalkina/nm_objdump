/*
** EPITECH PROJECT, 2020
** nm.h
** File description:
*/

#ifndef NM_H_
#define NM_H_

#include <elf.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

typedef struct f64_bits
{
    char *name;
    char *itself;
    void *bytes;
    void *end;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
} f64bits_t;

typedef struct prop
{
    char *name;
    int fd;
    int bits;
    f64bits_t form64;
} prop_t;

#endif /* !NM_H_ */
