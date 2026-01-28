list.o: list.c list.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c list.c

# NOTE: With the -Werror flag, warnings would prevent compilation, but if we
#       are still at the testing and debugging stage, arguably warnings are
#       okay as long as we eventually address them -- some of them only show up
#       because we haven't implemented the corresponding functions yet.
debug:
	gcc -Wall -Wextra -ansi -pedantic -g -c list.c

# NOTE: Memory leaks typically don't immediately cause fatal errors, but we
#       still want to be checking for them throughout the unit testing process,
#       just to catch them before they become more serious.
test: debug
	gcc -Wall -Wextra -ansi -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
