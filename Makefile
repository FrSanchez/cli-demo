appname := cli

CC := cc
CPPFLAGS := -Wall -Wextra -pedantic -g -DDEBUG -O0
LDFLAGS := 
LDLIBS :=  

all: $(appname)

debug: CFLAGS += -g -DDEBUG -O0
debug: $(appname)

srcfiles := $(shell find . -name "*.c")
objects  := $(patsubst %.c, %.o, $(srcfiles))


$(appname): $(objects)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CC) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend
