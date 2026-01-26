/* NOTE: This defines a new type named "struct Pair" by composing two integers
 *       together. Note that this just tells the compiler what a value of that
 *       type looks like; it doesn't actually make any such values. */
struct Pair {
    int first;
    int second;
};

/* NOTE: Alternatively, if we don't want to have to type the keyword "struct"
 *       everywhere, we can tell the compiler that "Pair" is just a new name
 *       for the existing type "struct Pair". */
typedef struct Pair Pair;
