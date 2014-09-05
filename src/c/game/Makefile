TOP = ../../..

include $(TOP)/environment/Makefile_c

OPENFTL_OBJ = main.o renderer.o shader.o texture.o

all: openftl

openftl: $(OPENFTL_OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OPENFTL_OBJ) $(LIBRARIES)

clean:
	rm -f *.o
	rm -f openftl
