/* print basic descriptive statistics 
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 17:21:35 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_cdf.h>

#include "vector.h"

int main()
{
        vector v;

        init_vector(&v, 256);

        read_vector(&v, stdin);
        int n = v.size;
        //printf("%zu items read: ", n);
        //print_vector(v, "%.1f", ", ");

        double min, max;
        gsl_stats_minmax(&min, &max, v.data, 1, n);
        double mean = gsl_stats_mean(v.data, 1, n);
        double median = gsl_stats_median(v.data, 1, n);

        printf("n=%d\n", n);
        printf("min=%f\n", min);
        printf("max=%f\n", max);
        printf("median=%f\n", median);
        printf("mean=%f\n", mean);

        if (n > 1) {
                double sd = gsl_stats_sd_m(v.data, 1, n, mean);
                double se = sd / sqrt(n);
                double skew = gsl_stats_skew_m_sd(v.data, 1, n, mean, sd);
                double kurtosis = gsl_stats_kurtosis_m_sd(v.data, 1, n, mean, sd);
                double absdev = gsl_stats_absdev_m(v.data, 1, n, mean);
                double work[n];
                double mad = gsl_stats_mad(v.data, 1, n, work);
                double t_95 = gsl_cdf_tdist_Pinv(.975, n - 1);
                double conf_int_95_inf = mean - se * t_95;
                double conf_int_95_sup = mean + se * t_95;
                printf("sd=%f\n", sd);
                printf("absdev=%f\n", absdev);
                printf("mad=%f\n", mad);
                printf("skew=%f\n", skew);
                printf("kurtosis=%f\n", kurtosis);
                printf("conf_int_95_inf=%f\n", conf_int_95_inf);
                printf("conf_int_95_sup=%f\n", conf_int_95_sup);
        }

        free_vector(v);
}
