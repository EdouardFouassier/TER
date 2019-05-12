# MAKEFILE	= Makefile

# CC			= gcc
# CFLAGS		= -W -Wall -O3 -openmp -fopenmp
# LDFLAGS		= -lm
# TARGET      = TER
# CLEAN		= clean

# OBJECTS	=	TER.o \
# 			algoLourd.o \
# 			FirstFit.o \
# 			gen.o \
# 			bibli.o

# $(TARGET): $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# compile: Makefile $(TARGET)

# # debug:$(CLEAN) $(EXEC)
# # 		gdb ./TER 50000 35 1000 10

# # run:$(CLEAN) $(EXEC)
# # 	./TER 50000 35 1000 1

# # memoire:$(CLEAN) $(EXEC)
# # 		valgrind --leak-check=full --show-leak-kinds=all ./TER 50000 35 1000 1

# # analyse:$(CLEAN) $(EXEC)
# # 		valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./TER 50000 35 1000 10

# # script:	$(CLEAN) $(EXEC)
# # 		./TER 50000 35 1000 10
# # 		R CMD BATCH "draw.R"
# # 		cp Rplots.pdf GrosTry.pdf
# # 		rm Rplots.pdf
# # 		xdg-open GrosTry.pdf

# TER.o: 	TER.c TER.h \
# 		algoLourd.h	\
# 		FirstFit.h	\
# 		gen.h		\
# 		bibli.h 	
# 		$(CC) -c $(CFLAGS) $(LDFLAGS) -o TER.o TER.c 

# algoLourd.o: 	algoLourd.c algoLourd.h \
# 				bibli.h 
# 				$(CC) -c $(CFLAGS) $(LDFLAGS) -o algoLourd.o algoLourd.c

# FirstFit.o: FirstFit.c FirstFit.h \
# 			bibli.h
# 			$(CC) -c $(CFLAGS) $(LDFLAGS) -o FirstFit.o FirstFit.c 

# gen.o: 	gen.c gen.h
# 		$(CC) -c $(CFLAGS) $(LDFLAGS) -o gen.o gen.c

# bibli.o:	bibli.c bibli.h
# 			$(CC) -c $(CFLAGS) $(LDFLAGS) -o bibli.o bibli.c

# clean: 
# 	rm -f data/In*
# 	rm -f *.Rout
# 	# rm -r .RData
# 	rm -f *.data
# 	rm -f *.o


# run:
# 	./TER 50000 35 1000 1

MAKEFILE	= Makefile

CC			= gcc
CFLAGS		= -W -Wall -O3 -openmp -fopenmp
LDFLAGS		= -lm
EXEC      	= TER
CLEAN		= clean

debug:$(CLEAN) $(EXEC)
		gdb ./TER 50000 35 1000 10

run:$(CLEAN) $(EXEC)
	./TER 50000 35 1000 2

memoire:$(CLEAN) $(EXEC)
		valgrind --leak-check=full --show-leak-kinds=all ./TER 50000 35 1000 1

analyse:$(CLEAN) $(EXEC)
		valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes ./TER 50000 35 1000 10

script:	$(CLEAN) $(EXEC)
		./TER 50000 35 1000 100
		R CMD BATCH "draw.R"
		cp Rplots.pdf GrosTry.pdf
		rm Rplots.pdf
		xdg-open GrosTry.pdf
		R CMD BATCH "draw2.R"
		cp Rplots.pdf GrosTry2.pdf
		rm Rplots.pdf
		xdg-open GrosTry2.pdf
		R CMD BATCH "draw3.R"
		cp Rplots.pdf GrosTry3.pdf
		rm Rplots.pdf
		xdg-open GrosTry3.pdf

TER: bibli.o gen.o FirstFit.o algoLourd.o algoSuperLourd.o algoPasilourd.o TER.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

TER.o: bibli.h gen.h FirstFit.h algoLourd.h algoSuperLourd.h algoPasilourd.h

algoLourd.o: bibli.h 

FirstFit.o: bibli.h

algoSuperLourd.o: bibli.h 

algoPasilourd.o: bibli.h 

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean: 
	rm -f data/In*
	rm -f *.Rout
	# rm -r .RData
	rm -f *.data
	rm -f *.o
