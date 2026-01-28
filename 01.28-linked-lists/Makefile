list.o: list.c list.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c list.c

# NOTE: With the -Werror flag, warnings like unused parameters would prevent
#       compilation. Arguably, if we are still in the process of testing and
#       debugging, that's okay; it might just mean that we haven't implemented
#       the corresponding functions yet.
debug:
	gcc -Wall -Wextra -ansi -pedantic -g -c list.c

# NOTE: Even if all the tests that we expect to pass are passing, we also need
#       to ensure that we haven't inadvertently leaked any memory. Throughout
#       the testing process, we want to make sure we address any leaks sooner
#       rather than later.
test: debug
	gcc -Wall -Wextra -ansi -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
