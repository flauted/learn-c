#include <stdio.h>
#include <string.h>

#define MAX_DATA 100


int read_line(char* line, int max_buf, FILE* f) {
    int i = 0;
    for (i = 0; i < max_buf - 1; i++) {
        char next = fgetc(f);
        if (next == '\0' || next == '\n') {
            line[i] = '\0';
            return 0;
        } else if (next == EOF) {
            line[i] = '\0';
            return 1;
        }
        line[i] = next;
    }
    // buffer goes beyond max_buf
    return -1;
}


int and_search(FILE* file, int argc, char** words) {
    char line[MAX_DATA];
    char* r = NULL;
    char* substr = NULL;
    int i = 0;
    int n_words_found = 0;

    int found[argc - 1];
    for (i = 0; i < argc -1; i++) {
        found[i] = 0;
    }

    // read lines
    while ((r = fgets(line, MAX_DATA, file)) != NULL) {
        // iterate over not-found words
        for (i = 1; i < argc; i++) {
            if (found[i-1] == 0) {
                // if the word is found, add it and count it
                if ((substr = strstr(line, words[i])) != NULL) {
                    // printf("%s", line);
                    found[i-1] = 1;
                    n_words_found += 1;
                    // if all words are found, return success
                    if (n_words_found == argc - 1) {
                        return 0;
                    }
                }
            }
        }
    }
    return -1;
}


int main(int argc, char* argv[]) {
    char* log_dot = ".logfind";
    FILE* f_dot = fopen(log_dot, "r");
    if (f_dot == NULL) {
        printf("Failed to open %s\n", log_dot);
        return -1;
    }
    char log_fn[MAX_DATA];
    int rc = 0;
    while ((rc = read_line(log_fn, MAX_DATA, f_dot)) != 1) {
        if (rc != 0) {
            printf("Something went wrong.");
            fclose(f_dot);
            return -1;
        }

        // printf("%s\n", log_fn);

        FILE* f_log = fopen(log_fn, "r");
        if (f_log == NULL) {
            printf("Failed to open %s\n", log_fn);
            return -1;
        }
        // printf("Successfully opened %s\n", log_fn);
        if (and_search(f_log, argc, argv) == 0) {
            // printf("\n\n!!!!!! Found all words in %s\n\n", log_fn);
            printf("[y] %s\n", log_fn);
        } else {
            printf("[x] %s\n", log_fn);
        }
        fclose(f_log);
    }

    fclose(f_dot);

    return 0;
}

