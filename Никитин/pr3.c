#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void rec(const char* str)
{ 
	DIR *dir=NULL;
	char* buf = malloc(sizeof(char)*strlen(str)+1);
	strcpy(buf,str);
	struct dirent *ent=NULL;
	errno = 0;
	if ((dir=opendir(buf)) != NULL)
	{
		while ((ent=readdir(dir)) != NULL)
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
				if (stat(file,&s)==-1) printf("problem files %s\n",strerror(errno));
				else
				{
					while ((*cur) && (*cur != '~')) cur++;
					if (*cur=='~')  
					{
						if ((S_ISREG(s.st_mode)) && (s.st_size == 0))
						{
							if (-1 == remove(file)) printf("problem file %s: %s\n", ent->d_name, strerror(errno));
						}
					}
					if (S_ISDIR(s.st_mode) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
					{
						rec(file);
					}
				}
				free(file);
			}
			errno = 0;
		}
		if (errno != 0) printf("problem file %s\n", strerror(errno));
		closedir(dir);
	}
	else
	{
		printf("catalog open error: %s %s\n",str,strerror(errno));
	}
}





void main()
{
	rec(".");
}
