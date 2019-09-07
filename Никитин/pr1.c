#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

int main()
{
 DIR *dir=NULL;
 struct dirent *ent=NULL;
 if ((dir=opendir(".")) != NULL)
 {
  while ((ent=readdir(dir)) != NULL)
  {
   bool flag=false;
   for (int i=0; i < strlen(ent->d_name); i++)
   {
    if (ent->d_name[i]=='~')
    {
     flag=true;
     break;
    }
   }
   if (flag)   
   {
    struct stat s;
    if (stat(ent->d_name,&s)==-1) printf("problem file %s",strerror(errno));
    if ((S_ISREG(s.st_mode))&&(s.st_size==0))
    {
     if (-1==remove(ent->d_name)) printf("problem file %s: %s",ent->d_name,strerror(errno));
    }
   } 
  }
  closedir(dir);
  return 0;
 }
 else
 {
  printf("ci: %s",strerror(errno));
  return 1;
 }
}
