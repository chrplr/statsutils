/* Generate random numbers from the uniform distrbution on [0, 1)
 *
 * See https://www.gnu.org/software/gsl/doc/html/rng.html
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 18:29:54 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdio.h>
#include <argp.h>
#include <gsl/gsl_rng.h>
#include "getns.h"

static char doc[] = "Generate random numbers in the interval [0,1) using GNU Scientific Library's Tausworthe generator.";
const char* argp_program_version = "1.0";

const char* argp_program_bug_address = "<christophe@pallier.org>";

struct arguments {
     int n_samples;
     long int seed;
};

static char args_doc[] ="[number_of_samples]";

static struct argp_option options[] = {
        {"seed", 'S', "SEED", 0, "seed for the random number generator"},
        {0}
};

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        struct arguments* arguments = state->input;

        switch (key) {
        case 'S':
                arguments->seed = atol(arg);
                break;
        case ARGP_KEY_ARG:
             if (state->arg_num >= 2)
                  argp_usage (state);

             arguments->n_samples = atoi(arg);
             break;
        default:
                return ARGP_ERR_UNKNOWN;
        }
        return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };


int main(int argc, char *argv[])
{
     struct arguments args;
     args.seed = getns();
     args.n_samples = 1;
     argp_parse(&argp, argc, argv, 0, 0, &args);

     gsl_rng *r = gsl_rng_alloc (gsl_rng_taus);
     gsl_rng_set(r, args.seed);

     for (uint i = 0; i < args.n_samples; i++)
          printf("%f ", gsl_rng_uniform(r));
     printf("\n");

     gsl_rng_free(r);
}
