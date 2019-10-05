#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void rec(const char* str)
{ 
	DIR *dir = NULL;
	char* buf = malloc(sizeof(char)*strlen(str)+1);
	strcpy(buf,str);
	struct dirent *ent=NULL;
	errno = 0;
	if((dir=opendir(buf)) != NULL)//todo: если происходит ошибка, то надо выводить ее описание (V)
	{
		while((ent = readdir(dir)) != NULL)
		{
			char* file=NULL;
			char* cur = ent->d_name;
			file = malloc(sizeof(char) * strlen(str) + sizeof(char) * strlen(ent->d_name) + 2);
			if (file == NULL)
			{
				printf("выдели память");
			}
			else
			{
				strcpy(file, str);
				strcat(file, "/");
				strcat(file, ent->d_name);
				struct stat s;
			
				
				if(stat(file, &s) == -1)
				{
					printf("%s\n", strerror(errno));
				}
				else
				{
					int size = s.st_size;
					
					//регулярный файл: man 2 stat -> регулярный файл
					if(size % 2 != 0 && S_ISREG(s.st_mode))
					{
					//проверь для случай, когда ! есть (готово)
						if(ent->d_name[strlen(ent->d_name) - 1] != '!')
						{
							char sign[1] = "!";
							char file2[strlen(file)+1];
							strcpy(file2, file);
							printf("%s\n", "llls");
							printf("%s\n", file2);
							int ret = rename(file, strcat(file2, sign));
							
						//нет проверки
							if(ret == 0)
							{
								printf("%s\n", strerror(errno));
							}
							else
							{
								printf("%s\n", "File renamed.");
							}
						}
					}
					else
					{
						if (S_ISDIR(s.st_mode) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
						{
							printf("%s\n", file);
							rec(file);
						}
						free(file);
					}
				}
			}
			errno = 0;
		}
		if(errno != 0)
		{
			printf("%s\n", strerror(errno));
		}
		closedir(dir);
	}
	else
	{
		printf("%s", strerror(errno));
	}

}



int main()
{
	
	rec(".");
	return 0;

}
