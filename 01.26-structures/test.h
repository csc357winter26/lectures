/* NOTE: This defines a new type named "struct Pair". Note that it only tells
 *       the compiler what that type looks like -- it consists of two integers
 *       composed together -- it doesn't actually make any values of that
 *       type. */
struct Pair {
    int first;
    int second;
};

/* NOTE: The above defines the type "struct Pair", but it is mildly annoying to
 *       have to type the keyword "struct" every time we want to use that type.
 *       A type definition allows us to give the type "struct Pair" the new
 *       name "Pair". */
typedef struct Pair Pair;
