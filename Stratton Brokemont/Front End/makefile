# project name (generate executable with this name)
TARGET		= StrattonBrokemont
TARGETBACK	= BackEnd
TARGETFRONT = QBasic

LKTARGETFRONT = Front\ End/src/QBasic.o
LKTARGETBACK = Back\ End/src/BackEnd.o

CC			= gcc -o
# compiling flags here
CFLAGS		= -Wall

SOURCES		:= $(wildcard *.c)
INCLUDES	:= $(wildcard *.h)
OBJECTS  	:= $(SOURCES:.c=*.o)
rm       	= rm -f

$(TARGET):
	@cd Front\ End; cd src; make QBasic
	@cd Back\ End; cd src; make BackEnd
	@#@cd Front\ End; cd src; make link
	@#@cd Back\ End; cd src; make link
	@$(CC) $(TARGET) $(CFLAGS) $(LKTARGETFRONT) $(LKTARGETBACK)
	@#@cd Front\ End; cd src; make clean
	@#@cd Back\ End; cd src; make clean
	@make clean
	@echo "Compilation complete!"

clean:
	@$(rm) $(TARGET) $(OBJECTS)
	@echo "Cleanup complete!"