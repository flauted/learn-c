#include <stdio.h>


void print_states(char** states, int num_states) {
    int i = 0;

    for (i=0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }
}

int main(int argc, char** argv) {
    int i = 0;

    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    char* states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    // int num_states = sizeof(states) / sizeof(char*);

    // for (i = 0; i < num_states; i++) {
    //     printf("state %d: %s\n", i, states[i]);
    // }
    print_states(states, sizeof(states) / sizeof(char*));

    return 0;
}
