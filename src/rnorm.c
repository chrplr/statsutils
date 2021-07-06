/* Generate random numbers following a normal distribution. 
 *
 * See https://www.gnu.org/software/gsl/doc/html/rng.html
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 18:30:57 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdio.h>
#include <argp.h>
#include <gsl/gsl_randist.h>
#include "getns.h"

static char doc[] = "Generate random numbers following a normal distribution.";
const char* argp_program_version = "1.0";

const char* argp_program_bug_address = "<christophe@pallier.org>";

struct arguments {
     int n_samples;
     long int seed;
     double mean;
     double sd;
};

static char args_doc[] ="[number_of_samples]";

static struct argp_option options[] = {
        {"seed", 'S', "SEED", 0, "seed for the random number generator"},
        {"mean", 'm', "mean", 0, "mean of the normal distribution"},
        {"sd", 's', "stddev", 0, "standard deviation of the normal distribution"},
        {0}
};

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        struct arguments* arguments = state->input;

        switch (key) {
        case 'S':
                arguments->seed = atol(arg);
                break;
        case 'm':
             arguments->mean = atol(arg);
             break;
        case 's':
             arguments->sd = atol(arg);
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
     args.mean = 0.0;
     args.sd = 1.0;

     argp_parse(&argp, argc, argv, 0, 0, &args);

     gsl_rng *r = gsl_rng_alloc (gsl_rng_taus);
     gsl_rng_set(r, args.seed);

     for (uint i = 0; i < args.n_samples; i++)
          printf("%f ", args.mean + gsl_ran_gaussian(r, args.sd));

     printf("\n");

     gsl_rng_free(r);
}
