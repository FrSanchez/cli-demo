CC = c++ # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info

objects = main.o commands.o
all: $(objects)
	$(CC) $(CFLAGS) -o cli $(objects) -lreadline

main.o: main.cpp

commands.o: commands.cpp

clean:
	rm -f *.o cli
