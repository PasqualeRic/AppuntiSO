
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct entry
    {
        char *name;
        int num;
    } syscall;
    

    int main(int argc, char const *argv[])
    {
        syscall list[] = {
   };int length = -1;
    for(int i = 0; i < length; i++)
    {
        if (strcmp(argv[1], list[i].name) == 0)
        {
            printf("%s %d\n", list[i].name, list[i].num);
            return 0;
        }
    }
    printf("system call does not exist\n");
    return 1;
    }
    