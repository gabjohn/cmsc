#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR 100

// #define VAR 'x'

typedef struct {
    int coef, expo;
} term;

typedef struct element {
    term item;
    struct element *next, *prev;
} node;

typedef struct {
    int size;
    node *head, *tail;
} list;

// initializes the head and tail to NULL and the size to zero
void init(list *l) {
    l->size = 0;
    l->head = l->tail = NULL;
}

// inserts the term at the end of the linked-list
int append(list *l, term t) {
    node *n = malloc(sizeof(node));

    if (n == NULL)
        return 0;
    else {
        n->item = t;
        n->prev = l->tail;
        n->next = NULL;

        if (l->head == NULL)
            l->head = l->tail = n;
        else {
            l->tail->next = n;
            l->tail = n;
        }

        l->size++;

        return 1;
    }
}

// deletes or removes the node found at the position represented by the second
// parameter the first parameter should be found at position 1
int deleteNode(list *l, int p) {
    int i = 1;

    if (l->head == NULL || p < 1 || p > l->size)
        return 0;
    else {
        node *tmp, *del;

        if (l->size == 1) {
            del = l->head;
            l->head = l->tail = NULL;
        } else {
            if (p == 1) {
                del = l->head;
                l->head = del->next;
                l->head->prev = NULL;
                del->next = NULL;
            } else if (p == l->size) {
                del = l->tail;
                tmp = del->prev;
                del->prev = NULL;
                tmp->next = NULL;
                l->tail = tmp;
            } else {
                tmp = l->head;

                while (i < p - 1) {
                    tmp = tmp->next;
                    i++;
                }

                del = tmp->next;
                tmp->next = del->next;
                tmp->next->prev = tmp;
                del->next = NULL;
                del->prev = NULL;
            }
        }
        free(del);

        l->size--;

        return 1;
    }
}

// frees or returns all the memory allocated to the list back to the free store
// or heap
void freeList(list *l) {
    while (l->size != 0) {
        deleteNode(l, 1);
    }
}

// prints on the console the elements of the linked-list as a polynomial
// expression
void display(list l) {
    node *tmp = l.head;
    int zeroFlag = 1;
    while (tmp != NULL) {
        if (tmp->item.expo > 0 && tmp->item.coef != 0) {
            zeroFlag = 0;
            if (tmp->item.expo > 1) {
                if (tmp->item.coef == 1)
                    printf("x^%i", tmp->item.expo);
                else if (tmp->item.coef == -1)
                    printf("-x^%i", tmp->item.expo);
                else if (tmp->item.coef != 0)
                    printf("%ix^%i", tmp->item.coef, tmp->item.expo);
            } else {
                if (tmp->item.coef == 1)
                    printf("x");
                else if (tmp->item.coef == -1)
                    printf("-x");
                else if (tmp->item.coef != 0)
                    printf("%ix", tmp->item.coef);
            }
        } else if (tmp->item.expo == 0 && tmp->item.coef != 0){
            zeroFlag = 0;
            printf("%i", tmp->item.coef);
        }

        // printf("%i%c^%i", tmp->item.coef, VAR, tmp->item.expo);
        if(tmp->item.coef != 0 && tmp->item.expo == 0){
            zeroFlag = 0;
        }
        tmp = tmp->next;

        if (tmp != NULL && !(tmp->prev->item.coef == 0 && tmp->prev->item.expo == 0)) printf("+");
    }

    if(zeroFlag){
        printf("0");
    }

    printf("\n");
}

char nextChar(char str[], int pos) {
    int i = pos;
    while(i < strlen(str)) {
        if(str[i] != ' ')
            return str[i];
        i++;
    }
    return 0;
}

