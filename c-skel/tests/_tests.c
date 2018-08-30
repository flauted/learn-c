#include "minunit.h"

char* test_WHATEVER() {
    return NULL;
}

char* test_functions() {
    return NULL;
}

char* test_failures() {
    return NULL;
}

char* all_tests() {
    mu_suite_start();
    mu_run_test(test_WHATEVER);
    mu_run_test(test_functions);
    mu_run_test(test_failures);

    return NULL;
}

RUN_TESTS(all_tests);

