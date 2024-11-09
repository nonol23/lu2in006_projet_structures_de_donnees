PROGRAMS = mainH mainTIME

all : $(PROGRAMS)

mainTIME : mainTIME.o biblioH.o entreeSortieH.o
	gcc -ggdb -o  mainTIME mainTIME.o biblioH.o entreeSortieH.o

mainH : mainH.o biblioH.o entreeSortieH.o
	gcc -ggdb -o  mainH mainH.o biblioH.o entreeSortieH.o

mainTIME.o : mainTIME.c biblioH.h entreeSortieH.h
	gcc -c  mainTIME.c

mainH.o : mainH.c biblioH.h entreeSortieH.h
	gcc -c  mainH.c

entreeSortieH.o : entreeSortieH.c biblioH.h entreeSortieH.h
	gcc -c  entreeSortieH.c

biblioH.o : biblioH.c biblioH.h
	gcc -c  biblioH.c

clean : 
	rm -f *.o main 
