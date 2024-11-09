PROGRAMS = main mainTIME

all : $(PROGRAMS)


mainTIME : mainTIME.o biblioLC.o entreeSortieLC.o 
	gcc -ggdb -o  mainTIME mainTIME.o biblioLC.o entreeSortieLC.o

main : main.o biblioLC.o entreeSortieLC.o 
	gcc -ggdb -o  main main.o biblioLC.o entreeSortieLC.o
 

main.o : main.c biblioLC.h entreeSortieLC.h
	gcc -c  main.c

mainTIME.o : mainTIME.c biblioLC.h entreeSortieLC.h
	gcc -c  mainTIME.c


biblioLC.o : biblioLC.c biblioLC.h
	gcc -c  biblioLC.c

entreeSortieLC.o : entreeSortieLC.c biblioLC.h entreeSortieLC.h
	gcc -c  entreeSortieLC.c


clean : 
	rm -f *.o main 
