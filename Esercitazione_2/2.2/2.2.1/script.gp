
f(x)=k*sqrt(x)
fit [0:100] f(x) 'Vettore_media.dat' using 1:2 via k
plot 'Vettore_media.dat' using 1:2:3 with yerr pt 9, f(x) with lines lw 2
