// Абдуллоев Парвиз. Вариант 1.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc,char* argv[])
{
    errno=0;
    if (argc==1)
    {
        printf("В программу надо передовать параметры по типу: ./mycp test1 test2");
        return 1;
    }
    else if (argc != 3) 
    {
        printf("кол-во аргументов не соответствует заданному");
        return 1;
    }
    
    if (-1 == rename(argv[1],argv[2])) printf("%s",strerror(errno));
    
    
    return 0;
}