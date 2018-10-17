CC=gcc
TARGET=libbptree.so
TESTTARGET=bptree_test

#Directories
BUILDDIR=build
INCLUDEDIR=src
SRCDIR=src
TESTDIR=test

CFLAGS=
LIB=

############################################

OBJECTS:=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
TESTOBJECTS:=$(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(TESTDIR)/*.c))
INCLUDE=$(patsubst %,-I%,$(INCLUDEDIR))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) -c -fpic -o $@ $< $(INCLUDE)

$(BUILDDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

# Make build directory when trying to create an object file.
$(OBJECTS) $(TESTOBJECTS): | $(BUILDDIR) 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(BUILDDIR)/$@ $^ $(INCLUDE) $(LIB)

$(TESTTARGET): $(TARGET) $(TESTOBJECTS)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $(TESTOBJECTS) $(BUILDDIR)/$(TARGET) $(INCLUDE) $(LIB)

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: clean test force debug install uninstall
clean:
	-rm $(BUILDDIR)/$(TARGET) $(BUILDDIR)/$(TESTTARGET) $(OBJECTS) $(TESTOBJECTS)

test: $(TESTTARGET)

force: clean $(TARGET)

debug: CFLAGS:=$(CFLAGS)-ggdb
debug: $(TARGET)

install: $(TARGET)
	cp $(BUILDDIR)/$(TARGET) /usr/lib/
	cp $(INCLUDEDIR)/bptree.h /usr/include/

uninstall:
	rm /usr/lib/$(TARGET)
	rm /usr/include/bptree.h
