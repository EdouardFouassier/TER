R CMD BATCH "draw.R"
cp Rplots.pdf GrosTry.pdf
rm Rplots.pdf
xdg-open GrosTry.pdf
R CMD BATCH "draw2.R"
cp Rplots.pdf GrosTry2.pdf
rm Rplots.pdf
#xdg-open GrosTry2.pdf
R CMD BATCH "draw3.R"
cp Rplots.pdf GrosTry3.pdf
rm Rplots.pdf
#xdg-open GrosTry3.pdf