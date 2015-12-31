#Compiles compute, C version wo BOINC API.

PROGRAM=compute
CC=gcc
matrix_size=4000
tile_size=4000
version=version2
CFLAGS=-D matrix_size=$(matrix_size) -D $(version) -D b=$(tile_size)
OFLAG= 

default: clean $(PROGRAM)

clean:
	rm -f $(PROGRAM)

$(PROGRAM): $(PROGRAM).c
	$(CC) $(CFLAGS) $(OFLAG) $(PROGRAM).c -o $(PROGRAM) -lm
	
	
