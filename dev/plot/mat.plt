#!/usr/bin/env gnuplot
set term post eps enh color size 14cm, 8cm
set key off

# matrix computed greens function
file="../data/mat-gf"
set out "mat-gf.eps"
set multiplot

# bottom left: timedep real part
set format x
set format y
set xtics mirror .01
set ytics nomirror 2e-13
set yr [-1e-12:-1e-15]

set lmargin at screen .15
set bmargin -1
set tmargin at screen .5
set rmargin at screen .5

set label 1 at graph .1,.2 "time, real"
pl file u 1:2 ev 10 w l t "time real"

# top left: timedep imag part
set format x '' 
set ytics 2e-4
set yr [-1-1e-4:-1+8e-4]

set tmargin -1
set bmargin at screen .5

set label 1 at graph .1,.9 "time, imag"
pl file u 1:3 ev 10 w l t "time imag"

# bottom right: freqdep real part
set format x
set xtics 5e12
set xr [-12e12:12e12]
set format y ''
set ytics ()
set format y2
set y2tics nomirror 5e-3
set y2r [-1e-2:12e-3]

set rmargin at screen .85
set lmargin at screen .5
set bmargin -1
set tmargin at screen .5

set label 1 at graph .1,.9 "freq, real"
pl file u 4:5  ev 10 ax x1y2 w l t "freq real"

# top right: freqdep imag part
set format x '' 
set y2tics 1e-5
set y2r [-34e-5:-3e-4]

set bmargin at screen .5
set tmargin -1

set label 1 at graph .1,.9 "freq, imag"
pl file u 4:6 ev 10 ax x1y2 w l t "freq imag"

unset multiplot

# restore normal settings
set margins -1,-1,-1,-1
set label 1 ''
set format y2 ''
set y2tics ()
set auto
set format x
set format y
set xtics auto
set ytics auto

# convergence plot of the bath parameter
set out "mat-gf-converg.eps"
file="../data/mat-converg"
# computing final parameter
set table $NULL
V = 0.0
pl file u (V=$1)
unset table
undefine $NULL

set xlabel "iteration"
set log y
set format y "%L"
set ylabel "|V-V_{final}| pow of 10"

set label at screen .9,.9 right sprintf("V: %f",V)
pl file u (abs($1-V)) w lp t "hybridisation"
