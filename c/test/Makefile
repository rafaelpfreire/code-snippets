APP_NAME=unittest

BINDIR=./bin
OBJDIR=$(BINDIR)/obj

TARGET_APP=$(BINDIR)/$(APP_NAME)

SOURCES=$(shell find ./ -iname "*.cpp")
OBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))

MOD_SOURCES+=$(wildcard ../*.c)
OBJECTS+=$(patsubst ../%.c,../%.o,$(MOD_SOURCES))

CXX=g++
CFLAGS=-pthread -g3
LDFLAGS=
LN_LIBS=-lgtest
LIBS=-L/usr/local/lib  -L/usr/lib -L/lib
INCL=-I/usr/local/include -I./include -I..

.PHONY: default all clean
.PRECIOUS: %.o

default: all
all: $(BINDIR) $(TARGET_APP)

$(OBJDIR)/%.o: ./%.cpp
	$(CXX) $(CFLAGS) $(INCL) -c $^ -o $@

$(TARGET_APP): $(OBJECTS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) $(LN_LIBS) -o $@

clean:
	rm -rf $(BINDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
