# NOTE: By splitting the compilation of this program up by its source files, if
#       we ever, for example, change main.c, we only have to recompile main.c;
#       we can reuse the existing add.o instead of recompiling add.c.
a.out: main.o add.o
	gcc main.o add.o

# NOTE: Rather than attempting to form a complete program (which needs add.c),
#       this just produces an object file containing machine code for main.c.
#       Since add.h is copied into main.c, it is not compiled separately.
main.o: main.c add.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c main.c

add.o: add.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c add.c
