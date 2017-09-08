CC=gcc
CFLAGS=-c -Wall -Werror -fPIC
LDFLAGS= -shared -Wl,-soname,libclist.1
SOURCES=clist.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=libclist.so.1.0

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


