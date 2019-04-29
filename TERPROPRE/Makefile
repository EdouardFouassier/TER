MAKEFILE	= Makefile

CC			= gcc
CFLAGS		= -W -Wall
LDFLAGS		= -lm -O3 -openmp -fopenmp
EXEC		= TER
CLEAN		= clean

debug:$(CLEAN) $(EXEC)
		gdb ./TER 50000 35 1000 10

run:$(CLEAN) $(EXEC)
	./TER 50000 35 1000 1

memoire:$(CLEAN) $(EXEC)
		valgrind --leak-check=full --show-leak-kinds=all ./TER 50000 35 1000 1

analyse:$(CLEAN) $(EXEC)
		valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./TER 50000 35 1000 10

script:	$(CLEAN) $(EXEC)
		./TER 50000 35 1000 10
		R CMD BATCH "draw.R"
		cp Rplots.pdf GrosTry.pdf
		rm Rplots.pdf
		xdg-open GrosTry.pdf

TER: bibli.o gen.o FirstFit.o algoLourd.o TER.o
	$(CC)  $^ $(LDFLAGS) -o $@

TER.o: bibli.h gen.h FirstFit.h algoLourd.h

algoLourd.o: bibli.h 

FirstFit.o: bibli.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -f data/In*
	rm -f *.Rout
	# rm -r .RData
	rm -f *.data
	rm -f *.o