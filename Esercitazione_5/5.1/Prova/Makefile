CC = g++
CFLAGS = -O3 --std=c++11

main.exe : main.o random.o metropolis.o
	$(CC) random.o main.o metropolis.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
metropolis.o : metropolis.cpp metropolis.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)




clean :
	rm *.o main.exe seed.out
