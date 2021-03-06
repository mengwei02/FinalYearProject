##########################################################################################
###                                                                                    ###
###   Plot Mean, Variance, Skewness of Correlation Coefficients with 10 day rollover   ###
###                                                                                    ###
##########################################################################################

reset

# produce postscript (.ps) output plot
set term postscript eps enhanced color size 7,5
set output "distributionCorrelationCoefficientsRollover_10.eps"

# x-axis data is time with format specified
set xdata time
set timefmt "%Y-%m-%d"
set format x "%Y"

# style for T = 100 time window length
set style line 1 lc rgb '#0b24fb' lt 1 lw 1.5 ps 1.5

# style for T = 150 time window length
set style line 2 lc rgb '#FF0000' lt 1 lw 1.5 ps 1.5

# style for T = 200 time window length
set style line 3 lc rgb '#000000' lt 1 lw 1.5 ps 1.5

set multiplot layout 3,1 

set key outside center bottom horizontal font "sans-serif, 18"

set xlabel "Time (year)"
set ylabel "Mean"
plot 'meanCorrelationCoefficientsRollover_10.dat' using 1:2 notitle with lines ls 1, 'meanCorrelationCoefficientsRollover_10.dat' using 3:4 notitle with lines ls 2, 'meanCorrelationCoefficientsRollover_10.dat' using 5:6 notitle with lines ls 3

set xlabel "Time (year)"
set ylabel "Variance"
plot 'varianceCorrelationCoefficientsRollover_10.dat' using 1:2 notitle with lines ls 1, 'varianceCorrelationCoefficientsRollover_10.dat' using 3:4 notitle with lines ls 2, 'varianceCorrelationCoefficientsRollover_10.dat' using 5:6 notitle with lines ls 3

set xlabel "Time (year)"
set ylabel "Skewness"
plot 'skewnessCorrelationCoefficientsRollover_10.dat' using 1:2 title 'T=100' with lines ls 1, 'skewnessCorrelationCoefficientsRollover_10.dat' using 3:4 title 'T=150' with lines ls 2, 'skewnessCorrelationCoefficientsRollover_10.dat' using 5:6 title 'T=200' with lines ls 3

unset multiplot


##########################################################################################
###                                                                                    ###
###   Plot Mean, Variance, Skewness of Correlation Coefficients with 1 day rollover    ###
###                                                                                    ###
##########################################################################################

reset

# produce postscript (.ps) output plot
set term postscript eps enhanced color size 7,5
set output "distributionCorrelationCoefficientsRollover_1.eps"

# x-axis data is time with format specified
set xdata time
set timefmt "%Y-%m-%d"
set format x "%Y"

# style for T = 100 time window length
set style line 1 lc rgb '#0b24fb' lt 1 lw 1.5 ps 1.5

# style for T = 150 time window length
set style line 2 lc rgb '#FF0000' lt 1 lw 1.5 ps 1.5

# style for T = 200 time window length
set style line 3 lc rgb '#000000' lt 1 lw 1.5 ps 1.5

set multiplot layout 3,1

set key outside center bottom horizontal font "sans-serif, 18"

set xlabel "Time (year)"
set ylabel "Mean"
plot 'meanCorrelationCoefficientsRollover_1.dat' using 1:2 notitle with lines ls 1, 'meanCorrelationCoefficientsRollover_1.dat' using 3:4 notitle with lines ls 2, 'meanCorrelationCoefficientsRollover_1.dat' using 5:6 notitle with lines ls 3

set xlabel "Time (year)"
set ylabel "Variance"
plot 'varianceCorrelationCoefficientsRollover_1.dat' using 1:2 notitle with lines ls 1, 'varianceCorrelationCoefficientsRollover_1.dat' using 3:4 notitle with lines ls 2, 'varianceCorrelationCoefficientsRollover_1.dat' using 5:6 notitle with lines ls 3

set xlabel "Time (year)"
set ylabel "Skewness"
plot 'skewnessCorrelationCoefficientsRollover_1.dat' using 1:2 title 'T=100' with lines ls 1, 'skewnessCorrelationCoefficientsRollover_1.dat' using 3:4 title 'T=150' with lines ls 2, 'skewnessCorrelationCoefficientsRollover_1.dat' using 5:6 title 'T=200' with lines ls 3

unset multiplot
