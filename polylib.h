#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP 100
// change the value of VAR to change the uni-variable character
#define VAR 'x'

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
int deleteNode(list *l, int p) {
    int i = 1;
    if(l->head == NULL || p < 1 || p > l->size)
        return 0;
    else {
        node *tmp, *del;

        if(l->size == 1)
            l->head = l->tail = NULL;
        else if(p == 1) {
            del = l->head;
            l->head = del->next;
            del->next = NULL;
            free(del);
        } else if(p == l->size) {
            tmp = l->tail->prev;

            del = tmp->next;
            tmp->next = NULL;
            l->tail = tmp;
            free(del);
        } else {
            tmp = l->head;

            while(i < p - 1) {
                tmp = tmp->next;
                i++;
            }

            printf("here\n");

            del = tmp->next;
            tmp->next = del->next;
            del->next = NULL;
            free(del);
        }

        l->size--;

        return 1;
    }
}

// frees or returns all the memory allocated to the list back to the free store or heap
void freeList(list *l) {

}

// prints on the console the elements of the linked-list as a polynomial expression
void display(list l) {
    node *tmp = l.head;

    while(tmp != NULL) {
        printf("%i%c^%i", tmp->item.coef, VAR, tmp->item.expo);
        tmp = tmp->next;
        if(tmp != NULL && tmp->item.coef > 0)
            printf("+");
    }

    printf("\n");
}

// checks for invalid input, returns 1 if input is invalid, 0 otherwise
int inputChecking(char *str) {
    // invalid inputs:
    // not a number (except x, ^, +, -)
    // negative exponent (x^-2)
    // operation followed with a carat (4x-^ or 4x+^)
    // operation after operation (eg +-)
    // variable after variable (xx)
    // a carat followed by a non-number character (4x^x or 4x)
    // variable followed by a number without the carat (4x4 or x6) (not sure if this is invalid)
    // number carat number without the variable (4^4 or 6^1) (not sure if this is invalid)
    for(int i = 0; i < strlen(str); i++) {
        if(((str[i] < '0' || str[i] > '9') && str[i] != VAR && str[i] != '^' && str[i] != ' ' && str[i] != '+' && str[i] != '-')
        || ((str[i] == '+' && str[i + 1] == '-') || (str[i] == '-' && str[i + 1] == '+')) || (str[i] == '^' && str[i + 1] == '-')
        || ((str[i] == '-' || str[i] == '+') && str[i + 1] == '^') || str[strlen(str) - 1] == '-' || str[strlen(str) - 1] == '+'
        || (str[i] == VAR && str[i + 1] == VAR) || (str[i] == '^' && (str[i + 1] < '0' || str[i + 1] > '9'))
        || (str[i] == VAR && (str[i + 1] >= '0' && str[i + 1] <= '0')) || (str[i] == '^' && str[i - 1] != VAR))
            return 1;
    }
    return 0;
}

// extracts the coeffiecient and the exponent of each term
term extract(char *str, int nega) {
    term t;
    char co[CAP], ex[CAP];
    int x = 0, i, j, flag = 0;
    
    for(i = 0, j = 0; i < strlen(str); i++) {
        if(str[i] == VAR) {
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

    if(nega)
        t.coef *= -1;

    return t;
}

// tokenizes the string and getting each single term in an expression and appending the term to the list
int tokenize(list *poly, char inputString[]) {
    // scan through the input string say "4x^2+8x+4"
    // if some characters in the string input to make invalid, return 0
    // else if valid and term substring was successfully extracted, append it to the linked-list  and return 1
    // this else part will involve a number of tasks (assume you keep a substring called termstring
    // to store a term substring from the input string)
    // - successfully extract "4x^2" and store it in termstring
    // - extract the coefficient and exponent from the termstring 
    // - construct a term structure based on the values you extracted from the token termstring, and you may call it tempterm
    // - append this term in the linked-list by calling/invoking append(poly, term)
    int inputError, i = 0, j = 0, nega = 0;
    char termString[CAP];
    // char *termString, *tmpString;
    // char *delim = "+-";

    // checks input
    inputError = inputChecking(inputString);

    if(inputError)
        return 0;
    else {
        // checks if the first term has a negative coefficient
        if(inputString[0] == '-') {
            nega = 1;
            i = 1;
        }
        for(; i < strlen(inputString); i++) {
            // creates a substring of each single term
            if(inputString[i] != '+' && inputString[i] != '-') {
                termString[j] = inputString[i];
                j++;
            }
            // the i == strlen(inputString) - 1 is there so that the last term that has no - or + after it will still be appended
            if(inputString[i] == '+' || inputString[i] == '-' || i == strlen(inputString) - 1) {
                termString[j] = '\0';
                // appends the term into the linked-list after extracting the coefficient and the exponent of the term using extract()
                append(poly, extract(termString, nega));
                // checks if the operation after the term is minus indicating a negative coefficient for the next term
                nega = (inputString[i] == '-') ? 1 : 0;
                j = 0;
            }
        }

        /*
        another way of tokenizing the input by using strtok
        tmpString = strdup(inputString);

        if(inputString[0] == '-')
            nega = 1;
        // source https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
        termString = strtok(inputString, delim);

        while(termString != NULL) {
            printf("%s\n", termString);
            append(poly, extract(termString, nega));
            nega = 0;

            // source: https://stackoverflow.com/questions/12460264/c-determining-which-delimiter-used-strtok
            // printf("%c\n", tmpString[termString - inputString + strlen(termString)]);
            // printf("%s | %s | %i \n", termString, inputString, strlen(termString));
            // printf("%p | %p | %i \n", termString, inputString, strlen(termString));
            // printf("%i\n", termString - inputString + strlen(termString));
            
            // gets the delimeter that separated the token
            if(tmpString[termString - inputString + strlen(termString)] == '-')
                nega = 1;

            termString = strtok(NULL, delim);
        }

        free(tmpString);
        */

        return 1;
    }
}
