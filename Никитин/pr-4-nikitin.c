
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    errno = 0;
    if (argc == 1)
    {
        printf("в программу надо передовать параметры по типу: ./dec2hex 125");
        return 1;
    }
    else if (argc != 2)
    {
        printf("кол-во аргументов не соответствует заданному");
       return 1;
    }
        int num=atoi(argv[1]);
        int ost=0;
        int i=0;
        char str[256];
         do
        {
            ost=num%16;
            if ((ost >=0) || (ost <=9)) str[i]=ost+'0';
            else str[i]=ost+'7';
            num=num/16;
            i++;
        } while (num!=0);
        for (int i=strlen(str);i>=0;i--)
        printf("%c",str[i]);
    return 0;
}