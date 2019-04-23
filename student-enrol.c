#include "student-list.h"

#define CAP 15

int enrol(list*, student);
int removeStudent(list*, char[]);
void displayProgram(list, char[]);
void displayYearLevel(list, int);
void sort(list*);

int main() {
    list l;
    student item;
    int t, c, pos, err = 0, year_level = 0;
    char student_number[MAX], program[MAX];

    init(&l);

    do {
        scanf("%i",&t);
    } while(t < 0);

    while(t > 0) {
        do {
            scanf("%i",&c);
        } while(c < 1 || c > 6);

        switch(c) {
            case 1:
                // STUDENT NUMBER
                do {
                    err = 0;
                    scanf(" %[^\n]s",item.student_num);
                    // in case student number is already taken
                    if(search(l, item.student_num)) {
                        err = 1;
                    }
                    // in case the student number isn't hyphenated
                    else if(strchr(item.student_num, '-') == NULL) {
                        err = 1;
                    }
                } while(err);

                // FIRST NAME
                scanf(" %[^\n]s",item.first_name);

                // LAST NAME
                scanf(" %[^\n]s",item.last_name);

                // MIDDLE NAME
                scanf(" %[^\n]s",item.mid_name);

                // PROGRAM
                scanf(" %[^\n]s",item.program);

                // YEAR LEVEL
                do {
                    scanf(" %i",&item.level);
                } while(item.level < 0);

                // AGE
                do {
                    scanf("%i",&item.age);
                } while(item.age < 0);

                // GENDER
                do {
                    scanf(" %c",&item.gender);
                } while(item.gender != 'M' && item.gender != 'F' && item.gender != 'O' && item.gender != 'm' && item.gender != 'f' && item.gender != 'o');

                // FINAL GRADE
                do {
                    scanf("%i",&item.f_grade);
                } while(item.f_grade < 0 || item.f_grade > 100);

                enrol(&l, item);
                printf("\n");
                displayAll(l);
                break;

            case 2:
                scanf(" %[^\n]s",student_number);
                printf("\n");
                removeStudent(&l, student_number);
                printf("\n");
                displayAll(l);
                break;
                
            case 3:
                scanf(" %[^\n]s",student_number);
                printf("\n");
                pos = search(l, student_number);
                if(pos)
                    display(getStudent(l, pos));
                break;
            
            case 4:
                scanf(" %[^\n]s", program);
                displayProgram(l, program);
                printf("\n");
                break;

            case 5:
                scanf("%i", &year_level);
                displayYearLevel(l, year_level);
                printf("\n");
                break;

            case 6:
                sort(&l);  
                printf("\n");
                displayAll(l);
                break;
        }

        t--;
    }
}

int enrol(list *l, student x) {
	node *n = malloc(sizeof(node));

	if(n == NULL || l->size == CAP)
		return 0;
	else{
		n->item = x;
		n->next = NULL;

		if(l->head == NULL)
			l->head = n;
		else{
			node *tmp = l->head;
			while(tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = n;
		}
		l->size++;
        
		return 1;
	}
}

int removeStudent(list *l, char student_number[MAX]) {
	int pos = search(*l, student_number), i = 1;

	if(!l->size || !pos)
		return 0;
	else {
        node *tmp = l->head;
        node *del;

		if(pos == 1)
			removeFirst(l);

        else if(pos == l->size) {
            while(i < pos - 1) {
                tmp = tmp->next;
                i++;
            }

            del = tmp->next;
            tmp->next = NULL;
            l->size--;
            free(del);
            
            return 1;

        } else {
            while(i < pos - 1) {
                tmp = tmp->next;
                i++;
            }

            del = tmp->next;
            tmp->next = del->next;
            del->next = NULL;
            l->size--;
            free(del);

            return 1;
        }
	}
}

void displayProgram(list l, char program[MAX]) {
	node *tmp = l.head;
	int i = 1;

	while(tmp != NULL) {
        // checks if current student is enrolled in the given program
		if(strcmp(tmp->item.program, program) == 0) {
            display(tmp->item);
        }
		tmp = tmp->next;
		i++;
	}

}

void displayYearLevel(list l, int level) {
	node *tmp = l.head;
	int i = 1;

	while(tmp != NULL) {
        // checks if current student is of the given year level
		if(tmp->item.level == level) {
            display(tmp->item);
        }
		tmp = tmp->next;
		i++;
	}

}

void sort(list *l) {
    node *curr = l->head;
    while(curr != NULL) {
        node *other = curr->next;

        while(other != NULL) {
            int order = strcmp(curr->item.student_num, other->item.student_num);

            if(order > 0) {
                student s = curr->item;
                curr->item = other->item;
                other->item = s;
            }

            other = other->next;
        }

        curr = curr->next;
    }
}