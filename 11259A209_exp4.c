
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

float stack[MAX];
int top = -1;

int push(float val) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return 0;
    }

    stack[++top] = val;
    return 1;
}

float pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return 0;
    }

    return stack[top--];
}

int evaluatePostfix(char postfix[], float *result) {
    int i;
    float op1, op2, value;

    top = -1;

    for (i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isspace((unsigned char)c)) {
            continue;
        }

        if (isdigit((unsigned char)c)) {
            if (!push(c - '0'))
                return 0;
        }

        else if (c == '+' || c == '-' ||
                 c == '*' || c == '/' || c == '^') {

            if (top < 1) {
                printf("Invalid postfix expression.\n");
                return 0;
            }

            op2 = pop();
            op1 = pop();

            switch (c) {
                case '+':
                    value = op1 + op2;
                    break;

                case '-':
                    value = op1 - op2;
                    break;

                case '*':
                    value = op1 * op2;
                    break;

                case '/':
                    if (op2 == 0) {
                        printf("Division by zero error.\n");
                        return 0;
                    }
                    value = op1 / op2;
                    break;

                case '^':
                    value = pow(op1, op2);
                    break;

                default:
                    return 0;
            }

            if (!isfinite(value)) {
                printf("Invalid mathematical result.\n");
                return 0;
            }

            if (!push(value))
                return 0;
        }

        else {
            printf("Invalid character: %c\n", c);
            return 0;
        }
    }

    if (top != 0) {
        printf("Invalid postfix expression.\n");
        return 0;
    }

    *result = pop();
    return 1;
}

int main() {
    char postfix[MAX];
    float result;

    printf("Enter a postfix expression (single-digit operands): ");

    if (scanf("%99s", postfix) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (evaluatePostfix(postfix, &result)) {
        printf("Result = %.2f\n", result);
    }

    return 0;
}
