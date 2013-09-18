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
#include <ctype.h>
#include <string.h>
#include <math.h>

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
void display(Stack s);

void toBinaryRepresentation();
void balancedCymbals(Stack *p, char *s);
int forEachBracket(Stack *p, char *s);
void evaluatePostfix(Stack *p, char *a);
void evaluatePostfixRadix(Stack *p, char *a);
int precedence(char ch);
void toPostFix(Stack *p, char *a);
void toPreFix(Stack *p, char *a);

int main(void) {

	Stack s;
	int choice,ele;
	s.top = -1;

	setbuf(stdout, NULL);

	printf("Enter choice : 1 for push, 2 for pop, 3 for display entire stack\n4 for binary representation\n5 for balanced cymbals\n6 for each bracket check\n7 for evaluate Post Fix String\n9 to convert Infix to PostFix\n10 to convert Infix to Prefix\n");

	do{
		printf("Enter choice : ");
		scanf("%d", &choice);

		switch(choice)
		{
		case 1:{
			//Add element

			printf("Enter an element\n");
			scanf("%d",&ele);
			push(&s, ele);

			break;
		}
		case 2:{
			//Remove element

			ele = pop(&s);
			break;
		}
		case 3:{
			//Display

			display(s);
			break;
		}
		case 4:{
			//Convert to binary representation

			Stack t;
			t.top = -1;

			toBinaryRepresentation(&t);
			break;
		}
		case 5:{
			//Balanced Cymbals

			Stack t;
			t.top = -1;

			char string[SIZE];

			printf("Enter a string to check for balanced\n");
			scanf("%s", string);

			balancedCymbals(&t, string);

			break;
		}
		case 6:{
			//For Each Bracket

			Stack t;
			t.top = -1;

			char string[SIZE];

			printf("Enter a string of any expression with brackets to check for balanced\n");
			scanf("%s", string);

			if(forEachBracket(&t, string)){
				printf("Cymbals are balanced\n");
			}
			else{
				printf("Unbalanced\n");
			}

			break;
		}
		case 7:{
			//Evaluate Post Fix

			Stack t;
			t.top = -1;

			char string[SIZE];

			printf("Enter a string to  evaluate single digits in postfix\n");
			scanf("%s", string);

			evaluatePostfix(&t, string);

			break;
		}
		/*case 8:{
			//Evaluate Radix Post Fix

			Stack t;
			t.top = -1;

			char string[SIZE];

			printf("Enter a string using # to separate a number\n");
			scanf("%s", string);

			evaluatePostfixRadix(&t, string);

			break;
		}*/
		case 9:{
			//To convert string to Post Fix

			Stack t;
			t.top = -1;

			char string[SIZE];

			printf("Enter a expression  to convert to Post fix\n");
			scanf("%s", string);

			toPostFix(&t, string);
			break;
		}
		case 10:{
			//To convert string to Pre Fix

			Stack t;
			t.top = -1;

			char string[SIZE];

			printf("Enter a expression  to convert to Pre fix\n");
			scanf("%s", string);

			toPreFix(&t, string);

			break;
		}



		default:{
			choice = -1;
		}

		}
	}while(choice != -1);

	//getch();

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
		//printf("The stack is empty\n");
		return -1;
	}
	else{
		return p->a[p->top--];
	}

}

int peek(Stack *p){

	if(p->top == -1){
		//printf("The stack is empty\n");
		return 0;
	}
	else{
		return p->a[p->top];
	}

}

int isEmpty(Stack *p){
	return p->top == -1;
}

void display(Stack s){
   while(!isEmpty(&s))
   {
    printf("%d\t",pop(&s));

   }

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

	printf("\n");

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

int forEachBracket(Stack *p, char *s){

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
				//printf("The brackets are unbalanced because of empty close\n");
				return 0;
			}

			if(s[i] == ')'){
				c = peek(p);

				if(c == '('){
					pop(p);
				}
				else{
					//printf("The brackets are unbalanced because of wrong order\n");
					return 0;
				}
			}
			else if(s[i] == '}'){
				c = peek(p);

				if(c == '{'){
					pop(p);
				}
				else{
					//printf("The brackets are unbalanced because of wrong order\n");
					return 0;
				}
			}
			else if(s[i] == ']'){
				c = peek(p);

				if(c == '['){
					pop(p);
				}
				else{
					//printf("The brackets are unbalanced because of wrong order\n");
					return 0;
				}
			}

		}

	}

	if(isEmpty(p)){
		//printf("The brackets are balanced\n");
		return 1;
	}
	else{
		//printf("The brackets are unbalanced\n");
		return 0;
	}

}

