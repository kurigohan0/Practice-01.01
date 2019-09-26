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
strcat(buf,"\\");
	struct dirent *ent=NULL;
	errno = 0;
	if ((dir=opendir(buf)) != NULL)
	{
		while ((ent=readdir(dir)) != NULL)
		{
char* file=NULL;
			char* cur = ent->d_name;
			while ((*cur) && (*cur != '~')) cur++;
			if (*cur=='~')  
			{
				struct stat s;
				if (stat(ent->d_name,&s)==-1) printf("problem file %s",strerror(errno));
				else
				{
					if ((S_ISREG(s.st_mode)) && (s.st_size == 0))
					{
file= malloc(sizeof(char)*strlen(str)+sizeof(char)*strlen(ent->d_name)+3);
						strcpy(file,str);
						strcat(file,"\\");
strcat(file,ent->d_name);
						if (-1 == remove(file)) printf("problem file %s: %s", ent->d_name, strerror(errno));
free(file);
					}
else if (S_ISDIR(s.st_mode))
{
	file= malloc(sizeof(char)*strlen(str)+sizeof(char)*strlen(ent->d_name)+6);
						strcpy(file,str);
						strcat(file,"\\");
strcat(file,ent->d_name);
rec(file);
free(file);

}
	}
				errno = 0;
			} 
		}
		if (errno != 0) printf("problem file %s", strerror(errno));
		closedir(dir);
	}
	else
	{
		printf("catalog open error: %s %s",str,strerror(errno));
	}
}

void main()
{
	rec(".");
}
