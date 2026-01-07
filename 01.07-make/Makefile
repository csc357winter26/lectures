# NOTE: Here, "a.out" is the target and "hello.c" is the dependency. If a.out
# 	    does not exist, or if it is older than hello.c, then the following
# 	    command "gcc ..." will be run in order to compile hello.c into an
# 	    updated version of a.out.
a.out: hello.c
	gcc -Wall -Werror -Wextra -ansi -pedantic hello.c
