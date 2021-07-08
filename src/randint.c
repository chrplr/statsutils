/* Generate random integers from the discrete uniform distribution in the interval [low, high].
 *
 * See https://www.gnu.org/software/gsl/doc/html/rng.html
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-08 09:16:51 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdio.h>
#include <argp.h>
#include <gsl/gsl_randist.h>
#include <assert.h>
#include "getns.h"

static char doc[] = "Generate random integers from the discrete uniform distribution in the interval [low, high]";
const char* argp_program_version = "1.0";

const char* argp_program_bug_address = "<christophe@pallier.org>";

struct arguments {
     uint n_samples;
     long int seed;
     long int low;
     long int high;
};

static char args_doc[] ="[number_of_samples]";

static struct argp_option options[] = {
        {"seed", 'S', "SEED", 0, "seed for the random number generator"},
        {"low", 'l', "inf", 0, "lowest (signed) integer to be drawn from the distribution"},
        {"high", 'h', "sup", 0, "highest (signed) integer to be drawn from the distribution"},
        {0}
};

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        struct arguments* arguments = state->input;

        switch (key) {
        case 'S':
                arguments->seed = atol(arg);
                break;
        case 'l':
             arguments->low = atol(arg);
             break;
        case 'h':
             arguments->high = atol(arg);
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
     args.low = 0;
     args.high = 1;

     argp_parse(&argp, argc, argv, 0, 0, &args);

     assert(args.high > args.low);

     gsl_rng *r = gsl_rng_alloc (gsl_rng_taus);
     gsl_rng_set(r, args.seed);

     long range = args.high - args.low + 1;
     for (uint i = 0; i < args.n_samples; i++)
             printf("%ld%c", args.low + (gsl_rng_get(r) % range), i < (args.n_samples - 1)? ' ': '\n');

     gsl_rng_free(r);
}
