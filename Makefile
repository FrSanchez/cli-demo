CC = clang # Flag for implicit rules
CFLAGS = -g -DDEBUG -O0
LDFLAGS = # Flag for implicit rules
LDLIBS = # Flag for implicit rules

objects = main.o commands.o splitString.o Tree.c

all: $(objects)
	$(CC) $(CFLAGS) -o cli $(objects) $(LDFLAGS) $(LDLIBS)

%.o : %.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o cli

