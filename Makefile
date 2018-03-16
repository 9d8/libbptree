CC=gcc
TARGET=btree

#Directories
BUILDDIR=build
INCLUDEDIR=src
SRCDIR=src

CFLAGS=
LIB=-lm
INCLUDE=-I$(INCLUDEDIR)

############################################

OBJECTS:=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard src/*.c))
DEPS:=$(patsubst $(INCLUDEDIR)/%.c,$(INCLUDEDIR)/%.o,$(wildcard src/*.h))


$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(TARGET): $(OBJECTS)
	$(CC) -o $(BUILDDIR)/$@ $^ $(CFLAGS) $(INCLUDE) $(LIB)

debug: CFLAGS=-ggdb
debug: $(OBJECTS)
	$(CC) -o $(BUILDDIR)/$(TARGET) $^ $(CFLAGS) $(INCLUDE) $(MAGICKWAND) $(LIB)

.PHONY: clean force
clean:
	-rm $(BUILDDIR)/$(TARGET) $(OBJECTS)

force: clean $(TARGET)