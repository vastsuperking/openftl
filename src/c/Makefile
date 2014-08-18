CC	= gcc
CFLAGS	=

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJECTS)
clean:
	rm -f *.o
