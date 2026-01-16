reverse: reverse.o
	gcc -o reverse reverse.o

reverse.o: reverse.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c reverse.c

# NOTE: By default, the C compiler removes information that is only useful when
#       debugging, such as line numbers -- assuming the programmer knows what
#       they are doing, that information should never be needed. The -g flag
#       asks the compiler to put it back in.
debug: reverse.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g -o reverse reverse.c
