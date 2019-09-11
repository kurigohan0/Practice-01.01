#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void main()
{
	DIR *dir=NULL;
	struct dirent *ent=NULL;
	errno = 0;
	if ((dir=opendir(".")) != NULL)
	{
		while ((ent=readdir(dir)) != NULL)
		{
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
						printf("%s", ent->d_name);
						if (-1 == remove(ent->d_name)) printf("problem file %s: %s", ent->d_name, strerror(errno));
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
		printf("catalog open error: %s",strerror(errno));
	}
}
     
