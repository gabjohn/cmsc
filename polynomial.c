#include "polylib.h"

int main() {
    list poly;
    char inputString[100];
    int cases, valid;

    // number of test cases
    scanf("%i",&cases);

    do {
        init(&poly);
        
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
