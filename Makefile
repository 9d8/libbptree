CC=gcc
TARGET=bptree

#Directories
BUILDDIR=build
INCLUDEDIR=src
SRCDIR=src

CFLAGS=
LIB=

############################################

OBJECTS:=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard src/*.c))
INCLUDE=$(patsubst %,-I%,$(INCLUDEDIR))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -fpic -o $@ $< $(INCLUDE)

# Make build directory when trying to create an object file.
$(OBJECTS): | $(BUILDDIR) 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(BUILDDIR)/lib$@.so $^ $(INCLUDE) $(LIB)

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: clean force debug install uninstall
clean:
	-rm $(BUILDDIR)/lib$(TARGET).so $(OBJECTS)

debug: CFLAGS:=$(CFLAGS)-ggdb
debug: $(TARGET)

force: clean $(TARGET)

install: $(TARGET)
	cp $(BUILDDIR)/lib$(TARGET).so /usr/lib/
	cp $(INCLUDEDIR)/bptree.h /usr/include/

uninstall:
	rm /usr/lib/lib$(TARGET).so
	rm /usr/include/bptree.h
