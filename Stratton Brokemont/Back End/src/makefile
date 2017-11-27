# project name (generate executable with this name)
TARGET = BackEnd
LINKTARGET = BackEnd.o

CC       = gcc -std=c99 -c
# compiling flags here
CFLAGS   = -Wall -I.

LINKER   = gcc -o
# linking flags here
LFLAGS   = -Wall

LINK 	= ld
LKFLAGS	= -r

SOURCES  := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
OBJECTS  := $(SOURCES:.c=*.o)
rm       = rm -f

$(TARGET): 
	@$(LINKER) $(TARGET) $(LFLAGS) $(SOURCES)
	@echo "Back End Linking complete!"

link: obj
	$(LINK) $(LKFLAGS) $(OBJECTS) -o $(LINKTARGET)

obj: $(SOURCES) $(INCLUDES)
	@$(CC) $(CFLAGS) $(SOURCES)
	@echo "Back End Compilation complete!"

clean:
	@$(rm) $(TARGET) $(OBJECTS)
	@echo "Back End Cleanup complete!"