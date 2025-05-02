#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
//binary tree
typedef struct binTree {
    char data;
    struct binTree* left;
    struct binTree* right;
} binTree;

// Stack for tree nodes
typedef struct {
    binTree* items[MAX_STACK_SIZE];
    int top;
} TreeStack;

//functional prototypes
int precedence(char op);
int isOperator(char c);
int isLeftAssociative(char op);

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
            root = buildPostfix(expression);
        }
        else if (strcmp(fromFormat, "prefix") == 0) {
            root = buildPrefix(expression);

        }
        else if (strcmp(fromFormat, "infix") == 0) {
            root = buildInfix(expression);

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
            printf("\n# Output: ");
            printPostfix(root);
            printf("\n\n");
        }
        else if (strcmp(toFormat, "prefix") == 0) {
            printf("\n# Output: ");
            printPrefix(root);
            printf("\n\n");
        }
        else if (strcmp(toFormat, "infix") == 0) {
            printf("\n# Output: ");
            printInfix(root);
            printf("\n\n");
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
    printf("\t******************************************************************************\n");
    printf("\t*                      NOTATION CONVERTER - HELP MENU                        *\n");
    printf("\t******************************************************************************\n");
    printf("\t* USAGE:                                                                     *\n");
    printf("\t*   ./notation-converter --from <input_format> --to <output_format> \"expr\"   *\n");
    printf("\t*                                                                            *\n");
    printf("\t* PARAMETERS:                                                                *\n");
    printf("\t*   <input_format>  : infix | prefix | postfix                               *\n");
    printf("\t*   <output_format> : infix | prefix | postfix                               *\n");
    printf("\t*   \"expr\"         : arithmetic expression (quotes if contains spaces)       *\n");
    printf("\t******************************************************************************\n");
    printf("\t* EXAMPLES:                                                                  *\n");
    printf("\t*   ./notation-converter --from infix --to postfix \"a+b\"                     *\n");
    printf("\t*   ./notation-converter --from prefix --to infix \"+ a b\"                    *\n");
    printf("\t*   ./notation-converter --from postfix --to prefix \"a b +\"                  *\n");
    printf("\t******************************************************************************\n");
    printf("\t* OTHER OPTIONS:                                                             *\n");
    printf("\t*   -h, --help   : Display this help menu                                    *\n");
    printf("\t*   --guide      : Show full user guide with rules, details, and examples    *\n");
    printf("\t******************************************************************************\n");
}


void guide() {
    printf("\t******************************************************************************\n");
    printf("\t*                                                                            *\n");
    printf("\t*                  NOTATION CONVERTER CLI GUIDE                              *\n");
    printf("\t*                                                                            *\n");
    printf("\t******************************************************************************\n");
    printf("\t* This section is dedicated as the guide for the project:                    *\n");
    printf("\t* Notation Converter CLI                                                     *\n");
    printf("\t******************************************************************************\n");
    printf("\t* What this program does:                                                    *\n");
    printf("\t*   This tool converts an arithmetic expression from one notation            *\n");
    printf("\t*   (infix, prefix, or postfix) to another by:                               *\n");
    printf("\t*     - Parsing the expression                                               *\n");
    printf("\t*     - Building an expression tree                                          *\n");
    printf("\t*     - Printing the tree in the desired output format                       *\n");
    printf("\t******************************************************************************\n");
    printf("\t* HOW TO RUN THE PROGRAM:                                                    *\n");
    printf("\t*   ./notation-converter --from <input_format> --to <output_format> \"expr\"   *\n");
    printf("\t*   <input_format>  : infix | prefix | postfix                               *\n");
    printf("\t*   <output_format> : infix | prefix | postfix                               *\n");
    printf("\t*   \"expression\"   : The expression in quotes (esp. if it has spaces)        *\n");
    printf("\t******************************************************************************\n");
    printf("\t* Supported Formats:                                                         *\n");
    printf("\t*   Infix   : a + b                                                          *\n");
    printf("\t*     Ex. ./notation-converter --from infix --to postfix \"a+b\"               *\n");
    printf("\t*   Prefix  : + a b                                                          *\n");
    printf("\t*     Ex. ./notation-converter --from prefix --to postfix \"+ a b\"            *\n");
    printf("\t*   Postfix : a b +                                                          *\n");
    printf("\t*     Ex. ./notation-converter --from postfix --to infix \"a b +\"             *\n");
    printf("\t******************************************************************************\n");
    printf("\t* Expression Rules:                                                          *\n");
    printf("\t*   - Use only single-digit numbers or single-letter variables               *\n");
    printf("\t*   - No parentheses are allowed                                             *\n");
    printf("\t*   - Supported operators: +, -, *, /                                        *\n");
    printf("\t*   - Spaces between characters are optional                                 *\n");
    printf("\t******************************************************************************\n");
    printf("\t* Example Conversions:                                                       *\n");
    printf("\t*   Input : ./notation-converter --from infix --to postfix \"a+b*c\"           *\n");
    printf("\t*   Output: a b c * +                                                        *\n");
    printf("\t*                                                                            *\n");
    printf("\t*   Input : ./notation-converter --from postfix --to prefix \"a b + c *\"      *\n");
    printf("\t*   Output: * + a b c                                                        *\n");
    printf("\t******************************************************************************\n");
    printf("\t* Common Errors & What They Mean:                                            *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Unknown option:                                                            *\n");
    printf("\t*   You typed a flag that isn't --help, -h, or --guide.                      *\n");
    printf("\t*   Fix: Only use those options for help.                                    *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Incorrect number of arguments:                                             *\n");
    printf("\t*   You must provide exactly 6 arguments for a conversion.                   *\n");
    printf("\t*   Fix: ./notation-converter --from infix --to postfix \"a+b\"                *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Missing or incorrect --from:                                               *\n");
    printf("\t*   You forgot to start with --from or misspelled it.                        *\n");
    printf("\t*   Fix: Make sure --from is the first flag.                                 *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Missing or incorrect --to:                                                 *\n");
    printf("\t*   The --to flag was missing or incorrect.                                  *\n");
    printf("\t*   Fix: Use --to right after the input format.                              *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Invalid format for --from or --to:                                         *\n");
    printf("\t*   You used an invalid notation format (e.g., 'infx').                      *\n");
    printf("\t*   Fix: Only use infix, prefix, or postfix.                                 *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Failed to build expression tree:                                           *\n");
    printf("\t*   The program couldn't convert the expression into a tree.                 *\n");
    printf("\t*   Fix: Check your expression for errors.                                   *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Expression cannot end with an operator:                                    *\n");
    printf("\t*   You ended with an operator like '+'.                                     *\n");
    printf("\t*   Fix: Make sure expressions end with a variable or number.                *\n");
    printf("\t*                                                                            *\n");
    printf("\t* Invalid operator on stack:                                                 *\n");
    printf("\t*   Detected an unrecognized operator during parsing.                        *\n");
    printf("\t*   Fix: Use only +, -, *, /                                                 *\n");
    printf("\t******************************************************************************\n\n");
}
// Helper function to create a new tree node


