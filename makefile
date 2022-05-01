CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Wall -Werror
VPATH = tool

AsciiArtTool: $(OBJS)
	gcc $(OBJS) -o AsciiArtTool

RLEList.o: RLEList.c RLEList.h Node.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h Node.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/AsciiArtTool.c
main.o: tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/main.c

clean:
	rm -f $(OBJS) $(EXEC)