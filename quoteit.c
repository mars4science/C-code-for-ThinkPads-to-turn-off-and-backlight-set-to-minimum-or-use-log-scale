// argv[0] is name of the program, argc includes it

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])  
{ 
    if (argc ==2 && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")))
    {
        printf("The program surrounds set of arguments with double quotes\n");
        printf("Example: quoteit 12 23 outputs \"12 23\"\n");
        return 0;
    } 
    //printf("%d\n", argc); 
    
    printf("\""); 
    for (int i=1; i< argc; i++) 
    {
        printf("%s", argv[i]);
        if (i<argc-1) printf(" ");  
    } 
    printf("\"\n");
    return 0; 
}
