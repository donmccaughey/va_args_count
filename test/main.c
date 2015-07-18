#include <stdio.h>
#include <stdlib.h>
#include <va_args_count.h>


#define PRINT_INTS(...) \
    print_int_array( \
        (int[]) { __VA_ARGS__ }, \
        VA_ARGS_COUNT(__VA_ARGS__) \
    )


static void
print_int_array(int *int_array, int count);


int
main(int argc, char *argv[])
{
    PRINT_INTS(1, 2, 3, 5, 8, 13);
    return EXIT_SUCCESS;
}


static void
print_int_array(int *int_array, int count)
{
    printf("Printing %i integers:\n", count);
    for (int i = 0; i < count; ++i) {
        printf("\t%i\n", int_array[i]);
    }
}
