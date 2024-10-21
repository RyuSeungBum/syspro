#include <stdio.h> 
#include "bookquery.c"
#include "bookupdate.c"
#include "db.dat"


int main(int argc, char* argv[]) 
{ 
struct student rec;
FILE *fp;
if (argc != 2) {
fprintf(stderr, "How to use: %s FileName\n",argv[0]);
exit(1); 
}
fp = fopen(argv[1], "wb");
printf("%-2s %-8s %-6s %-4s %-10s %-6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow"); 
while (scanf("%d %s %s %d %d %s", &rec.id, rec.bookname, &rec.author, &rec.year , &rec.numofborrow , &rec.borrow) == 6) 
fwrite(&rec, sizeof(rec), 1, fp);
fclose(fp);
exit(0);
}
