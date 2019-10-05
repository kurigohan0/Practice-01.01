#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int compareFiles(FILE *fp1, FILE *fp2) 
{ 
    char ch1 = getc(fp1); 
    char ch2 = getc(fp2); 
  
    // error keeps track of number of errors 
    // pos keeps track of position of errors 
    // line keeps track of error line 
    int error = 0, pos = 0, line = 1; 
  
    // iterate loop till end of file 
    while (ch1 != EOF && ch2 != EOF) 
    { 
        pos++; 
        if (ch1 == '\n' && ch2 == '\n') 
        { 
            line++; 
            pos = 0; 
        } 

        if (ch1 != ch2) 
        { 
            error++; 
        } 
  
        // fetching character until end of file 
        ch1 = getc(fp1); 
        ch2 = getc(fp2); 
		if(error!=0)
		{
			printf("%s\n", "false");
			return 1;
		}
		else
		{
			printf("%s\n", "true");
			return 1;
		}
    } 
  } 

int main(int argc,char* argv[])
{
    errno=0;
    if (argc==1)
    {
        printf("В программу надо передовать параметры по типу: ./diff test1.txt test2.txt");
        return 1;
    }
    else if (argc != 3) 
    {
        printf("кол-во аргументов не соответствует заданному");
        return 1;
    }
    
	FILE *fp1 = fopen(argv[1], "r"); 
    FILE *fp2 = fopen(argv[2], "r");    

	if (fp1 == NULL || fp2 == NULL) 
    { 
       printf("Error : Files not open"); 
	   return 1;
    } 
	if(compareFiles(fp1, fp2) == 1)
	return 1;
	fclose(fp1); 
    fclose(fp2); 
    
    return 0;
}