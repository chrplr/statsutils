/*
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 18:18:31 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdio.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_histogram.h>
#include "vector.h"

int main(int argc, char *argv[])
{
     vector v;
     init_vector(&v, 128);
     read_vector(&v, stdin);

     double xmin, xmax;
     gsl_stats_minmax(&xmin, &xmax, v.data, 1, v.size);

     int nbins = 10;
     gsl_histogram *hist=gsl_histogram_alloc(nbins);
     gsl_histogram_set_ranges_uniform(hist, xmin, xmax);

     for (uint i = 0; i < v.size; i++)
          gsl_histogram_increment(hist, v.data[i]);

     double max_pop = gsl_histogram_max_val(hist);
     double scale = (max_pop < 80)? 1 : (80 / max_pop); 

     for (uint i= 0; i<nbins; i++) {
          printf("%5.2f %4.0f ", (hist->range[i] + hist->range[i+1]) / 2, hist->bin[i]);
          printf("%.*s\n", (int)(hist->bin[i] * scale), "********************************************************************************");
     }


}
