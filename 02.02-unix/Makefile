# NOTE: This declares a variable named "CFLAGS" containing all of the flags we
#       intend to pass to the compiler. As programmers who ostensibly now know
#       what we are doing, we can drop the -Werror flag and switch to the
#       latest supported GNU 11 standard.
CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: copy fcopy

debug: CFLAGS += -g
debug: clean all

copy: copy.o
	gcc -o copy copy.o

fcopy: fcopy.o
	gcc -o fcopy fcopy.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
