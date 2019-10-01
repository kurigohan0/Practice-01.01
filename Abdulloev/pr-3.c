// Абдуллоев Парвиз. Вариант 1.
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void rec(const char *str)
{
    DIR *dir = NULL;
    char *buf = malloc(sizeof(char) * strlen(str) + 1);
    strcpy(buf, str);
    struct dirent *ent = NULL;
    errno = 0;
    if ((dir = opendir(buf)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            char *file = NULL;
            char *cur = ent->d_name;
            file = malloc(sizeof(char) * strlen(str) + sizeof(char) * strlen(ent->d_name) + 2);
            if (file==NULL)
            {
                printf("выдели память");
            }
            else
            {
                strcpy(file, str);
                strcat(file, "/");
                strcat(file, ent->d_name);
                struct stat s;
                if (stat(file, &s) == -1) printf("problem files %s\n", strerror(errno));
                else
                {
                    char *cur = ent->d_name;
                    int countOfVowels;
                    countOfVowels = 0;

                    while ((*cur) && (countOfVowels < 3))
                    {
                        switch (*cur) {
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
                            countOfVowels++;
                            break;
                        }
                        cur++;
                    }

                    if (countOfVowels == 2)
                    {
                        if ((S_ISREG(s.st_mode)))
                        {
                            char *file2 = malloc(sizeof(char) * strlen(str) + sizeof(char) * strlen(ent->d_name) + 1);
                            if (file2 == NULL)
                                printf("Необходимо выделить память");
                            else
                            {
                                strcpy(file2, str);
                                strcat(file2, "/");
                                strcat(file2, ent->d_name+1);
                                if ((rename(file, file2)) == 0)
                                {
                                    printf("%s >>>>> %s\n", file, file2);
                                }
                                else
                                {
                                    printf("Файле не переименован %s", strerror(errno));
                                }
                                free(file2);
                            }
                        }
                    }
                    else if (S_ISDIR(s.st_mode) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
                    {
                            rec(file);
                    }
                }
                free(file);
            }
            errno = 0;
        }
        if (errno != 0)
            printf("problem file %s\n", strerror(errno));
        closedir(dir);
    }
    else
    {
        printf("catalog open error: %s %s\n", str, strerror(errno));
    }
}

int main()
{
    rec(".");
}
