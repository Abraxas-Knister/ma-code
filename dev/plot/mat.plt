#!/usr/bin/env gnuplot
set term png enh size 1000 , 1000
set key above
set out "mat-gf.png"
set multiplot layout 2,2
set auto
pl "../data/mat-gf" u 1:2 w lp t "time real"
set auto
pl "../data/mat-gf" u 1:3 w lp t "time imag"
set auto
pl "../data/mat-gf" u 4:5 w lp t "freq real"
set auto
pl "../data/mat-gf" u 4:6 w lp t "freq imag"
unset multiplot

set out "mat-gf-converg.png"
set log y
set auto
pl "../data/mat-converg"  w lp t "hybridisation"
