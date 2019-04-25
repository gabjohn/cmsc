#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int coef, expo;
}term;

typedef struct element {
    term item;
    struct element *next, *prev;
}node;

typedef struct {
    int size;
    node *head, *tail;
}list;

//initializes the head and tail to NULL and the size to zero
void init(list *l) {
    l->size = 0;
    l->head = l->tail = NULL;
}

// inserts the term at the end of the linked-list
int append(list *l, term t) {
    node *n = malloc(sizeof(node));

    if(n == NULL)
        return 0;
    else {
        n->item = t;
        n->prev = l->tail;
        n->next = NULL;

        if(l->head == NULL)
            l->head = l->tail = n;
        else {
           l->tail->next = n;
           l->tail = n;
        }

        l->size++;

        return 1;
    }
}

// deletes or removes the node found at the position represented by the second parameter
// the first parameter should be found at position 1
int deleteNode(list *l, int position) {

}

// frees or returns all the memory allocated to the list back to the free store or heap
void freeList(list *l) {
    free(l);
}

// prints on the console the elements of the linked-list as a polynomial expression
void display(list l) {
    node *tmp = l.head;

    while(tmp != NULL) {
        printf("%i %i\n", tmp->item.coef, tmp->item.expo);
        tmp = tmp->next;
    }
}

// checks for invalid input, returns 1 if input is invalid, 0 otherwise
int inputChecking(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(((str[i] < '0' || str[i] > '9') && str[i] != 'x' && str[i] != '^' && str[i] != ' '
            && str[i] != '+' && str[i] != '-') || ((str[i] == '+' && str[i + 1] == '-') 
            || (str[i] == '+' && str[i + 1] == '-')) || (str[i] == '^' && str[i + 1] == '-'))
                return 1;
    }
    return 0;
}

// extracts the coeffiecient and the exponent of each term
term extract(char *str) {
    term t;
    char co[100], ex[100];
    int x = 0, i, j, flag = 0;
    
    for(i = 0, j = 0; i < strlen(str); i++) {
        if(str[i] == 'x') {
            x = i + 1;
            co[i] = '\0';
            i++;
        }

        if(!x)
            co[i] = str[i];
        else {
            if(str[i] == '^')
                flag++;
            else {
                ex[j] = str[i];
                j++;
            }
        }
    }
    ex[j] = '\0';

    // array of characters to int
    t.coef = atoi(co);
    t.expo = atoi(ex);
    
    // case x, coeffiecient is 1
    if(t.coef == 0 && x == 1)
        t.coef = 1;
    
    // case x, exponent is 1
    if(t.expo == 0 && x && !flag)
        t.expo = 1;

    return t;
}

// tokenizes the string and getting each single term in an expression and appending the term to the list
int tokenize(list *poly, char *inputString) {
    // scan through the input string say "4x^2+8x+4"
    // if some characters in the string input to make invalid, return 0
    // else if valid and term substring was successfully extracted, append it to the linked-list  and return 1
    // this else part will involve a number of tasks (assume you keep a substring called termstring
    // to store a term substring from the input string)
    // - successfully extract "4x^2" and store it in termstring
    // - extract the coefficient and exponent from the termstring 
    // - construct a term structure based on the values you extracted from the token termstring, and you may call it tempterm
    // - append this term in the linked-list by calling/invoking append(poly, term)
    int inputError, i, j = 0;
    char *termString;
    char delim[3] = "+-";
    term tmpTerm;

    inputError = inputChecking(inputString);

    if(inputError)
        return 0;
    else {
        tmpString[ = ]
        termString = strtok(inputString, delim);

        while(termString != NULL) {
            printf("%s\n", termString);
            tmpTerm = extract(termString);
            // source: https://stackoverflow.com/questions/12460264/c-determining-which-delimiter-used-strtok
            // printf("%c\n", tmpString[termString-inputString+strlen(termString)]);
            append(poly, tmpTerm);
            printf("%i | %i\n", tmpTerm.coef, tmpTerm.expo);

            termString = strtok(NULL, delim);
        }

        return 1;
    }
}