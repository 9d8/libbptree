include ../global.mk
BASEDIR=../

CFLAGS+=-I$(INCLUDEDIR) -MMD

LIBBPT=$(BUILDDIR)/$(TARGET)

UTILOBJ=$(patsubst %.c,%.o,$(wildcard util/*.c))
TESTSRC=$(wildcard *.c)
TESTS=$(patsubst %.c,%,$(TESTSRC))

all: $(TESTS)

$(TESTS): %: %.o $(UTILOBJ) $(LIBBPT)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean force
clean:
	@-$(RM) $(TESTS) *.o *.d util/*.o util/*.d cache/*

force:
	touch *.c
	@make all

-include $(TESTS:%:%.d)
