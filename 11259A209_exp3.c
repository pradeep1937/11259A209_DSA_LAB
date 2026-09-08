#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char c) {
if (top == MAX - 1)
printf("Stack Overflow\n");
else
stack[++top] = c;
}
char pop() {
if (top == -1) {
printf("Stack Underflow\n");
return -1;
}
return stack[top--];
}
char peek() {
if (top == -1)
return -1;
return stack[top];
}
int precedence(char c) {
if (c == '^') return 3;
if (c == '*' || c == '/') return 2;
if (c == '+' || c == '-') return 1;
return -1;
}
int isOperand(char c) {
return isalnum(c);
}
void infixToPostfix(char infix[], char postfix[]) {
int i, j = 0;
for (i = 0; infix[i] != '\0'; i++) {
char c = infix[i];
if (isOperand(c)) {
postfix[j++] = c;
} else if (c == '(') {
push(c);
} else if (c == ')') {
while (top != -1 && peek() != '(')
postfix[j++]=pop();
pop(); /* remove*/
} else {
while (top != -1 && precedence(peek()) >= precedence(c))
postfix[j++] = pop();
push(c);
}
}
while (top != -1)
postfix[j++] = pop();
postfix[j] = '\0';
}
int main() {
char infix[MAX], postfix[MAX];
printf("Enter an infix expression: ");
scanf("%s", infix);
infixToPostfix(infix, postfix);
printf("Postfix expression: %s\n", postfix);
return 0;
}
