reverse: reverse.o
	gcc -o reverse reverse.o

reverse.o: reverse.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c reverse.c

# NOTE: By default, the compiler strips out information that would be useful
#       when debugging, such as line numbers, under the assumption that we know
#       what we're doing that that information will not be needed. The -g flag
#       instructs the compiler to put it back in.
debug: reverse.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g -o reverse reverse.c
