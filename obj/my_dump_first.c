//
// Created by tag43 on 3/8/21.
//


#include "../include/obj.h"

int type_check(prop_t *in_file)
{
    (void) in_file;
    return (0);

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
        if (in_file->form64.bytes == -1)
        /*{


                    printf ("mmap (%s) : %08x\n", path , in_file->form64.bytes);
                    elf = in_file->form64.bytes;
                    if (elf->e_ident[EI_CLASS] == ELFCLASS64)
                        printf("I am 64_bits file!\n");
                    printf (" Section Header Table : addr = %08 x , nb = %d\n",
                            elf -> e_shoff , elf -> e_shnum );
        } else {*/
        {
            perror ("mmap");
            return (84);
        }
        close (in_file->fd);
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

    if (read_file(path, &in_file) == 84)
        return (84);
    if (type_check(&in_file) == 84)
        return (84);
    return (0);

}

