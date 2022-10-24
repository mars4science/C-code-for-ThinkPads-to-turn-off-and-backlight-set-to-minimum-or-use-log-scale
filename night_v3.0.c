/* 
    Version 1 can set min and max backlight brighness
    Version 2 adds support for gradual brightness control
    Version 3 moves to agrp.h usage and adds support for number of steps, mnimimal and maximum brightness parameters
    to install use (Disclaimer: as sets execution bits might increase security exposure):
    night="night" bash -c 'gcc night_v2.2.c -lm -o $night && sudo cp $night /usr/bin && sudo chmod a+s /usr/bin/$night'
    then use command with name_you_like and also assign with parameters to hot-keys, including standard brighness keys 

    TODO in version 3+: use some "standard" arg library, add agrs of number of steps, min brightness, maybe different scale functions, changes by number of decibels also 
    Development notes:    
   *argv[1] should give first character
*/ 
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <argp.h>

// choose log function - base 10 or e etc
// actually one can try to use non-log if wishes

// define is not Ok to define pw(x, power), so...
// edit the following functions code to change behaviour (now log 10)
#define scale_function_text "log 10" // only for help output, log10 could be convinient if one wants to increment in decibels (+1 / -1 in steps from min to max)
double scale_function(int);
double inverse_scale_function(double);
const int min_brighness_int = 1;
const char* min_brighness = "1";

int read (const char *file_name, char * brighness);

int steps = 10; // number of step to gradually increment on logarighmic scale
const char *steps_arg_prefix = "steps=";

const char * argp_program_version="night 3.0"
const char * argp_program_bug_address="alexei.martianov.2020@gmail.com"
const struct argp_option *options
  

/* This structure is used by main to communicate with parse_opt. */
struct arguments
{
  char *args[2];            /* ARG1 and ARG2 */
  int verbose;              /* The -v flag */
  char *outfile;            /* Argument for -o */
  char *string1, *string2;  /* Arguments for -a and -b */
};

/*
   OPTIONS.  Field 1 in ARGP.
   Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
*/
static struct argp_option options[] =
{
  {"verbose", 'v', 0, 0, "Produce verbose output"},
  {"steps",   'a', "10", 0, "Number of steps for change from min to max"},
  {"bravo",   'b', "STRING2", 0, "Do something with STRING2 related to the letter B"},
  {"output",  'o', "OUTFILE", 0, "Output to OUTFILE instead of to standard output"},
  {0}
};


/*
   PARSER. Field 2 in ARGP.
   Order of parameters: KEY, ARG, STATE.
*/
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'v':
      arguments->verbose = 1;
      break;
    case 'a':
      arguments->string1 = arg;
      break;
    case 'b':
      arguments->string2 = arg;
      break;
    case 'o':
      arguments->outfile = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
	{
	  argp_usage(state);
	}
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 2)
	{
	  argp_usage (state);
	}
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/*
   ARGS_DOC. Field 3 in ARGP.
   A description of the non-option command-line arguments
     that we accept.
*/
static char args_doc[] = "ARG1 ARG2";

/*
  DOC.  Field 4 in ARGP.
  Program documentation.
*/
static char doc[] =
"argex -- A program to demonstrate how to code command-line options
and arguments.\vFrom the GNU C Tutorial.";

/*
   The ARGP structure itself.
*/
static struct argp argp = {options, parse_opt, args_doc, doc};

/*
   The main function.
   Notice how now the only function call needed to process
   all command-line options and arguments nicely
   is argp_parse.
*/

