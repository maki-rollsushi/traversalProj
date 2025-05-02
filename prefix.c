#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
char stack[MAX];
int top = -1;

// Function to push an element into the stack
void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

// Function to pop an element from the stack
char pop() {
    if (top >= 0)
        return stack[top--];
    return -1;
}

// Function to check the precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to reverse a string
void reverse(char *exp) {
    int length = strlen(exp);
    for (int i = 0; i < length / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[length - i - 1];
        exp[length - i - 1] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char *exp, char *result) {
    reverse(exp);
    int k = 0;
    
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isalnum(exp[i])) {
            result[k++] = exp[i];
        }
        else if (exp[i] == ')') {
            push(exp[i]);
        }
        else if (exp[i] == '(') {
            while (top >= 0 && stack[top] != ')') {
                result[k++] = pop();
            }
            pop();  // Pop the ')'
        }
        else if (isOperator(exp[i])) {
            while (top >= 0 && precedence(stack[top]) >= precedence(exp[i])) {
                result[k++] = pop();
            }
            push(exp[i]);
        }
    }
    
    while (top >= 0) {
        result[k++] = pop();
    }
    
    result[k] = '\0';
    reverse(result);
}

// Function to check if the expression is a valid infix expression
int isValidInfix(char *exp) {
    int i, len = strlen(exp);
    int openParentheses = 0;
    int prevChar = 0;  // To track the previous character (0: none, 1: operand, 2: operator, 3: parenthesis)
    
    for (i = 0; i < len; i++) {
        char c = exp[i];
        
        // Check for invalid characters
        if (!isalnum(c) && !isOperator(c) && c != '(' && c != ')') {
            return 0;  // Invalid character found
        }
        
        // Check parentheses balance
        if (c == '(') {
            openParentheses++;
        } else if (c == ')') {
            openParentheses--;
            if (openParentheses < 0) return 0;  // Mismatched parentheses
        }
        
        // Check for consecutive operators or invalid start/end of expression
        if (isOperator(c)) {
            if (prevChar == 2 || prevChar == 0) return 0;  // Consecutive operators or starts with operator
            prevChar = 2;
        }
        else if (isalnum(c)) {
            prevChar = 1;
        }
        else if (c == '(' || c == ')') {
            prevChar = 3;
        }
    }
    
    // Expression should not end with an operator or an opening parenthesis
    if (prevChar == 2 || prevChar == 3) return 0;
    
    // Parentheses should be balanced
    return openParentheses == 0;
}

int main() {
    char infix[MAX], prefix[MAX];
    
    printf("Enter an infix expression: ");
    gets(infix);  // Use gets or fgets for input (depends on compiler)
    
    // Check if the input is a valid infix expression
    if (!isValidInfix(infix)) {
        printf("Invalid infix expression!\n");
        return 1;
    }
    
    infixToPrefix(infix, prefix);
    
    printf("Prefix Expression: %s\n", prefix);
    
    return 0;
}
