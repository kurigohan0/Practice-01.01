// Абдуллоев Парвиз. Вариант 1.

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdbool.h>

int main()
{
	DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir=readdir(d)) != NULL) {
            struct stat file;
            stat(dir->d_name, &file);
            if (S_ISREG(file.st_mode)){ // Проверка на regular file

                int i, countOfVowels;
                countOfVowels = 0; // кол-во гласных букв в названии файла

                for (i = 0; i < strlen(dir->d_name); i++) {
                    if ((dir->d_name[i] == 'a') || (dir->d_name[i] == 'o') || (dir->d_name[i] == 'i')
                        || (dir->d_name[i] == 'e') || (dir->d_name[i] == 'u') || (dir->d_name[i] == 'y')){
                        countOfVowels += 1;   
                    }
                }

                if (countOfVowels == 2) { // Если имя файла содержит 2 гласные буквы

                    char old[strlen(dir->d_name) + 1];
                    strcpy(old, dir->d_name);

                    int indexToDel = 0; // индекс символа, который мы удалим
                    memmove(&old[indexToDel], &old[indexToDel + 1], strlen(old) - indexToDel); // удаляем первый символ

                    // Проверка
                    if ((rename(dir->d_name, old)) == 0) {
                        printf("%s >>>>> %s\n", dir->d_name,  old);
                    } 
                    // else {
                    //     
                    // }  
                }
            }    
        }
        closedir(d); // не забываем закрыть директорию

    } else {
        printf("%s", strerror(errno));
    }

    return 0;
}