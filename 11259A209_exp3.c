
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = c;
    }
}

char pop() {
    if (top == -1) {
        return '\0';
    }
    return stack[top--];
}

char peek() {
    if (top == -1) {
        return '\0';
    }
    return stack[top];
}

int precedence(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return -1;
}

int isOperand(char c) {
    return isalnum((unsigned char)c);
}

int isOperator(char c) {
    return c == '+' || c == '-' ||
           c == '*' || c == '/' || c == '^';
}

int infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    top = -1;

    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace((unsigned char)c)) {
            continue;
        }

        if (isOperand(c)) {
            postfix[j++] = c;
        }

        else if (c == '(') {
            push(c);
        }

        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                postfix[j++] = pop();
            }

            if (top == -1) {
                return 0;
            }

            pop();
        }

        else if (isOperator(c)) {
            while (top != -1 && peek() != '(' &&
                   (precedence(peek()) > precedence(c) ||
                   (precedence(peek()) == precedence(c) && c != '^'))) {
                postfix[j++] = pop();
            }

            push(c);
        }

        else {
            return 0;
        }
    }

    while (top != -1) {
        if (peek() == '(') {
            return 0;
        }

        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    return 1;
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");

    if (scanf("%99s", infix) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (strlen(infix) == 0) {
        printf("Empty expression.\n");
        return 1;
    }

    if (infixToPostfix(infix, postfix)) {
        printf("Postfix expression: %s\n", postfix);
    } else {
        printf("Invalid infix expression.\n");
    }

    return 0;
}
