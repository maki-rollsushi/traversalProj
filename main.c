#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//binary tree
typedef struct binTree {
    char data;
    struct binTree* left;
    struct binTree* right;
} binTree;



//functional prototypes
//builds a Tree based on the user input --from
binTree* buildPostfix(const char* expression);
binTree* buildPrefix(const char* expression);
binTree* buildInfix(const char* expression); 


//prints the output based on the input --to
void printPostfix(binTree* root);
void printPrefix(binTree* root);
void printInfix(binTree* root);  

void help();
void guide();



//takes an input from the user.
int main(int argc, char* argv[]) {
    //Only one input possibly -h, --help or --guide
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            help();
            return 0;
        }
        else if (strcmp(argv[1], "--guide") == 0) {
            guide();
            return 0;
        }
        else {
            printf("Error: Unknown option. Use -h or --help or --guide for more details.\n ");
            return 1;
        }
    }
    else if (argc == 6) { 
        // Expected input: ./program --from X --to Y "expression"
        
        char* expression = argv[5];
        char* fromFormat = NULL;
        char* toFormat = NULL;

        // Read the --from and --to arguments
        if (strcmp(argv[1], "--from") == 0) {
            fromFormat = argv[2];
        }
        else {
            printf("Error: Missing or incorrect --from argument. Input is \'%s\' it must be --from \n", argv[2]);
            return 1;
        }

        if (strcmp(argv[3], "--to") == 0) {
            toFormat = argv[4];
        }
        else {
            printf("Error: Missing or incorrect --to argument. Input is \'%s\' it must be --to\n", argv[5]);
            return 1;
        }
        
        // Build the expression tree
        binTree* root = NULL;

        if (strcmp(fromFormat, "postfix") == 0) {
            printf("Create tree from postfix.\n");
            //root = buildFromPostfix(expression);
        }
        else if (strcmp(fromFormat, "prefix") == 0) {
            //root = buildFromPrefix(expression);
            printf("Create tree from prefix.\n");

        }
        else if (strcmp(fromFormat, "infix") == 0) {
            //root = buildFromInfix(expression);
            printf("Create tree from infix.\n");
        }
        else {
            printf("Error: Invalid format specifier \'%s\' for --from. Must be infix, prefix, or postfix.\n", fromFormat);
            return 1;
        }

        if (root == NULL) {
            printf("Error: Failed to build expression tree.\n");
            return 1;
        }

        // Print the output format
        if (strcmp(toFormat, "postfix") == 0) {
            printPostfix(root);
            printf("\n");
        }
        else if (strcmp(toFormat, "prefix") == 0) {
            printPrefix(root);
            printf("\n");
        }
        else if (strcmp(toFormat, "infix") == 0) {
            printInfix(root);
            printf("\n");
        }
        else {
            printf("Error: Invalid format specifier \'%s\' for --to. Must be infix, prefix, or postfix.\n", toFormat);
            return 1;
        }
    }
    else {
        printf("Error: Incorrect number of arguments. Use -h or --help for usage.\n");
        return 1;   
    }

    return 0;
}

void help() {
    printf("******************************************************************************\n");
    printf("*                      NOTATION CONVERTER - HELP MENU                        *\n");
    printf("******************************************************************************\n");
    printf("* USAGE:                                                                     *\n");
    printf("*   ./notation-converter --from <input_format> --to <output_format> \"expr\"   *\n");
    printf("*                                                                            *\n");
    printf("* PARAMETERS:                                                                *\n");
    printf("*   <input_format>  : infix | prefix | postfix                               *\n");
    printf("*   <output_format> : infix | prefix | postfix                               *\n");
    printf("*   \"expr\"         : arithmetic expression (quotes if contains spaces)       *\n");
    printf("******************************************************************************\n");
    printf("* EXAMPLES:                                                                  *\n");
    printf("*   ./notation-converter --from infix --to postfix \"a+b\"                     *\n");
    printf("*   ./notation-converter --from prefix --to infix \"+ a b\"                    *\n");
    printf("*   ./notation-converter --from postfix --to prefix \"a b +\"                  *\n");
    printf("******************************************************************************\n");
    printf("* OTHER OPTIONS:                                                             *\n");
    printf("*   -h, --help   : Display this help menu                                    *\n");
    printf("*   --guide      : Show full user guide with rules, details, and examples    *\n");
    printf("******************************************************************************\n");
}


