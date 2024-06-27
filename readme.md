# shapeon
A time series analysis method.

## Description
Converts a set of labelled time series into features that best discriminate them. An example feature is minimum distance to a sub-series.

How well a feature discriminates the set of labelled time series is the calculated as the Fischer Linear Discriminant for multiple classes.

## Experiment
Is set up to run with the UCR Time Series Classification Archive, found [here](https://www.cs.ucr.edu/~eamonn/time_series_data_2018/).

## Building
To build the executable, simply run the following:
```
make build
```
> [!NOTE]
> Has only been tested on linux.

## Tests
To run tests, simply run the following:
```
make test
```
> [!IMPORTANT]
> The tests require [Criterion](https://github.com/Snaipe/Criterion). As such, it is required to be installed on the system. This is not automatic.

Example Output
```
gcc -Isrc -g -O3 -Wall -Wextra -flto -std=c17 -march=native -fsanitize=address -D LOG_DEBUG -O0 -o test_runner
 tests/*.c src/parse.o src/window.o src/io.o src/feature.o src/log.o src/analysis.o src/preprocessing.o -lcrit
erion -lm
./test_runner
[                 analysis.equal_scatter            ] [ 0,000391 s ] [   OK   ]
...
[                 windower.single                   ] [ 0,000113 s ] [   OK   ]
[====] Synthesis: Tested: 23 | Passing: 23 | Failing: 0 | Crashing: 0
```
