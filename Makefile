CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = test1 main2 main3 test56 main7 analyse_7 election

.PHONY: all clean

all: $(PROGRAMS)
	 

test1: test1.o exercice1.o 
	$(CC) -o $@ $(CFLAGS) $^

main2: main2.o exercice1.o exercice2.o
	$(CC) -o $@ $(CFLAGS) $^

main3: main3.o  exercice1.o exercice2.o exercice3.o exercice4.o
	$(CC) -o $@ $(CFLAGS) $^

test56: test56.o  exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o  
	$(CC) -o $@ $(CFLAGS) $^ 

main7: main7.o  exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o
	$(CC) -o $@ $(CFLAGS)  $^ -lssl -lcrypto
	
analyse_7: analyse_7.o  exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o 
	$(CC) -o $@ $(CFLAGS)  $^ -lssl -lcrypto
	
election: election.o  exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o exercice9.o
	$(CC) -o $@ $(CFLAGS)  $^ -lssl -lcrypto
	
test1.o: test1.c
	gcc -c $(CFLAGS) test1.c

main2.o: main2.c
	gcc -c $(CFLAGS) main2.c

main3.o: main3.c
	gcc -c $(CFLAGS) main3.c

test56.o: test56.c
	gcc -c $(CFLAGS) test56.c
	

main7.o: main7.c
	gcc -c $(CFLAGS) main7.c -lssl -lcrypto

analyse_7.o: analyse_7.c
	gcc -c $(CFLAGS) analyse_7.c -lssl -lcrypto
	
election.o: election.c
	gcc -c $(CFLAGS) election.c -lssl -lcrypto
	
clean:
	rm -f *.o *~ $(PROGRAMS)
