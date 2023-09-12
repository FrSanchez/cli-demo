CC = cc # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info
LDFLAGS = # Flag for implicit rules
LDLIBS = # Flag for implicit rules

objects = main.o commands.o splitString.o Tree.c

all: $(objects)
	$(CC) $(CFLAGS) -o cli $(objects) $(LDFLAGS) $(LDLIBS)

%.o : %.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o cli
