/* maketrix reads strings separated by white space (spaces, tabs, and newlines) from the standard input and prints ncols of them per line to the standard output until the input is exhausted. (inspired from Gary Perlman |STAT) */
/* Time-stamp: <2021-07-06 13:51:10 christophe@pallier.org> */
/* Copyright Christophe Pallier 2021
   LICENSE: GNU GPL v3 <https://www.gnu.org/licenses/gpl-3.0.html>
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <argp.h>

static char doc[] = "Tokenize input and print tokens in columns. E.g. `seq 1 10 | maketrix 2`";
const char* argp_program_version = "1.0";

const char* argp_program_bug_address = "<christophe@pallier.org>";

struct arguments {
     int ncols;
};

static char args_doc[] ="ncols";

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        struct arguments* arguments = state->input;

        switch (key) {
        case ARGP_KEY_ARG:
             if (state->arg_num >= 2)
                  argp_usage (state);

             arguments->ncols = atoi(arg);
             break;
        default:
                return ARGP_ERR_UNKNOWN;
        }
        return 0;
}

static struct argp argp = { NULL, parse_opt, args_doc, doc };


int main(int argc, char *argv[])
{
     struct arguments args;
     args.ncols = 1;
     argp_parse(&argp, argc, argv, 0, 0, &args);

     int ncols = args.ncols;
     int col = 0;

     char* line = NULL;
     size_t len = 0;
     ssize_t nread;

     const char *DELIMITERS = " ,:;|\t\r\n";

     // The only argument is an int, the number of columns in the output
     if (argc != 2) {
          fprintf(stderr, "maketrix: Missing the number of columns as argument");
          exit(1);
     }

     ncols = atoi(argv[1]);

     while ((nread = getline(&line, &len, stdin)) != -1) {
          char* token = strtok(line, DELIMITERS);
          while (token != NULL) {
               printf("%s", token);
               if (0 == ++col % ncols)
                    printf("\n");
               else
                    printf(" ");
               token = strtok(NULL, DELIMITERS);
          }
     }

     if (col % ncols)
          printf("\n");

     free(line);
}
