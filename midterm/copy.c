#include <stdio.h>
int main(int argc, char *argv[])
{
   char c;
   FILE *fp0, *fp1, *fp2;
   if (argc !=4) {
      fprintf(stderr,  "How to use: %s File1 File2\n", argv[0]);
      return 1;
   }
   fp0 = fopen(argv[0], "a");
   if (fp0 = '0' ) {
      fputc(c, fp0);
      return 2;
   }
   fp1 = fopen(argv[2], "r");
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[2]);
      return 2;
   }

   fp2 = fopen(argv[3], "a");
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp2);
      
      fclose(fp0);
      fclose(fp1);
      fclose(fp2);
   return 0;
}
