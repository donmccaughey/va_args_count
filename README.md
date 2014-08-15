VA\_ARGS\_COUNT
=============

A C macro to find the number of arguments in the C99 `__VA_ARGS__` macro.


Usage
-----

Used directly, the `VA_ARGS_COUNT()` macro returns the number of arguments 
passed to it as an `int`.

    printf("There are %i arguments.\n", VA_ARGS_COUNT(1, "two", 3.0));

### Counting Function Arguments

By itself, this isn't very useful. The `VA_ARGS_COUNT()` macro really shines 
when used inside other variadic macros. You may have a function that takes a 
variable number of arguments like this:

    void print_strings(int count, const char *s1, ...);
    
where the first parameter `count` specifies the number of string arguments
passed to the function. It's easy to use this type of function incorrectly:

    // print 3 strings
    print_strings(5, "one", "two", "three"); // wrong!

See the error? The `print_strings()` function will now grab two invalid values
off the stack, printing garbage or even crashing.

This use of variable arguments is typically a poor design choice, but sometimes 
you run across old APIs like this. Wrapping a variadic macro around this type 
of function makes it much less error prone:

    #define PRINT_STRINGS(...) \
        print_strings(VA_ARGS_COUNT(__VA_ARGS__), __VA_ARGS__)

Now the compiler does the counting for you:

    // print 3 strings
    PRINT_STRINGS("one", "two", "three");

### Counting Array Items

Another great use of `VA_ARGS_COUNT()` is when passing arrays to functions. A 
common C idiom is to pass an array along with the count of items in the array, 
like this:

    void print_int_array(int *int_array, int count);

Like the variadic `print_strings()` function, it's possible to pass an 
incorrect count with disasterous results, most commonly when using literal 
values:

    // print 3 ints
    int high_scores[] = { 100, 98, 93 };
    print_int_array(high_scores, 5); // wrong!

Using C99 compound literals, you can make the same mistake in one line:

    // print 3 ints
    print_int_array((int[]) { 100, 98, 93 }, 5); // wrong!

The `(int[]) { 100, 98, 93 }` compound literal is equivalent to the 
`high_scores` array in the previous example.

With `VA_ARGS_COUNT()`, you can create a less error-prone wrapper macro for 
`print_int_array()` like this:

    #define PRINT_INTS(...) \
        print_int_array( \
            (int[]) { __VA_ARGS__ }, \
            VA_ARGS_COUNT(__VA_ARGS__) \
        )

And it's easier to read:

    // print 3 ints
    PRINT_INTS(100, 98, 93);
