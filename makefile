CC = gcc
OBJS = RLEList.o tool/AsciiArtTool.o tool/main.o
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Wall -Werror -Itool -I/home/mtm/public/2122b/ex1 -I./
VPATH = tool
EXEC = AsciiArtTool
AsciiArtTool: $(OBJS)
	gcc $(OBJS) -o $(EXEC)

RLEList.o: RLEList.c 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
tool/AsciiArtTool.o: tool/AsciiArtTool.c 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/AsciiArtTool.c -o tool/AsciiArtTool.o
tool/main.o: tool/main.c 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/main.c -o tool/main.o

clean:
	rm -f $(OBJS) $(EXEC)
