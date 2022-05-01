CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Wall -Werror

AsciiArtTool: main.o AsciiArtTool.o RLEList.o
	gcc main.o AsciiArtTool.o RLEList.o -o AsciiArtTool

RLEList.o: RLEList.c RLEList.h Node.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h Node.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
main.o: main.c AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)