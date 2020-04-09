#!/usr/bin/env gnuplot
set term post eps enh color size 14cm, 8cm
set key above

# matrix computed greens function
file="../data/mat-gf"

set out "mat-gf-freq.eps"
pl \
file u 4:5  w l t "real" ,\
file u 4:6  w l t "imag" 

set yr [-1.1:1.1]
set format y
set format y2 "%h"
set ytics nomirror
set y2tics nomirror
set ylabel "imag"
set y2label "real"
set out "mat-gf-time.eps"
pl \
file u 1:2  w l t "real" ax x1y2,\
file u 1:3  w l t "imag" 
set format y2 ''
set auto
set y2label ''
set y2tics ()

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
set ylabel "|(V-V_{fin})/V_{fin}| pow of 10"

set label at screen .1,.3 left sprintf("V_{fin}: %f",V)
pl file u (abs(($1-V)/V)) w lp t "hybridisation"
