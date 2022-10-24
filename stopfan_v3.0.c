// argv[0] is name of the program, argc includes it

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
  
// Taking argument from command line 
int main(int argc, char *argv[])  
{ 
    FILE *fptr;
    char driver_file_name[] = "/proc/acpi/ibm/fan";
    char ch;
    if (argc > 3)  
    { 
        printf("only 1 or 2 arguments are expected, -h/--help for help\n"); 
        return 1; 
    } // else if (argc < 2) argv[1]="0"; no good portable idea, see https://stackoverflow.com/questions/25737434/is-argvn-writable

    if (argc > 1 && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")))
    {
        printf("Version 3.0. The program works with fan on thinkpad computers\n\n");
        printf("It writes \"level ARG\" to %s, where ARG is argument given on command line\n", driver_file_name);
        printf("Argument can usually be from 0 (full silence) to 7; it can be omitted, then 0 is used\n");
        printf("There are some other commands (omit `level` word) to be passed as arguments, use read (see below) to find out\n");
        printf("If \"read\" is the argument, it will read from the above file and output to standard\n");
        return 0;
    } 


    // check for right-away correct parameters to save on opening file descriptors

    if (argc > 3 || argc == 3 && strcmp(argv[1],"watchdog"))
    {
        printf("Incorrect parameter(s), use -h/--help for details\n");
        return 1;
    } 

    // process read command

    if (argc > 1 && (!strcmp(argv[1],"read")))
    {
        printf("Here is was thinkfan driver gives from reading %s\n", driver_file_name);
        fptr = fopen(driver_file_name,"r");
        if(fptr == NULL)
        {
            printf("Could not open %s for reading; is thinkfan installed?\n", driver_file_name);   
            return 1;
        } 
        while ((ch = fgetc(fptr)) != EOF)
        {
            printf("%c", ch);
        }
        fclose(fptr);
        return 0;
    } 

    // read option processed, now only writes are left
    // interestingly as I've noted from thinkfan code, if "/proc/acpi/ibm/fan" is opened with r+ modification timestamp does not change
    // if opened with w than modification timestamp does change


    fptr = fopen(driver_file_name,"r+");
    if(fptr == NULL)
    {
        printf("Could not open %s for writing; is thinkfan installed? are you sure you run as root?\n", driver_file_name);   
        return 1;        
    }


    // strcomp returns 0 if same

    if (argc == 3 && !strcmp(argv[1],"watchdog") )
    {
        fprintf(fptr, "%s %s\n", argv[1], argv[2]);
        fclose(fptr);
        return 0;
    } 


    char *text_commands_level[] = {"auto", "disengaged", "full-speed", 0};
    char *text_commands_single[] = {"enable", "disable", 0};
    if (argc == 2)
    {

        int i = 0;
        while(text_commands_level[i]) {
            if(strcmp(text_commands_level[i], argv[1]) == 0) {
                fprintf(fptr, "level %s\n", argv[1]);
                fclose(fptr);
                //break;
                return 0;
            }
            i++;
        }
        i = 0;
        while(text_commands_single[i]) {
            if(strcmp(text_commands_single[i], argv[1]) == 0) {
                fprintf(fptr, "%s\n", argv[1]);
                fclose(fptr);
                //break;
                return 0;
            }
            i++;
        }

    } 

    // checked for all correct text parameters, the rest is signle digit parameter
    
    if (argc == 2 && (strlen(argv[1])!=1 || !isdigit(*argv[1]))) // *argv[1] should give first character
    {
        printf("Incorrect parameter(s), use -h/--help for details\n");
        fclose(fptr);
        return 1;
    } 


    if (argc==1) 
        fprintf(fptr, "level 0\n");
    else
        fprintf(fptr, "level %s\n", argv[1]);
    
    fclose(fptr);
    return 0;
} 

// int a; 
// Converting string type to integer type 
// using function "atoi(argument)" 
// a = atoi(argv[1]);    
// printf("%d is largest ",c); 
// exit(1);
