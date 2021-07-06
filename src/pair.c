/*
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 22:49:52 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_fit.h>
#include "vector.h"

double two_tails_p(double p)
{
     if (p < 0.5)
          return 2 * p;
     else
          return 2 * (1 - p);
}

int main(int argc, char *argv[])
{
     vector a, b, diff;
     init_vector(&a, 128);
     init_vector(&b, 128);
     init_vector(&diff, 128);

     char* line = NULL;
     size_t len = 0;
     ssize_t nread;
     int n = 0;

     const char *DELIMITERS = ",/:;|\t\n\r ";
     while ((nread = getline(&line, &len, stdin)) != -1) {
          double col1 = 0.0, col2 = 0.0;

          char* token = strtok(line, DELIMITERS);
          if (token != NULL)
               col1 = atof(token);
          token = strtok(NULL, DELIMITERS);
          if (token != NULL)
               col2 = atof(token);
          else {  // single number on the line
               col2 = col1;
               col1 = ++n;
          }
          push_back_vector(&a, col1);
          push_back_vector(&b, col2);
          push_back_vector(&diff, col2 - col1);
     }

     n = a.size;

     double mean_a = gsl_stats_mean(a.data, 1, n);
     double mean_b = gsl_stats_mean(b.data, 1, n);
     double mean_diff = gsl_stats_mean(diff.data, 1, n);
     double sd_a = gsl_stats_sd(a.data, 1, n);
     double sd_b = gsl_stats_sd(b.data, 1, n);
     double sd_diff = gsl_stats_sd(diff.data, 1, n);

     int df = n - 1;
     double t_a = mean_a / (sd_a / sqrt(n));
     double t_b = mean_b / (sd_b / sqrt(n));
     double t_diff = mean_diff / (sd_diff / sqrt(n));

     double p_a = two_tails_p(gsl_cdf_tdist_Q(t_a, df));
     double p_b = two_tails_p(gsl_cdf_tdist_Q(t_b, df));
     double p_diff = two_tails_p(gsl_cdf_tdist_Q(t_diff, df));

     double cor = gsl_stats_correlation(a.data, 1, b.data, 1, n);
     int df_cor = n - 2;
     double t_cor = cor / sqrt((1.0 - cor * cor) / df_cor);
     double p_cor = two_tails_p(gsl_cdf_tdist_Q(t_cor, df_cor));

     double c0, c1, cov00, cov01, cov11, sumsq;
     gsl_fit_linear(a.data, 1, b.data, 1, n, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);

     printf("Analysis for %d points:\n", n);
     printf("                   Column1            Column2           Difference\n");
     printf("Means     %16.4f   %16.4f  %16.4f\n", mean_a, mean_b, mean_diff);
     printf("SDs       %16.4f   %16.4f  %16.4f\n", sd_a, sd_b, sd_diff);
     printf("t(%d)     %16.4f   %16.4f  %16.4f\n", df, t_a, t_b, t_diff);
     printf("p         %16.4g   %16.4g  %16.4g\n", p_a, p_b, p_diff);
     printf("\n");
     printf("\n     Correlation         r-squared          t(%d)              p\n", df_cor);
     printf("%16.4f %16.4f %16.4f %16.4f\n", cor, cor*cor, t_cor, p_cor);
     printf("       Intercept         Slope\n");
     printf("%16.4f %16.4f\n", c0, c1);

     free_vector(a);
     free_vector(b);
     free_vector(diff);
}
