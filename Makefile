CC=gcc
TARGET=libbptree.so

#Directories
BUILDDIR=build
INCLUDEDIR=src
SRCDIR=src
TESTDIR=test

CFLAGS=-ggdb
LIB=

############################################

OBJECTS:=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
INCLUDE=$(patsubst %,-I%,$(INCLUDEDIR))

all: $(TARGET) build-tests

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) -c -fpic -o $@ $< $(INCLUDE)

# Make build directory when trying to create an object file.
$(OBJECTS): | $(BUILDDIR) 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(BUILDDIR)/$@ $^ $(INCLUDE) $(LIB)

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: clean build-tests run-tests install uninstall
clean:
	@make clean -C $(TESTDIR)
	-$(RM) $(BUILDDIR)/$(TARGET) $(OBJECTS)

build-tests: $(TARGET)
	@make -C $(TESTDIR)

run-tests: build-tests
	@$(TESTDIR)/run_tests.sh

install: $(TARGET)
	cp $(BUILDDIR)/$(TARGET) /usr/lib/
	cp $(INCLUDEDIR)/bptree.h /usr/include/

uninstall:
	$(RM) /usr/lib/$(TARGET)
	$(RM) /u1sr/include/bptree.h
