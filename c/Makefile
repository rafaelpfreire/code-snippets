SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(notdir $(SOURCES)))

CXX=gcc
CFLAGS=
LDFLAGS=
LN_LIBS=
LIBS=-L/usr/local/lib  -L/usr/lib -L/lib
INCL=-I/usr/local/include -I./include

.PHONY: default all clean
.PRECIOUS: %.o

default: all
all: $(OBJECTS)

./%.o: ./%.cpp
	$(CXX) $(CFLAGS) $(INCL) -c $^ -o $@

clean:
	rm -rf $(OBJECTS)
