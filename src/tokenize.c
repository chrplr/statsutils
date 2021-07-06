/* tokenize a text file
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 13:04:18 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <search.h>


const char* DELIMITERS = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~\\\t\n\r ";

int main(int argc, char* argv[])
{
        FILE* fd;
        char* line = NULL;
        size_t len = 0;
        ssize_t nread;

        fd = (argc > 1)? fopen(argv[1],"r") : stdin;
        if (!fd)
        {
                perror(argv[1]);
                return EXIT_FAILURE;
        }

        while ((nread = getline(&line, &len, fd)) != -1) {
                char* token = strtok(line, DELIMITERS);
                while (token != NULL) {
                        puts(token);
                        token = strtok(NULL, DELIMITERS);
                }
        }

        free(line);
}
