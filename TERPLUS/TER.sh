
rm -f data/in*
make
./TER 50000 35 1000 100
R CMD BATCH "draw.R"
cp Rplots.pdf GrosTry.pdf
rm Rplots.pdf
xdg-open GrosTry.pdf
