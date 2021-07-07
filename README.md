# statsutils

*statsutils* is a suite of command-line tools to perform simple statistical data
manipulations and analyses from data stored in text files.

The programs that can currently be built with this package are:

| name      | purpose                                                 | progress |
| -----     | ---------                                               | -------- |
| runif     | generate random numbers uniformly on [0, 1)             |     100% |
| rnorm     | generate random numbers following a normal distribution |     100% |
| hist      | create an histogram                                     |      50% |
| stats     | basic descriptive statistics                            |      90% |
| pair      | compare two paired variables                            |      90% |
| maketrix  | format text file into columns                           |     100% |
| transpose | transpose a matrix                                      |      80% |


Examples:

```
$ rnorm -m 10 -s 3 30  | stats
n=30
min=4.208317
max=14.964540
median=9.248378
mean=10.035583
sd=3.033801
absdev=2.535955
mad=3.137011
skew=0.214240
kurtosis=-1.120684
conf_int_95_inf=8.902743
conf_int_95_sup=11.168423

$ rnorm 200 | hist
-2.22    3 ***
-1.68   12 ************
-1.14   21 *********************
-0.61   36 ************************************
-0.07   48 ************************************************
 0.47   39 ***************************************
 1.01   26 **************************
 1.55    9 *********
 2.09    3 ***
 2.62    2 **
  
$ rnorm -m 10 -s 3 30  | maketrix 2 | pair
Analysis for 15 points:
                   Column1            Column2           Difference
Means              11.1890            10.5444           -0.6446
SDs                 3.1579             2.8622            4.1277
t(14)              13.7228            14.2683           -0.6048
p                1.642e-09          9.845e-10             0.555

Correlation         r-squared            t(13)                p
     0.0623            0.0039           0.2251           0.8254
  Intercept             Slope
     9.9126            0.0565

```

Note that this is a **work in progress**. More tools are planned (suggestions
and contributions are welcome!)


## A predecessor: |STAT 

This package takes inspiration from [`|STAT`](https://garyperlman.com/stat/).

`|STAT` embodies the *Unix philosophy* according to which each program does one
thing and does it well ("To do a new job, build afresh rather than complicate
old programs by adding new "features". Expect the output of every program to
become the input to another, as yet unknown, program."
[wikipedia](https://en.wikipedia.org/wiki/Unix_philosophy))

It heavily relies on the piping concept of unix. In the words of `|STAT`'s
author:

> An analysis consists of an extraction of data, optional transformations, and
> some analysis. Pictorially, this can be shown as:
>
>   data | extract | transform | format | analysis | results
>
> where a copy a subset of the data has been extracted, transformed, reformatted,
> and analyzed by chaining several programs. Data manipulation functions,
> sometimes built into analysis programs in other packages, are distinct programs
> in |STAT. The use of pipelines, signaled with the pipe symbol, |, is the reason
> for the name |STAT.

See <https://garyperlman.com/stat/example.html> for some examples of usage.

[Gary Perlman](https://garyperlman.com), the author, wrote a very fine
[handbook](https://garyperlman.com/stat/handbook/handbook.html), which is quite
readable by newbies.

The original code can be obtained by contacting the author, [Gary
Perlman](https://garyperlman.com). It still compiles, yet, written in C in the
80s (predating C89), the code has a few weaknesses, notably the use of many
hard-coded limits; the `indent` does not manage to parse it because of macros,
and gcc spits many warnings (e.g. about the use of the dangerous function
`gets`).

## Why command line statistical tools are still useful

Before the advent of [`R`](https://www.r-project.org/), I used to perform most
of my data analyses using `|STAT`, in conjunction with
[`AWK`](https://en.wikipedia.org/wiki/AWK) and
[`gnuplot`](http://www.gnuplot.info/) (and yes, it is possible to [produce
good-looking graphics with
gnuplot](https://www.electricmonk.nl/log/2014/07/12/generating-good-looking-charts-with-gnuplot/)).

I believe there is still a use case for some of such tools: "quick and dirty""
data exploration from the command line, saving the need to launch `R`.


## Original |STAT Programs ##

The original suite features the following tools:

### Data Manipulation ###
 
| name      | purpose                                    |
| --------- | ------------------------------------------ |
| abut      | join data files beside each other          |
| colex     | column extraction/formatting               |
| dm        | conditional data extraction/transformation |
| dsort     | multiple key data sorting filter           |
| linex     | line extraction                            |
| maketrix  | make matrix format from free-format input  |
| perm      | random/numerical/alphabetical permutation  |
| probdist  | probability distribution functions         |
| ranksort  | convert data to ranks                      |
| repeat    | repeat strings or lines in files           |
| reverse   | reverse lines, columns, or characters      |
| series    | generate an additive series of numbers     |
| transpose | transpose matrix format input              |
| validata  | verify data file consistency               |


### Data Analysis ###


| name      | purpose                                    |
| --------- | ------------------------------------------ |
| anova     | multi-factor analysis of variance, plots   |
| calc      | interactive algebraic modeling calculator  |
| contab    | contingency tables and chi-square          |
| desc      | descriptions, histograms, frequency tables |
| dprime    | signal detection d' and beta calculations  |
| features  | tabulate features of items                 |
| oneway    | one-way anova/t-test, error-bar plots      |
| pair      | paired data statistics, regression, plots  |
| rankind   | independent conditions rank order analysis |
| rankrel   | related conditions rank order analysis     |
| regress   | multiple linear regression and correlation |
| stats     | simple summary statistics                  |
| ts        | time series analysis, plots                |
  

### Replacements ### 
  
 Some tools already have good replacements: 
  
 *  `abut`, `colex`, `series` and `perm` can be replaced by `paste`, `cut`, `seq` and `shuf` from [GNU's coreutils](https://www.gnu.org/software/coreutils/manual/coreutils.html) 
  
 * `dm`, `linex` can be replaced by the more powerful `awk` (e.g., [GNU Awk](https://www.gnu.org/software/gawk/manual/gawk.html)) 
  
 * `calc` can be replaced by [calc](http://www.isthe.com/chongo/tech/comp/calc/) 
  
 
## Current project 

 We do not aim for an exact replacement: we can also seek inspiration from R
 names and outputs when clearer.

 We start from scratch, so as not to infringe the Copyright of Gary Perlman.

 Ideally, one day, the very fine handbook of Gary Perlman could be modified to
 reflect the new tools, but the license forbids it.

## Compiling statsutils

If you do not already have a C compiler and the `make` tool, you need to install
them. Under Debian/Ubuntu, this is achieved with the command `sudo apt install
build-essential`

Some programs rely on functions from the GNU Scientific Library (GSL). You must
therefore install the headers and libraties. Under Ubuntu, this is achieved with
`sudo apt install libgsl-dev`.

To compile the programs and do a system-wide install, run:

    ./configure --prefix
    make
    sudo make install

To install only for the current user, run:

    ./configure --prefix=$HOME
    make
    make install

Check out the file `INSTALL` for detailed instructions.


## License

The code is distributed under the GNU Public License v.3 (see LICENSE file in
this folder)

## Authors

- Christophe Pallier <christophe@pallier.org>


(Looking for Contributors to add to the list!)
