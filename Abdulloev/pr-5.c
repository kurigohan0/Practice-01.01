// Абдуллоев Парвиз. Вариант 1.
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



struct list_int
{
    pid_t num;
    struct list_int *next;
};


// Добавление процесса в список
void addList(struct list_int **p, pid_t k)
{
    struct list_int *pr = NULL;
    if (*p == NULL)
    {
        pr = malloc(sizeof(struct list_int));
        if (pr)
        {
            *p = pr;
            pr->num = k;
            pr->next = NULL;
        }
        else
        {
            printf("Необходимо выделить память!");
        }
    }
    else
    {
        pr = *p;
        while (pr->next != NULL) pr = pr->next;
        pr->next = malloc(sizeof(struct list_int));
        if (pr->next)
        {
            pr->next->num = k;
            pr->next->next = NULL;
        }
        else printf("Необходимо выделить память!");
    }
}


// Получение последнего элемента
pid_t getLastElement(struct list_int *p)
{
    struct list_int *pr = p;
    
    if (p != NULL)
    {
        while (pr->next != NULL) // доходим до конца
            pr = pr->next;

        return pr->num;
    }

    return 0;
}


// Удалить процесс из списка
void deleteList(struct list_int *p)
{
    if (p)
    {
        struct list_int *points;
        while (p != NULL)
        {
            points = p;
            p = p->next;
            free(points);
        }
    }
}




void main()
{
    char *str = malloc(sizeof(char) * 2);
    if (str)
    {
        strcpy(str, ".");
        struct list_int *process = NULL;
        DIR *dir = NULL;
        struct dirent *ent = NULL;
        errno = 0;

        if ((dir = opendir(str)) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                if (str)
                {
                    char *file = NULL;
                    char *cur = ent->d_name;
                    file = malloc(sizeof(char) * strlen(str) + sizeof(char) * strlen(ent->d_name) + 2);

                    if (file == NULL) printf("Необходимо выделить память!");
                    else
                    {
                        strcpy(file, str);
                        strcat(file, "/");
                        strcat(file, ent->d_name);
                        printf("%s\n", file);
                        struct stat s;
                        if (stat(file, &s) == -1)
                        {
                            printf("problem files %s\n", strerror(errno));
                        }
                                
                        else
                        {
                            int countOfVowels;
                            countOfVowels = 0;
                            while ((*cur) && (countOfVowels < 3))
                            {
                                switch (*cur)
                                {
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
                                    {
                                        printf("Необходимо выделить память");
                                    }                                        
                                    else
                                    {
                                        strcpy(file2, str);
                                        strcat(file2, "/");
                                        strcat(file2, ent->d_name + 1);
                                        if ((rename(file, file2)) == 0)
                                        {
                                            printf("Файл %s переименован >>>>>>>>> %s\n", file, file2);
                                        }
                                        else
                                        {
                                            printf("Файле не переименован %s", strerror(errno));
                                        }
                                        free(file2);
                                    }
                                }
                            }

                            if (S_ISDIR(s.st_mode) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
                            {
                                pid_t i = fork();
                                
                                if (i > 0) // родительский  
                                {
                                    addList(&process, i);
                                }
                                 

                                else if (i == 0) // дочерний
                                {
                                    deleteList(process);
                                    free(str);
                                    str = malloc(sizeof(char) * strlen(file) + 1);
                                    if (str)
                                    {
                                        strcpy(str, file);
                                        closedir(dir);
                                        if ((dir = opendir(file)) == NULL)
                                        {
                                            printf("Ошибка при чтении каталога: %s %s\n", str, strerror(errno));
                                        }
                                    }
                                    else
                                        printf("Необходимо выделить память!");
                                }
                                else if (i < 0) // ошибка
                                {
                                    printf("Ошибка: %s %s\n", str, strerror(errno));
                                }
                            }
                        }
                        free(file);
                    }
                }
                else
                    printf("error");
                errno = 0;
            }
            if (errno != 0)
                printf("Ошибка при чтении файла %s\n", strerror(errno));
            if (getLastElement(process) > 0) // есть ли родительский процесс
            {
                struct list_int *points = process;
                while (points != NULL)
                {
                    int status;
                    if (waitpid(points->num, &status, 0) == -1) // ожидает родительского процесса
                        printf("%s\n", strerror(errno));
                    else
                    {
                        if (!WIFEXITED(status)) // не равно нулю, если дочерний процесс успешно завершился
                            printf("Error close process");
                    }
                    points = points->next;
                }
                deleteList(process);
            }
            closedir(dir);
        }
        else
        {
            printf("Ошибка при чтении каталога: %s %s\n", str, strerror(errno));
        }
        if (str) free(str);
    }
    else
    {
        printf("Необходимо выделить память!");
    }
}