PROGRAM1=matrix
PROGRAM2=distribute
CC=gcc
matrix_size=4000
tile_size=1000
version=version2
CFLAGS=-D matrix_size=$(matrix_size) -D $(version) -D b=$(tile_size)
OFLAG= 

default: clean $(PROGRAM1) $(PROGRAM2)

clean:
	rm -f $(PROGRAM1) $(PROGRAM2)

$(PROGRAM1): $(PROGRAM1).c
	$(CC) $(CFLAGS) $(OFLAG) $(PROGRAM1).c -o $(PROGRAM1) -lm

$(PROGRAM2): $(PROGRAM2).c
	$(CC) $(CFLAGS) $(OFLAG) $(PROGRAM2).c -o $(PROGRAM2) -lm
	
	
