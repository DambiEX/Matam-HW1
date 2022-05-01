CC = gcc

OBJS=RLEList.o AsciiArtTool.o main.o
DEBUG_FLAG=
COMP_FLAGS=-std=c99 -Wall -Werror -I/home/mtm/public/2122b/ex1 -I/tool -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c

AsciiArtTool: $(OBJS)
	$(CC) $(OBJS) -o AsciiArtTool

RLEList.o: RLEList.c Node.h

AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h Node.h

main.o: tool/main.c tool/AsciiArtTool.h

clean:
	rm -f $(OBJS) $(EXEC)