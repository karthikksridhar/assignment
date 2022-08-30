CC = g++
CFLAGS = -c -Wall

all : concordance_test

concordance_test: concordance_test.cpp
	$(CC) -o concordance_test concordance_test.cpp

clean:
	rm concordance_test  