void guide() {
    printf("******************************************************************************\n");
    printf("*                                                                            *\n");
    printf("*                  NOTATION CONVERTER CLI GUIDE                              *\n");
    printf("*                                                                            *\n");
    printf("******************************************************************************\n");
    printf("* This section is dedicated as the guide for the project:                    *\n");
    printf("* Notation Converter CLI                                                     *\n");
    printf("******************************************************************************\n");
    printf("* What this program does:                                                    *\n");
    printf("*   This tool converts an arithmetic expression from one notation            *\n");
    printf("*   (infix, prefix, or postfix) to another by:                               *\n");
    printf("*     - Parsing the expression                                               *\n");
    printf("*     - Building an expression tree                                          *\n");
    printf("*     - Printing the tree in the desired output format                       *\n");
    printf("******************************************************************************\n");
    printf("* HOW TO RUN THE PROGRAM:                                                    *\n");
    printf("*   ./notation-converter --from <input_format> --to <output_format> \"expr\"   *\n");
    printf("*   <input_format>  : infix | prefix | postfix                               *\n");
    printf("*   <output_format> : infix | prefix | postfix                               *\n");
    printf("*   \"expression\"   : The expression in quotes (esp. if it has spaces)        *\n");
    printf("******************************************************************************\n");
    printf("* Supported Formats:                                                         *\n");
    printf("*   Infix   : a + b                                                          *\n");
    printf("*     Ex. ./notation-converter --from infix --to postfix \"a+b\"               *\n");
    printf("*   Prefix  : + a b                                                          *\n");
    printf("*     Ex. ./notation-converter --from prefix --to postfix \"+ a b\"            *\n");
    printf("*   Postfix : a b +                                                          *\n");
    printf("*     Ex. ./notation-converter --from postfix --to infix \"a b +\"             *\n");
    printf("******************************************************************************\n");
    printf("* Expression Rules:                                                          *\n");
    printf("*   - Use only single-digit numbers or single-letter variables               *\n");
    printf("*   - No parentheses are allowed                                             *\n");
    printf("*   - Supported operators: +, -, *, /                                        *\n");
    printf("*   - Spaces between characters are optional                                 *\n");
    printf("******************************************************************************\n");
    printf("* Example Conversions:                                                       *\n");
    printf("*   Input : ./notation-converter --from infix --to postfix \"a+b*c\"           *\n");
    printf("*   Output: a b c * +                                                        *\n");
    printf("*                                                                            *\n");
    printf("*   Input : ./notation-converter --from postfix --to prefix \"a b + c *\"      *\n");
    printf("*   Output: * + a b c                                                        *\n");
    printf("******************************************************************************\n");
    printf("* Common Errors & What They Mean:                                            *\n");
    printf("*                                                                            *\n");
    printf("* Unknown option:                                                            *\n");
    printf("*   You typed a flag that isn't --help, -h, or --guide.                      *\n");
    printf("*   Fix: Only use those options for help.                                    *\n");
    printf("*                                                                            *\n");
    printf("* Incorrect number of arguments:                                             *\n");
    printf("*   You must provide exactly 6 arguments for a conversion.                   *\n");
    printf("*   Fix: ./notation-converter --from infix --to postfix \"a+b\"                *\n");
    printf("*                                                                            *\n");
    printf("* Missing or incorrect --from:                                               *\n");
    printf("*   You forgot to start with --from or misspelled it.                        *\n");
    printf("*   Fix: Make sure --from is the first flag.                                 *\n");
    printf("*                                                                            *\n");
    printf("* Missing or incorrect --to:                                                 *\n");
    printf("*   The --to flag was missing or incorrect.                                  *\n");
    printf("*   Fix: Use --to right after the input format.                              *\n");
    printf("*                                                                            *\n");
    printf("* Invalid format for --from or --to:                                         *\n");
    printf("*   You used an invalid notation format (e.g., 'infx').                      *\n");
    printf("*   Fix: Only use infix, prefix, or postfix.                                 *\n");
    printf("*                                                                            *\n");
    printf("* Failed to build expression tree:                                           *\n");
    printf("*   The program couldn't convert the expression into a tree.                 *\n");
    printf("*   Fix: Check your expression for errors.                                   *\n");
    printf("*                                                                            *\n");
    printf("* Expression cannot end with an operator:                                    *\n");
    printf("*   You ended with an operator like '+'.                                     *\n");
    printf("*   Fix: Make sure expressions end with a variable or number.                *\n");
    printf("*                                                                            *\n");
    printf("* Invalid operator on stack:                                                 *\n");
    printf("*   Detected an unrecognized operator during parsing.                        *\n");
    printf("*   Fix: Use only +, -, *, /                                                 *\n");
    printf("******************************************************************************\n");
}


