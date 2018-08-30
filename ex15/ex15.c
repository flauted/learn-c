#include <stdio.h>

void print_1(char* names[], int ages[], int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
}


void print_2(char** _cur_name, int* _cur_age, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", *(_cur_name + i), *(_cur_age + i));
    }
}


void print_3(char** _cur_name, int* _cur_age, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", _cur_name[i], _cur_age[i]);
    }
}


void print_why(char* _names[], int _ages[], int count) {
    char** cn = _names;
    int* ca = _ages;
    for (cn = _names, ca = _ages; (ca - _ages) < count;
            cn++, ca++) {
        printf("%s is %d years old.\n", *cn, *ca);
    }
}


int main(int argc, char* argv[]) {
    int ages[] = { 23, 43, 12, 89, 2 };
    char* names[] = {
        "Alan", "Frank", "Mary", "John", "Lisa"
    };

    int count = sizeof(ages) / sizeof(int);
    print_1(names, ages, count);

    printf("---\n");

    print_2(names, ages, count);

    printf("---\n");
    print_3(names, ages, count);

    printf("---\n");
    print_why(names, ages, count);

    return 0;
}
