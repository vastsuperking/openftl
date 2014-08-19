CC	= gcc
CFLAGS	= -g -ansi -pedantic-errors -Wall -Wextra -Wno-unused-parameter -Wno-long-long -Werror
LINK_FLAGS = -lGL -lGLU -lglut

SOURCES = $(shell find . -name \*\.c -print0 | xargs -0 echo | sed 's/\.\///g')
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(SOURCES:.c=.h)

#$(OBJECTS): $(SOURCES)
#	$(CC) $(CFLAGS) $(SOURCES)  $(LIBRARY_FLAGS) -o $(OBJECTS)
openftl: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LINK_FLAGS)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
clean:
	rm -f *.o 
	rm -f openftl
