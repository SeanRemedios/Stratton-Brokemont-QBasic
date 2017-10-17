CFLAGS = -Wall

# All .c files in the folder
SRC=$(wildcard *.c)

QBasic: $(SRC)
	# Compiles the target ($@) with all the dependencies ($^) with the flags (CFLAGS)
	gcc -o $@ $^ $(CFLAGS)

# "make cleanup" gets rid of all the files produced by the make rules above
cleanup:
	rm -f *.o QBasic