void evaluatePostfix(Stack *p, char *a){
	int i,b,c;


	if(forEachBracket(p, a)){
		for(i = 0; a[i]; i++){

			if(a[i] >= '0' && a[i]<= '9'){
				push(p, a[i]-48);
			}
			else if(a[i] == '*'){
				c = pop(p);
				b = pop(p);
				push(p, b*c);
			}
			else if(a[i] == '+'){
				c = pop(p);
				b = pop(p);
				push(p, b+c);
			}
			else if(a[i] == '-'){
				c = pop(p);
				b = pop(p);
				push(p, b-c);
			}
			else if(a[i] == '/'){
				c = pop(p);
				b = pop(p);
				push(p, b/c);
			}
			else if(a[i] == '%'){
				c = pop(p);
				b = pop(p);
				push(p, b%c);
			}
			else if(a[i] == '^'){
				c = pop(p);
				b = pop(p);
				push(p, (int) pow(b,c));
			}

		}

		printf("%d\n", pop(p));

	}
	else{
		printf("The string is not balanced\n");
	}


}

void evaluatePostfixRadix(Stack *p, char *a){
	int i,b,c,x = 0, f = 0;



	if(forEachBracket(p, a)){
		for(i = 0; a[i]; i++){

			if(a[i] >= '0' && a[i]<= '9'){
				f = 1;
				x = x*10 + (a[i]-48);
			}
			else if(a[i] == '#'){
				if(f != 0){
					f = 0;
					push(p, x);
					x = 0;
				}
			}
			else if(a[i] == '*'){
				c = pop(p);
				b = pop(p);
				push(p, b*c);
			}
			else if(a[i] == '+'){
				c = pop(p);
				b = pop(p);
				push(p, b+c);
			}
			else if(a[i] == '-'){
				c = pop(p);
				b = pop(p);
				push(p, b-c);
			}
			else if(a[i] == '/'){
				c = pop(p);
				b = pop(p);
				push(p, b/c);
			}
			else if(a[i] == '%'){
				c = pop(p);
				b = pop(p);
				push(p, b%c);
			}
			else if(a[i] == '^'){
				c = pop(p);
				b = pop(p);
				push(p, (int) pow(b,c));
			}

		}

		printf("%d\n", pop(p));

	}
	else{
		printf("Unbalanced String\n");
	}
}

int precedence(char ch){
	switch(ch){
		case '^':
		case '$':
			return 4;
		case '*':
		case '/':
		case '%':
			return 3;
		case '+':
		case '-':
			return 2;
		case '(':
		case ')':
			return 1;
	}

	return 0;
}

void toPostFix(Stack *p, char *a){
	int i = 0,j = 0;
	char ch, post[SIZE];

	for(i = 0; a[i]; i++){

		if(isalpha(a[i]) || isdigit(a[i]))
			post[j++] = a[i];

		else if(isEmpty(p) || a[i] == '(' || precedence(a[i]) >= precedence(peek(p)) || a[i] == '^'){

			push(p, a[i]);

		}

		else if(a[i] == ')'){
			while((ch = pop(p)) != '('){
				post[j++] = ch;
			}
		}
		else{
			while(!isEmpty(p) && precedence(a[i]) < precedence(peek(p))){
				post[j++] = pop(p);
			}

			push(p, a[i]);
		}
	}

	while(!isEmpty(p)){
		post[j++] = pop(p);
	}

	post[j] = '\0';

	puts(post);


}

void toPreFix(Stack *p, char *a){
	int i,j = 0;
	int n = strlen(a);
	char pre[SIZE], ch;

	for(i = n-1; i >= 0; i--){

		if(isalpha(a[i]) || isdigit(a[i])){
			pre[j++] = a[i];
		}

		else{
			if(isEmpty(p) && a[i] == '^' && peek(p) == '^'){
				pre[j++] = a[i];
			}
			else if(!isEmpty(p) || a[i] == ')' || precedence(a[i]) >= precedence(peek(p))){
				push(p, a[i]);
			}
			else if(a[i] == '('){
				while((ch = pop(p)) != ')'){
					pre[j++] = ch;
				}
			}
			else{
				while(!isEmpty(p) && precedence(a[i]) < precedence(peek(p))){
					pre[j++] = pop(p);
				}

				push(p, a[i]);
			}

		}

	}

	while(!isEmpty(p)){
		pre[j++] = pop(p);
	}

	pre[j] = '\0';

	n = strlen(pre);

	strrev(pre);

	puts(pre);
}
