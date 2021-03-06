.SUFFIXES:
TARGETS=main
CC=gcc
CFLAGS=-g -Wfatal-errors -O2 -fomit-frame-pointer
DEPS=$(wildcard *.h) Makefile
#OBJS=rand.o
#$(objects:.o=.c)

all: $(TARGETS)
clean:
	rm -rf $(TARGETS)

%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS) -o $@

%: %.c $(OBJS) $(DEPS)
	$(CC) $< $(OBJS) $(CFLAGS) -o $@