//return value is the root node
binTree* buildPostfix(const char* expression){
    //insert code here
}
binTree* buildPrefix(const char* expression){
    //code here
}


int precedence(char op);
int isOperator(char c);
int isLeftAssociative(char op);


//using Shunting-Yard algorithm to turn it into a postfix then call buildPostfix to make it into a tree.
binTree* buildInfix(const char* expression) {
    char postfix[1024] = "";         // Stores the postfix expression
    char stack[1024];               // Operator stack
    int top = -1;                   // Top index of stack
    int outIndex = 0;               // Output index

    char token;
    char prev = '\0';

    // Loop through the infix expression
    for (int i = 0; expression[i] != '\0'; i++) {
        token = expression[i];

        if (isspace(token)) continue; // Skip spaces

        if (isdigit(token) || isalpha(token)) {
            // If token is an operand, add to output
            postfix[outIndex++] = token;
            postfix[outIndex++] = ' '; // Space separates tokens
        } 
        else if (isOperator(token)) {
            // While there is an operator at the top with greater or equal precedence
            while (top >= 0 && isOperator(stack[top]) &&
                   ((isLeftAssociative(token) && precedence(token) <= precedence(stack[top])))) {
                postfix[outIndex++] = stack[top--];  // Pop from stack to output
                postfix[outIndex++] = ' ';
            }
            stack[++top] = token; // Push current operator to stack
        }
        prev = token;
    }
        // Check for trailing operator
    if (isOperator(prev)) {
            printf("Error: Expression cannot end with an operator.\n");
            return NULL;
        }

    // Pop any remaining operators
    while (top >= 0) {
        if (!isOperator(stack[top])) {
            printf("Error: Invalid operator on stack.\n");
            return NULL;
        }
        postfix[outIndex++] = stack[top--];
        postfix[outIndex++] = ' ';
    }

    postfix[outIndex] = '\0'; // Null-terminate the output string

    // Call buildPostfix with the resulting postfix expression
    return buildPostfix(postfix);
}

//helper functions for buildInfix
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int isLeftAssociative(char op) {
    return 1; 
}



//print left and right first
void printPostfix(binTree* root) {
    if (root == NULL) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%c ", root->data);
}


//print operation first then left and right
void printPrefix(binTree* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    printPrefix(root->left);
    printPrefix(root->right);
}


//print in first operand then operation then lastly the second operand
void printInfix(binTree* root) {
    if (root == NULL) return;
    // Add parentheses to preserve structure (optional)
    if (root->left || root->right) printf("( ");
    printInfix(root->left);
    printf("%c ", root->data);
    printInfix(root->right);
    if (root->left || root->right) printf(") ");
}
