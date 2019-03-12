CC=gcc
CFLAGS=-ggdb -I../src -MMD

LIBBPT=../build/libbptree.so

############################################

TESTSRC=$(wildcard test_*.c)
TESTS=$(patsubst %.c,%,$(TESTSRC))

all: $(TESTS)

$(TESTS): %: %.o $(LIBBPT)
	$(CC) $(CFLAGS) -o $@ $< $(LIBBPT)

.PHONY: clean force
clean:
	-$(RM) $(TESTS) *.o *.d

force:
	touch *.c
	@make all

-include $(TESTS:%:%.d)
