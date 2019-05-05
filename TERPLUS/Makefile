make:
	gcc TER.c FirstFit.c algoLourd.c gen.c bibli.c -lm -O3 -openmp -fopenmp -o TER

clean:
	rm -f data/in*
	rm -f *.Rout

debug:
	make clean
	make
	gdb ./TER 50000 35 1000 10

run:
	make clean
	make
	./TER 50000 35 1000 1


memoire:
	make clean
	make
	valgrind --leak-check=full --show-leak-kinds=all ./TER 50000 35 1000 1

analyse:
	make clean
	make
	valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./TER 50000 35 1000 10

script:
	make clean
	make
	./TER 50000 35 1000 10
	R CMD BATCH "draw.R"
	cp Rplots.pdf GrosTry.pdf
	rm Rplots.pdf
	xdg-open GrosTry.pdf