int main(int argc, char *argv[])  
{ 
    FILE *fptr;
    const char *driver_file_name = "/sys/class/backlight/intel_backlight/brightness";
    const char *driver_file_name_max = "/sys/class/backlight/intel_backlight/max_brightness";
    char ch;
    char brighness[10]; // assume range is not larger then 10^10
    char max_brighness[10];
    
    // argv[0] is name of the program, argc includes it

    // if (strncmp(str, "test", 4) == 0) { printf("it matches!"); }
    // https://stackoverflow.com/questions/13832321/compare-part-of-an-input-string-using-strcmp-in-c

    if (argc = 3) then 
// char * strncpy (char *restrict to, const char *restrict from, size_t size)
/*

Function: char * strndup (const char *s, size_t size)

    Preliminary: | MT-Safe | AS-Unsafe heap | AC-Unsafe mem | See POSIX Safety Concepts.

    This function is similar to strdup but always copies at most size bytes into the newly allocated string.

    If the length of s is more than size, then strndup copies just the first size bytes and adds a closing null byte. Otherwise all bytes are copied and the string is terminated.

    This function differs from strncpy in that it always terminates the destination string.

    As noted below, this function is generally a poor choice for processing text.

    strndup is a GNU extension. 
*/


        char* step_check;
        

if (strncmp(argv[2], steps_arg_prefix, 4) == 0 > strlen (steps_arg_prefix) && argv[2][0..
    if (argc > 2)
    { 
        printf("only 1 or no arguments are expected, -h/--help for help\n"); 
        return 1; 
    } // else if (argc < 2) argv[1]="0"; no good portable idea, see https://stackoverflow.com/questions/25737434/is-argvn-writable

    if (argc > 1 && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")))
    {
        printf("\nNight, Version 2.2., written and tested on Linux kernel 5.4, Lenovo ThinkPad.).\n");
        printf("Copyright (c) Alexei Martianov, 2021, license(s) included in the package.\n\n");

        printf("The program is written to work with Intel graphics driver to read/set backlight.\n");
        printf("Program does not try to catch errors if produced by the driver.\n");
        printf("Decimal places are not supported as current driver does not seem to support them.\n\n");
        printf("Arguments: none, N0 set = {0,1,2,...}, max, +1, -1, read, steps=N.\n\n");

        printf(" - The program is written to attempt to write to %s \n", driver_file_name);
        printf("   to set screen backlight brightness level.\n");
        printf(" - In case of no arguments \"%s\" is used as parameter to write to the driver.\n", min_brighness);
        printf(" - For \"read\" argument, this program is written to try\n"); 
        printf("   to read from the above file descriptor and output to standard\n");
        printf("   and also from %s to get max brighness supported.\n", driver_file_name_max);
        printf(" - Argument \"max\" means to read from %s and write it\n", driver_file_name_max);
        printf("   to %s.\n", driver_file_name);
        printf(" - Arguments +1 and -1 mean trying to modify brighness based on scale function and number of steps;\n");
        printf("   if result is below min constant, then 0 is used and that is expected to blank the screen,\n");
        printf("   -1 / +1 when brightness is at 0 is coded to set minimal brightness; +1 at max is writtten to produce no effect.\n");
        printf(" - Program uses hardcoded constants:\n");
        printf("   minimal brightness: %d, number of steps: %d, and %s scale function.\n", min_brighness_int, steps, scale_function_text);
        printf("   Note: actual number of steps could be less due to rounding and +1 on the way up from 0 (as 0 might not equal min).\n");
        printf(" - Version 3+ expected to support more arguments in place of some current constants.\n");
        return 0;
    } 
    
    // strcomp returns 0 (false) if same
    if (argc == 2 && (!strcmp(argv[1], "read")))
        {
            if (read(driver_file_name, brighness)) return 1; else
                printf("Reading %s gives: %s\n", driver_file_name, brighness);
            if (read(driver_file_name_max, brighness)) return 1; else
                printf("Reading %s gives: %s\n", driver_file_name_max, brighness);
            return 0;
        }

    // read option processed, now only writes are left
    fptr = fopen(driver_file_name,"w");
    if(fptr == NULL)
    {
        printf("Could not open %s for writing; are you sure you run as root? does system use Intel graphics driver?\n", driver_file_name);   
        return 1;        
    }

    const char *text_commands[] = {"max", "+1", "-1", 0};
    if (argc == 2)
    {
        int i = 0;
        while(text_commands[i]) {
            if(strcmp(text_commands[i], argv[1]) == 0) { 
                if (read(driver_file_name_max, max_brighness)) 
                {
                    fclose(fptr);
                    return 1;
                }

                if (!i) { // 0 
                    fprintf(fptr, "%s\n", max_brighness);
                    fclose(fptr);
                    return 0; 
                }
                // increment / decrement need more code 
                if (read(driver_file_name, brighness)) 
                {
                    fclose(fptr);
                    return 1;
                }

                int brighness_int = atof(brighness);
                if (!brighness_int) { // if 0 then just set min as log of 0 is not defined (changing from 1 to 0 should work by log code path)
                    fprintf(fptr, "%s\n", min_brighness);
                    fclose(fptr);
                    return 0; 
                }

                int max_brighness_int = atof(max_brighness);
                double brighness_scaled = scale_function(brighness_int);
                double max_brighness_scaled = scale_function(max_brighness_int);
                double min_brighness_scaled = scale_function(min_brighness_int); // should be 0 for brightness of 1, but for universality of code...
                double step_scaled = (max_brighness_scaled - min_brighness_scaled)/steps; 
                int new_brightness_int;

                switch (i)
                    {
                        case 1: // +1
                            new_brightness_int = ceil(inverse_scale_function(brighness_scaled + step_scaled)); // ceil() to round up, implicit conversion
                            break;
                        case 2: // -1
                            new_brightness_int = (int) inverse_scale_function(brighness_scaled - step_scaled); // round down by default
                        //default:
                    }

                if (new_brightness_int > max_brighness_int) fprintf(fptr, "%s\n", max_brighness); else
                    if (new_brightness_int < min_brighness_int) fprintf(fptr, "%s\n", "0"); else
                        fprintf(fptr, "%d\n", new_brightness_int);

                fclose(fptr);
                return 0;      
            }
            i++;
        }
        
        // processed text commands, now only numbers expected
        for (int i=0;i<strlen(argv[1]); i++)
            if (!isdigit(argv[1][i]))
                {
                    printf ("Entered parameter is not a natural number, use -h/--help for details\n");
                    fclose(fptr);
                    return 1; // exit(1) return from funcion - main(), not exit from the program;
                }
        fprintf(fptr, "%s\n", argv[1]);

    } else 
        fprintf(fptr, "%s\n", min_brighness);

    fclose(fptr);
    return 0;
} 


int read (const char *file_name, char * brighness)
{
    FILE *fptr;
    //printf("Here is the reading from %s\n", file_name);
    fptr = fopen(file_name,"r");
    if(fptr == NULL)
    {
        printf("Could not open %s for reading; does system use Intel graphics driver?\n", file_name);   
        return 1;
    } 
    int i;
    for (i=0; (brighness[i] = fgetc(fptr)) != EOF; i++);
    brighness[--i]=0; // overwrite EOF (which is undefined)
    fclose(fptr);
    return 0; 
}

double scale_function(int x)
{
    return log10((double)x);
}
double inverse_scale_function(double x)
{
    return pow(10,x);
}

