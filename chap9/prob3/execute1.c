#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
   printf("parent process start\n");
   if (fork() == 0) {
      execl("/bin/echo", "echo", "hello", NULL);
      fprintf(stderr, "fail"); 
      exit(1);
   }
   printf("parent process end\n");
}

