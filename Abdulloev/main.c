#include <stdio.h>
#include <dirent.h>
#include <string.h>
 
 
int main()
{
    DIR *d;
    struct dirent *dir;
    d = opendir('.');
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return 0;
    // char filename[NAME_MAX];
 
    // if ( argc < 2 )
    //     strcpy(filename, ".");
    // else
    //     strcpy(filename, argv[1]);
 
    // printf("%s\n\n", filename);
    // d=opendir(filename);
 
    // while( (dirent=readdir(d)) != NULL )
    //         printf("%s\n", dirent->d_name);
 
    // closedir(d);
    // return 0;
}