CC	= gcc-4.8
CFLAGS	= -g -std=c11 -pedantic-errors -Wall -Wextra -Wno-unused-parameter -Wno-long-long -Werror
#CFLAGS	= -g -ansi -pedantic-errors -Wall -Wextra -Wno-unused-parameter -Wno-long-long -Werror
LINK_FLAGS = -lglloadD -lGL -lglut -L../../libs
#LINK_FLAGS = -L../../libs -L/usr/lib/x86_64-linux-gnu -lGL -lglut -lglloadD
INCLUDE_FLAGS = -I ../../libs/include;

SOURCES = $(shell find . -name \*\.c -print0 | xargs -0 echo | sed 's/\.\///g')
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(SOURCES:.c=.h)

#$(OBJECTS): $(SOURCES)
#	$(CC) $(CFLAGS) $(SOURCES)  $(LIBRARY_FLAGS) -o $(OBJECTS)
openftl: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LINK_FLAGS)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE_FLAGS)
clean:
	rm -f *.o 
	rm -f openftl
