/*
** EPITECH PROJECT, 2020
** obj.h
** File description:
*/

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
    Elf32_Ehdr *ehdrl;
    Elf32_Shdr *shdr;
} f32bits_t;

typedef struct f64_bits
{
    void *end;
    char *name;
    char *itself;
    void *bytes;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
} f64bits_t;

typedef struct prop
{
    char *name;
    int fd;
    int bits;
    f32bits_t form32;
    f64bits_t form64;
} prop_t;

unsigned int get_hex_width(int current, int size);
void print_char(char ch);
void print_addr(unsigned width, unsigned tmp);
int show_file(prop_t *in_file);
int my_dump(char *path);
int error64(prop_t *);
void show_dump64(f64bits_t *type_64);
void print_sections(const Elf64_Shdr, char *);
void print_space(unsigned int i, char end);
void print_hex(const Elf64_Shdr shdr, char *bytes, \
unsigned int i);


#endif /* !OBJDUMP_H_ */
