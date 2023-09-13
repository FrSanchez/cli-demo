appname := cli

CC := clang
CXX := clang++
CXXFLAGS := -std=c++11
CFLAGS := -g -O0 -Wall -Wextra -pedantic -DDEBUG
LDFLAGS := -g
LDLIBS := 

srcfiles := $(shell find . -name "*.c")
objects  := $(patsubst %.c, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend
