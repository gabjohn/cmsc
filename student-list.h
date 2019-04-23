#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
	char student_num[MAX];
	char first_name[MAX];
	char last_name[MAX];
	char mid_name[MAX];
	char program[MAX];
	int level;
	int age;
	char gender;
	int f_grade;
}student;

typedef struct mynode{
	student item;
	struct mynode *next;
}node;

typedef struct{
	int size;
	node *head;
}list;

void init(list *l){
	l->size = 0;
	l->head = NULL;
}

void display(student data) {
	printf("%s\n", data.student_num);
	printf("%s,", data.last_name);
    printf(" %s", data.first_name);
	printf(" %s\n", data.mid_name);
	printf("%s\n", data.program);
	printf("%i\n", data.level);
	printf("%i\n", data.age);
	printf("%c\n", data.gender);
	printf("%i\n", data.f_grade);
    printf("\n");
}

void displayAll(list l){
	node *curr = l.head;

	if(curr == NULL)
		printf("NO STUDENTS CURRENTLY ENROLLED\n");

	while(curr!=NULL){
		display(curr->item);
		curr = curr->next;
	}
}

int removeFirst(list *l){
	if(l->head==NULL)
		return 0;
	else{
		node *del = l->head;
		l->head = del->next;
		del->next = NULL;
		l->size--;
		free(del);
		return 1;
	}
}

// returns the position of the student
int search(list l, char student_number[MAX]) {
	node *tmp = l.head;
	int i = 1;

	while(tmp != NULL) {
		if(strcmp(tmp->item.student_num, student_number) == 0)
			return i;
		tmp = tmp->next;
		i++;
	}

	return 0;
}

// function to get the student using the position
student getStudent(list l, int pos) {
	node *tmp = l.head;
	int i = 1;

	while(i < pos) {
		tmp = tmp->next;
		i++;
	}

	return tmp->item;
}