// checks for invalid input, returns 1 if input is invalid, 0 otherwise
int inputChecking(char *str) {
    // invalid inputs:
    // not a number (except x, ^, +, -)
    // negative exponent (x^-2)
    // operation followed with a carat (4x-^ or 4x+^)
    // operation after operation (eg +-)
    // variable after variable (xx)
    // a carat followed by a non-number character (4x^x or 4x^^)
    // variable followed by a number without the carat (4x4 or x6) (not sure if this is invalid)
    // number carat number without the variable (4^4 or 6^1) (not sure if this is invalid)
    for(int i = 0; i < strlen(str); i++) {
        char next = nextChar(str, i+1);

        if(str[i + 1] == ' ') {
            if ((str[i] >= '0' && str[i] <= '9') && (next >= '0' && next <= '9'))
                return 1;
        }
        
        if(((str[i] < '0' || str[i] > '9') && str[i] != 'x' && str[i] != '^' && str[i] != ' ' && str[i] != '+' && str[i] != '-')
        || (str[i] == '+' && next == '-') 
        || (str[i] == '+' && next == '+') 
        || (str[i] == '-' && next == '+') 
        || (str[i] == '-' && next == '-') 
        || (str[i] == '^' && next == '-')
        || ((str[i] == '-' || str[i] == '+') && next == '^') 
        || str[strlen(str) - 1] == '-' 
        || str[strlen(str) - 1] == '+'
        || (str[i] == '^' && (next < '0' || next > '9'))
        || (str[i] == 'x' && (next != '^' && next != '+' && next != '-' && next != 0))) {
            // printf("%c %i", next, next);
            return 1;
        }
    }

    return 0;
}

void sortTerms(list *l) {
    node *curr = l->head;

    while (curr != NULL) {
        node *other = curr->next;

        while (other != NULL) {
            if (curr->item.expo < other->item.expo) {
                term t = curr->item;
                curr->item = other->item;
                other->item = t;
            }

            other = other->next;
        }

        curr = curr->next;
    }
}

// scan through the input string say "4x^2+8x+4"
// if some characters in the string input to make invalid, return 0
// else if valid and term substring was successfully extracted, append it to
// the linked-list  and return 1 this else part will involve a number of
// tasks (assume you keep a substring called termstring to store a term
// substring from the input string)
// - successfully extract "4x^2" and store it in termstring
// - extract the coefficient and exponent from the termstring
// - construct a term structure based on the values you extracted from the
// token termstring, and you may call it tempterm
// - append this term in the linked-list by calling/invoking append(poly,
// term
int tokenize(list *poly, char inputString[]) {
    int neg = 0, termStart = 0, var = 0, tens = 0, coefConverted = 0,
        expoConverted = 0, len = strlen(inputString);
    term t;

    // Checks for invalid inputs
    if (inputChecking(inputString)) {
        return 0;
    } else {
        for (int i = 0; i < len; i++) {
            // Initializes variables at the start and at new terms
            if (inputString[i] == '-' || inputString[i] == '+' || i == 0) {
                termStart = 1;
                tens = 1;
                var = 0;
                t.coef = 0;
                t.expo = 0;
                neg = 0;
                coefConverted = 0;
                expoConverted = 0;

                // Handles if the term is negative
                if (inputString[i] == '-') {
                    neg = 1;
                }
            }
            if (termStart) {
                // Checks if the variable has been reached and resets certain
                // variables
                if (inputString[i] == 'x') {
                    var = 1;
                    tens = 1;

                    // checks if the term has an exponent, if it does not, sets
                    // it to 1
                    char next = nextChar(inputString, i+1);
                    if (next != '^') {
                        expoConverted = 1;
                    }
                }

                // Converts the coefficients but it first checks if it is a
                // number to catch spaces in the input
                if (!var && inputString[i] >= '0' && inputString[i] <= '9') {
                    coefConverted = 1;
                    t.coef *= 10;
                    t.coef += (inputString[i] - '0');
                }

                // Converts the exponent but it first checks if it is a number
                // to catch spaces in the input
                if (!expoConverted && var && inputString[i] >= '0' &&
                    inputString[i] <= '9') {
                    t.expo *= 10;
                    t.expo += (inputString[i] - '0');
                }

                // If the next input is a plus or minus or the end of the string
                // then it means that the tem has already ended. This cleans up
                // the coeffecient and exponents, to handle edge cases
                if (inputString[i + 1] == '+' || inputString[i + 1] == '-' ||
                    i + 1 == len) {
                    termStart = 0;

                    // This means that the coefficent was not found but x was
                    if (coefConverted != 1) {
                        t.coef = 1;
                    }

                    // This means that x was found but the exponent was not
                    if (expoConverted) {
                        t.expo = 1;
                    }

                    // Converts the coefficient to negative depending on the
                    // sign used
                    if (neg) {
                        t.coef *= -1;
                    }
                    append(poly, t);
                }
            }
        }

        return 1;
    }
}