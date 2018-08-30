#include "ex22.h"
#include "dbg.h"

const char* MY_NAME = "Dylan Flaute";

void scope_demo(int count) {
    log_info("Count is %d", count);

    if (count > 10) {
        int count = 100;

        log_info("count in this scope is: %d", count);
    }

    log_info("count is at exit (outside of scope): %d", count);

    count = 3000;

    log_info("count after assign: %d", count);
}

int main(int argc, char* argv[]) {
    log_info("My name: %s, my age (from get_age()): %d", MY_NAME, get_age());

    set_age(100);

    log_info("Used set_age(). My age is now (from get_age()): %d", get_age());

    log_info("THE_SIZE (extern defined in ex22.h) is now: %d", THE_SIZE);

    print_size();

    THE_SIZE = 9;

    log_info("THE_SIZE is now: %d", THE_SIZE);

    print_size();

    log_info("Ratio at first: %f", update_ratio(2.0));

    log_info("Ratio again: %f", update_ratio(10.0));

    log_info("Ratio once more: %f", update_ratio(2000.0));

    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count (in ex22_main:main) after calling scope_demo: %d", count);

    return 0;
}
