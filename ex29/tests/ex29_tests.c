#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

typedef int (*lib_function) (const char* data, const int len);

const char* lib_file = "build/libex29.so";

int main(int argc, char* argv[]) {
    int rc = 0;
    // check(argc == 4, "USAGE: ex29 libex29.so function data");

    char* data = "HeLlO";
    char* funcs_to_run[] = {
        "lowercase", "uppercase", "print_a_message"
    };
    int n_funcs = 3;

    void* lib = dlopen(lib_file, RTLD_NOW);
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

    int i = 0;
    for (i = 0; i < n_funcs; i++) {
        char* func_to_run = funcs_to_run[i];
        lib_function func = dlsym(lib, func_to_run);
        check(func != NULL, "did not find %s function in the library %s: %s",
                func_to_run, lib_file, dlerror());
    
        rc = func(data, strlen(data));
        check(rc == 0, "Function %s returned %d for data: %s", func_to_run, rc, data);
    }
    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return 1;
}
