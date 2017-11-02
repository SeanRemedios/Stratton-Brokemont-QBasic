CFLAGS = -Wall

# All .c files in the folder
SRC=$(wildcard *.c)

QBasic: $(SRC)
	# Compiles the target ($@) with all the dependencies ($^) with the flags (CFLAGS)
	gcc -o $@ $^ $(CFLAGS)

	# Example of how to compile a file without having to continuously type out the commands.
	# Must include all .c files that are dependent on one (e.g. if agent uses functions from check)
agent: 
	gcc -Wall agent.c check.c -o agent


# "make cleanup" gets rid of all the files produced by the make rules above
cleanup:
	rm -f *.o QBasic

