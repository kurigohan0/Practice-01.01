#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if(d)//todo: если происходит ошибка, то надо выводить ее описание (V)
	{
		while((dir = readdir(d)) != NULL) 
		{
			struct stat st;
			stat(dir->d_name, &st);
			int size = st.st_size;
			printf("%d\n", size);
			//регулярный файл: man 2 stat -> регулярный файл
			if(size % 2 != 0 && S_ISREG(st.st_mode))
			{
				//проверь для случай, когда ! есть (готово)
				if(dir->d_name[strlen(dir->d_name) - 1] != '!')
				{
					char old[strlen(dir->d_name) + 1];
					char sign[1] = "!";
					strcpy(old ,dir->d_name);

					
					int ret = rename(dir->d_name, strcat(old, sign));
					
					//нет проверки
					if(ret == 0)
					{
						printf("%s\n", dir->d_name);
					}
					else
					{

						printf("%s\n", "File renamed.");
					}
				}
			}
		}
		closedir(d);
	}
	else
	{
		printf("%s", strerror(errno));
	}
	
return 0;

}
