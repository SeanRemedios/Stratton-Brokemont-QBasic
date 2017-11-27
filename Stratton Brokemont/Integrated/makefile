# project name (generate executable with this name)
TARGETBACK	= BackEnd
TARGETFRONT 	= FrontEnd

BACKPATH	= "Back End/src"
FRONTPATH	= "Front End/src"
NEWPATH 	= "../../Integrated"
NEWBACKPATH	= "BackEnd-Files"
NEWFRONTPATH	= "FrontEnd-Files"

CC			= gcc -o
# compiling flags here
CFLAGS		= -Wall

SOURCES		:= $(wildcard *.c)
INCLUDES	:= $(wildcard *.h)
OBJECTS  	:= $(SOURCES:.c=*.o)
rm       	= rm -f

main:
	@make clean
	@cd $(FRONTPATH); make $(TARGETFRONT); cp $(TARGETFRONT) $(NEWPATH)/$(NEWBACKPATH)
	@cd $(BACKPATH); make $(TARGETBACK); cp $(TARGETBACK) $(NEWPATH)/$(NEWFRONTPATH)
	@echo "Compilation complete!"

clean:
	@$(rm) $(TARGET) $(OBJECTS)
	@echo "Cleanup complete!"