#include <stdlib.h>
#include <stdio.h>

struct my_struct {
    int my_number;
    double my_double;
};


int main(int argc, char *argv[])
{
    int test_number = 3;
    double test_double = 4.0;

    struct my_struct test_struct = { test_number, test_double };

    printf("sizeof(test_number): %lu\n", sizeof(test_number));
    printf("sizeof(test_double): %lu\n", sizeof(test_double));
    printf("sizeof(test_struct): %lu\n", sizeof(test_struct));

    return EXIT_SUCCESS;
}