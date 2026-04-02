#include <stdio.h>
#include <stdlib.h> // atoi
#include <string.h> // strtok
// #include <ctype.h> // toupper

#define BUF_SIZE 256
#define NUM_TESTS 13
#define NUM_STUDENTS 5

typedef struct {
    char name[BUF_SIZE];
    int score;
} Student;

static Student g_students[NUM_STUDENTS];

static void fix_case(char* ch) {
    // could use toupper() from ctype.h
    if (*ch > 0x60) {
        *ch -= 0x20;
    }
}

static void parse_student(char* buffer, Student* student) {
    char *tok = strtok(buffer, " ");
    strcpy(student->name, tok);
    fix_case(student->name);

    for (int i = 0; i < NUM_TESTS; ++i) {
        char* n = strtok(NULL, " ");
        student->score += atoi(n);
    }
}

static float find_mean() {
    float result = 0;
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        result += (float) g_students[i].score;
    }
    return result / NUM_STUDENTS;
}

static Student find_best() {
    Student best = g_students[0];
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        if (g_students[i].score > best.score) {
            best = g_students[i];
        }
    }
    return best;
}


int main() {
    char input_buffer[BUF_SIZE];

    // parse students
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        fgets(input_buffer, BUF_SIZE, stdin);
        parse_student(input_buffer, &g_students[i]);
    }

    // Print best student
    printf("%s\n", find_best().name);

    // Print students below mean
    float mean = find_mean();

    for (int i = 0; i < NUM_STUDENTS; ++i) {
        if ((float) g_students[i].score < mean) {
            printf("%s\n", g_students[i].name);
        }
    }

    return 0;
}

