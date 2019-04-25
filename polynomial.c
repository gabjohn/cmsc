#include "polylib.h"

// void init(list*);
// int append(list*, term);
// int deleteNode(list*, int);
// void freeList(list*);
// void display(list);
// int tokenize(list*, char);

int main() {
    list poly;
    char inputString[100];
    int cases, valid;

    // number of test cases
    scanf("%i",&cases);

    init(&poly);

    do {
        scanf(" %[^\n]s",inputString);
        valid = tokenize(&poly, inputString);

        if(valid)
            display(poly);
        else 
            printf("Invalid polynomial.\n");

        // freeList(&poly);

        cases--;
    } while(cases > 0);
}