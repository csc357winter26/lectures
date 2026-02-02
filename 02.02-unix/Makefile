# NOTE: As programmers who ostensibly know what we are doing, we can drop the
#       -Werror flag and switch to the latest GNU 11 standard supported by the
#       Cal Poly UNIX servers.
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
