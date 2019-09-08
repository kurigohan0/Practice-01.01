#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
  DIR * dir = NULL;
  struct dirent * ent = NULL;
  if ((dir = opendir(".")) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      bool flag = false;
      int k;
      for (int i = 0; i < strlen(ent - > d_name); i++) {
        if (ent - > d_name[i] == '$') {
          flag = true;
          k = i;
          break;
        }
      }
      if (flag) {
        struct stat s;
        if (-1 == stat(ent - > d_name, & s)) printf("problem %s: %s", ent - > d_name, strerror(errno));
        else {
          char st[20];
          sprintf(st, "%lu", s.st_size);
          char str1[100];
          char str2[100];
          for (int i = strlen(ent - > d_name) - 1; i > k; i--) {
            str2[i - k - 1] = ent - > d_name[i];
          }
          strncat(str1, ent - > d_name, k);
          strcat(str1, st);
          strcat(str1, str2);
          printf("%s", str1);
          if (S_ISREG(s.st_mode)) {
            if (-1 == rename(ent - > d_name, str1)) printf("problem file %s: %s", ent - > d_name, strerror(errno));
          }
        }
      }
    }
    closedir(dir);
    return 0;
  } else {
    printf("ci: %s", strerror(errno));
    return 1;
  }
}