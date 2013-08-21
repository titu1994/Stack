/*
 ============================================================================
 Name        : Stack.c
 Author      : Somshubra Majumdar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

typedef struct stack{
	int a[SIZE];
	int top;
} Stack ;

/*
 * Method declarations
 */

int push(Stack *p, int v);
int pop(Stack *p);
int peek(Stack *p);
int isEmpty(Stack *p);
void toBinaryRepresentation();
void balancedCymbals(Stack *p, char *s);
void forEachBracket(Stack *p, char *s);

int main(void) {
	Stack s;
	s.top = -1;
	char a[SIZE];

	//void toBinaryRepresentation();

	setbuf(stdout, NULL);

	//toBinaryRepresentation(&s);

	printf("Enter a string : \n");
	gets(a);

	forEachBracket(&s, a);

	return EXIT_SUCCESS;
}

int push(Stack *p, int v){

	if(p->top == SIZE - 1){
		return 0;
	}
	else{
		p->a[++p->top] = v;
		return 1;
	}

}

int pop(Stack *p){

	if(p->top == -1){
		printf("The stack is empty\n");
		return -1;
	}
	else{
		return p->a[p->top--];
	}

}

int peek(Stack *p){

	if(p->top == -1){
		printf("The stack is empty\n");
		return 0;
	}
	else{
		return p->a[p->top];
	}

}

int isEmpty(Stack *p){
	return p->top == -1;
}

/*
 * The remaining functions are not part of Stack Operations
 *
 * They are applications of Stack
 */

void toBinaryRepresentation(Stack *p){
	int v;

	printf("Enter a number\n");
	scanf("%d",&v);

	while(v != 0){
		push(p, v%2);
		v = v/2;
	}

	while(!isEmpty(p)){
		printf("%d\t",pop(p));
	}

}

void balancedCymbals(Stack *p, char *s){
	int i = 0;

	while(s[i] != '\0'){

		if(s[i] == '('){
			push(p, '(');
		}

		if(s[i] == ')'){
			if(p->top == -1){
				printf("The cymbals are unbalanced\n");
				return;
			}

			pop(p);
		}

		i++;
	}

	if(isEmpty(p)){
		printf("Cymbals are balanced\n");
	}
	else{
		printf("The cymbals are unbalanced\n");
	}

}

void forEachBracket(Stack *p, char *s){

	int i, c;

	for(i = 0; s[i] != '\0'; i++){

		if(s[i] == '('){

			push(p, '(');

		}
		else if(s[i] == '{'){

			push(p, '{');

		}else if(s[i] == '['){

			push(p, '[');

		}

		if(s[i] == ')' || s[i] == '}' || s[i] == ']'){
			if(p->top == -1){
				printf("The brackets are unbalanced because of empty close\n");
				return;
			}

			if(s[i] == ')'){
				c = peek(p);

				if(c == '('){
					pop(p);
				}
				else{
					printf("The brackets are unbalanced because of wrong order\n");
					return;
				}
			}
			else if(s[i] == '}'){
				c = peek(p);

				if(c == '{'){
					pop(p);
				}
				else{
					printf("The brackets are unbalanced because of wrong order\n");
					return;
				}
			}
			else if(s[i] == ']'){
				c = peek(p);

				if(c == '['){
					pop(p);
				}
				else{
					printf("The brackets are unbalanced because of wrong order\n");
					return;
				}
			}

		}

	}

	if(isEmpty(p)){
		printf("The brackets are balanced\n");
	}
	else{
		printf("The brackets are unbalanced\n");
	}

}


