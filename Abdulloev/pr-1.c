// Абдуллоев Парвиз. Вариант 1.

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>

int main()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    errno = 0;
    if (d) {
        while ((dir=readdir(d)) != NULL) {
            struct stat file;

            if (stat(dir->d_name, &file) == -1){
                printf("Ошибка в файле %s", strerror(errno));
            }
            else if (S_ISREG(file.st_mode)) // Проверка на regular file
            { 

                int countOfVowels;
                countOfVowels = 0; // кол-во гласных букв в названии файла
                char* s=dir->d_name;
                while ((*s) && (countOfVowels < 3)) {

                    switch (*s){
                        case 'a':
                        case 'o':
                        case 'i':
                        case 'e':
                        case 'u':
                        case 'y':
                        case 'A':
                        case 'O':
                        case 'I':
                        case 'E':
                        case 'U':
                        case 'Y':
                            countOfVowels += 1;
                            break;    
                    }
                    s++;
                }

                if (countOfVowels == 2) { // Если имя файла содержит 2 гласные буквы

                    char old[strlen(dir->d_name) ];
                    strcpy(old, dir->d_name + 1);

                    // Проверка
                    if ((rename(dir->d_name, old)) == 0) {
                        printf("%s >>>>> %s\n", dir->d_name,  old);
                    } 
                    else {
                        printf("Файле не переименован %s", strerror(errno));  
                    }  
                }
            }    
        }
        if (errno != 0 ) {
            printf("Error reading directory %s", strerror(errno));
        }
        closedir(d); // не забываем закрыть директорию

    } else {
        printf("%s", strerror(errno));
    }

    return 0;
}