void initStack(TreeStack* s) {
    s->top = -1;
}

int isEmpty(TreeStack* s) {
    return s->top == -1;
}

int isFull(TreeStack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(TreeStack* s, binTree* node) {
    if (!isFull(s)) {
        s->items[++(s->top)] = node;
    } else {
        printf("Error: Stack overflow.\n");
    }
}

binTree* pop(TreeStack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Error: Stack underflow.\n");
        return NULL;
    }
}

binTree* createNode(char data) {
    binTree* node = (binTree*)malloc(sizeof(binTree));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Return the root of the built expression tree
binTree* buildPostfix(const char* expression) {
    TreeStack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; ++i) {
        char token = expression[i];

        if (isspace(token)) continue;

        if (isalnum(token)) {
            // Operand
            binTree* operand = createNode(token);
            push(&stack, operand);
        } else if (isOperator(token)) {
            // Operator
            binTree* node = createNode(token);

            // Right and left operands must be popped
            binTree* right = pop(&stack);
            binTree* left = pop(&stack);

            if (!left || !right) {
                printf("Error: Invalid postfix expression.\n");
                return NULL;
            }

            node->left = left;
            node->right = right;

            push(&stack, node);
        } else {
            printf("Error: Invalid character '%c' in expression.\n", token);
            return NULL;
        }
    }

    // At the end, stack should have only one item (the root)
    if (stack.top != 0) {
        printf("Error: Malformed expression, remaining elements in stack.\n");
        return NULL;
    }

    return pop(&stack);
}



// Assumes binTree, createNode, isOperator are already defined

// Recursive helper for prefix parsing
binTree* buildFromPrefix(const char** expression) {
    while (**expression == ' ') (*expression)++;  // skip spaces

    if (**expression == '\0') {
        fprintf(stderr, "Error: Unexpected end of expression.\n");
        return NULL;
    }

    char c = **expression;
    (*expression)++;  // advance past current character

    if (!isOperator(c) && !isalnum(c)) {
        fprintf(stderr, "Error: Invalid character '%c' in expression.\n", c);
        return NULL;
    }

    binTree* node = createNode(c);

    if (isOperator(c)) {
        node->left = buildFromPrefix(expression);
        if (!node->left) {
            fprintf(stderr, "Error: Missing left operand for operator '%c'.\n", c);
            return NULL;
        }

        node->right = buildFromPrefix(expression);
        if (!node->right) {
            fprintf(stderr, "Error: Missing right operand for operator '%c'.\n", c);
            return NULL;
        }
    }

    return node;
}

binTree* buildPrefix(const char* expression) {
    return buildFromPrefix(&expression);
}



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
