    /* Programming Project 1: Notation-Converter CLI
    *  Subject: CS 110 - Discrete Structures 2
    *  Course and Bloc: BSCS 2A
    *  Project Members:
    *      Dela Cruz, Mark L.
    *      Gamis, Shana Aislinn
    *      Tabayag, Xaris Joy
    */



    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdlib.h>

    #define MAX 100

    // ------------------ Type Definitions ------------------
    typedef struct binTree {
        char data;
        struct binTree* left;
        struct binTree* right;
    } binTree;

    typedef struct {
        binTree* items[MAX];
        int top;
    } TreeStack;
    
    typedef enum {
        FORMAT_HELP, 
        FORMAT_GUIDE, 
        FORMAT_INVALID, 
        FORMAT_INFIX, 
        FORMAT_PREFIX, 
        FORMAT_POSTFIX 
    } Format;

    // ------------------ Stack Operations ------------------

    void initStack(TreeStack* s) { s->top = -1; }
    int isEmpty(TreeStack* s) { return s->top == -1; }
    int isFull(TreeStack* s) { return s->top == MAX - 1; }

    void push(TreeStack* s, binTree* node) {
        if (!isFull(s)) s->items[++(s->top)] = node;
        else printf("Error: Stack overflow.\n");
    }

    binTree* pop(TreeStack* s) {
        if (!isEmpty(s)) return s->items[(s->top)--];
        printf("Error: Stack underflow.\n");
        return NULL;
    }

    // ------------------ Tree Utilities ------------------
    binTree* createNode(char data) {
        binTree* node = (binTree*)malloc(sizeof(binTree));
        node->data = data;
        node->left = node->right = NULL;
        return node;
    }

    void freeTree(binTree* root) {
        if (!root) return;
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }

    // ------------------ Helper Functions ------------------
    int strEquals(const char* a, const char* b) { return strcmp(a, b) == 0; }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
    int isLeftAssociative(char op) { return 1; }

    Format parseFormat(const char* str) {
        if (strEquals(str, "--h") || strEquals(str, "--help")) return FORMAT_HELP;
        if (strEquals(str, "--guide")) return FORMAT_GUIDE;
        if (strEquals(str, "infix")) return FORMAT_INFIX;
        if (strEquals(str, "prefix")) return FORMAT_PREFIX;
        if (strEquals(str, "postfix")) return FORMAT_POSTFIX;
        return FORMAT_INVALID;
    }

    // ------------------ Tree Builders ------------------
    binTree* buildPostfix(const char* expression) {
        TreeStack stack;
        initStack(&stack);
        for (int i = 0; expression[i] != '\0'; ++i) {
            char token = expression[i];
            if (isspace(token)) continue;    
            if (isalnum(token)) {             
                binTree* operand = createNode(token);
                push(&stack, operand);
            } else if (isOperator(token)) {
                binTree* node = createNode(token);
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
        if (stack.top != 0) {
            printf("Error: Malformed expression, remaining elements in stack.\n");
            return NULL;
        }
        return pop(&stack);
    }

    binTree* buildPrefix(const char** expression) {
        while (isspace(**expression)) (*expression)++;  // skip spaces
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
            node->left = buildPrefix(expression);
            if (!node->left) {
                fprintf(stderr, "Error: Missing left operand for operator '%c'.\n", c);
                return NULL;
            }
            node->right = buildPrefix(expression);
            if (!node->right) {
                fprintf(stderr, "Error: Missing right operand for operator '%c'.\n", c);
                return NULL;
            }
        }
        return node;
    }

    binTree* buildInfix(const char* expression) {
        char postfix[100] = "";        
        char stack[100];              
        int top = -1;                   
        int outIndex = 0;          
        char token;
        char prev = '\0';
        for (int i = 0; expression[i] != '\0'; i++) {
            token = expression[i];
            if (isspace(token)) continue; 
            if (isalnum(token)) {
                postfix[outIndex++] = token;
                postfix[outIndex++] = ' ';
            } 
            else if (isOperator(token)) {
                while (top >= 0 && isOperator(stack[top]) &&
                    (precedence(token) <= precedence(stack[top]))) {
                    postfix[outIndex++] = stack[top--];  
                    postfix[outIndex++] = ' ';
                }
                stack[++top] = token;
            }
            prev = token;
        }
        if (isOperator(prev)) {
                printf("Error: Expression cannot end with an operator.\n");
                return NULL;
            }
        while (top >= 0) {
            if (!isOperator(stack[top])) {
                printf("Error: Invalid operator on stack.\n");
                return NULL;
            }
            postfix[outIndex++] = stack[top--];
            postfix[outIndex++] = ' ';
        }
        postfix[outIndex] = '\0'; 
        return buildPostfix(postfix);
    }

    // ------------------ Print Functions ------------------
    void printPostfix(binTree* root) {
        if (!root) return;
        printPostfix(root->left);
        printPostfix(root->right);
        printf("%c ", root->data);
    }

    void printPrefix(binTree* root) {
        if (!root) return;
        printf("%c ", root->data);
        printPrefix(root->left);
        printPrefix(root->right);
    }

    void printInfix(binTree* root) {
        if (!root) return;
        if (root->left || root->right) printf("( ");
        printInfix(root->left);
        printf("%c ", root->data);
        printInfix(root->right);
        if (root->left || root->right) printf(") ");
    }

    // ------------------ Help & Guide ------------------
    void help() {
        printf("\n\n\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t*                      NOTATION CONVERTER - HELP MENU                        *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* USAGE:                                                                     *\n");
        printf("\t* For Linux:                                                                 *\n");
        printf("\t*    ./notation-converter --from <input_format> --to <output_format> \"expr\"  *\n");
        printf("\t*                                                                            *\n");
        printf("\t* For Windows:                                                               *\n");
        printf("\t*    notation-converter --from <input_format> --to <output_format> \"expr\"    *\n");
        printf("\t*                                                                            *\n");
        printf("\t* PARAMETERS:                                                                *\n");
        printf("\t*   <input_format>  : infix | prefix | postfix                               *\n");
        printf("\t*   <output_format> : infix | prefix | postfix                               *\n");
        printf("\t*   \"expr\"         : arithmetic expression (quotes if contains spaces)       *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* EXAMPLES:                                                                  *\n");
        printf("\t* Linux:                                                                     *\n");
        printf("\t*   ./notation-converter --from infix --to postfix \"a+b\"                     *\n");
        printf("\t*   ./notation-converter --from prefix --to infix \"+ a b\"                    *\n");
        printf("\t*   ./notation-converter --from postfix --to prefix \"a b +\"                  *\n");
        printf("\t*                                                                            *\n");
        printf("\t* Windows:                                                                   *\n");
        printf("\t*   notation-converter --from infix --to postfix \"a+b\"                       *\n");
        printf("\t*   notation-converter --from prefix --to infix \"+ a b\"                      *\n");
        printf("\t*   notation-converter --from postfix --to prefix \"a b +\"                    *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* OTHER OPTIONS:                                                             *\n");
        printf("\t*   notation -convetver --h   :   Display this help menu                     *\n");
        printf("\t*   notation-converter --help :   Display this help menu                     *\n");
        printf("\t*   notation-converter --guide:   Show full user guide with                  *\n");
        printf("\t*                                 rules, details, and examples               *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n\n\n");
    }


    void guide() {
        printf("\n\n\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t*                  NOTATION CONVERTER CLI GUIDE                              *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* This section is dedicated as the guide for the project:                    *\n");
        printf("\t* Notation Converter CLI                                                     *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* What this program does:                                                    *\n");
        printf("\t*   This tool converts an arithmetic expression from one notation            *\n");
        printf("\t*   (infix, prefix, or postfix) to another by:                               *\n");
        printf("\t*     - Parsing the expression                                               *\n");
        printf("\t*     - Building an expression tree                                          *\n");
        printf("\t*     - Printing the tree in the desired output format                       *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* HOW TO RUN THE PROGRAM:                                                    *\n");
        printf("\t* For Linux:                                                                 *\n");
        printf("\t*   ./notation-converter --from <input_format> --to <output_format> \"expr\"   *\n");
        printf("\t*                                                                            *\n");
        printf("\t* For Windows:                                                               *\n");
        printf("\t*   notation-converter --from <input_format> --to <output_format> \"expr\"     *\n");
        printf("\t*                                                                            *\n");
        printf("\t* Definitions:                                                               *\n");
        printf("\t*   <input_format>  : infix | prefix | postfix                               *\n");
        printf("\t*   <output_format> : infix | prefix | postfix                               *\n");
        printf("\t*   \"expression\"   : The expression in quotes (esp. if it has spaces)        *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* Supported Formats:                                                         *\n");
        printf("\t*   Infix   : a + b                                                          *\n");
        printf("\t*     Ex. ./notation-converter --from infix --to postfix \"a+b\"               *\n");
        printf("\t*   Prefix  : + a b                                                          *\n");
        printf("\t*     Ex. ./notation-converter --from prefix --to postfix \"+ a b\"            *\n");
        printf("\t*   Postfix : a b +                                                          *\n");
        printf("\t*     Ex. ./notation-converter --from postfix --to infix \"a b +\"             *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* Expression Rules:                                                          *\n");
        printf("\t*   - Use only single-digit numbers or single-letter variables               *\n");
        printf("\t*   - No parentheses are allowed                                             *\n");
        printf("\t*   - Supported operators: +, -, *, /                                        *\n");
        printf("\t*   - Spaces between characters are optional                                 *\n");
        printf("\t*   - Must use quotations \"a + b\" when including spaces                      *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* Example Conversions:                                                       *\n");
        printf("\t*   Input : ./notation-converter --from infix --to postfix \"a+b*c\"           *\n");
        printf("\t*   # Output: a b c * +                                                      *\n");
        printf("\t*                                                                            *\n");
        printf("\t*   Input : ./notation-converter --from postfix --to prefix \"a b + c *\"      *\n");
        printf("\t*   # Output: * + a b c                                                      *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n");
        printf("\t*                                                                            *\n");
        printf("\t* Common Errors & What They Mean:                                            *\n");
        printf("\t*                                                                            *\n");
        printf("\t* Unknown option:                                                            *\n");
        printf("\t*   You typed a flag that isn't --help, --h, or --guide.                     *\n");
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
        printf("\t* Expression cannot end with an operator (for infix):                        *\n");
        printf("\t*   You ended with an operator like '+'.                                     *\n");
        printf("\t*   Fix: Make sure expressions end with a variable or number.                *\n");
        printf("\t*                                                                            *\n");
        printf("\t* Invalid operator on stack:                                                 *\n");
        printf("\t*   Detected an unrecognized operator during parsing.                        *\n");
        printf("\t*   Fix: Use only +, -, *, /                                                 *\n");
        printf("\t*                                                                            *\n");
        printf("\t******************************************************************************\n\n");
    }

    // ------------------ Conversion Logic ------------------
    int processConversion(const char* fromStr, const char* toStr, const char* expression) {
        Format from = parseFormat(fromStr);
        Format to = parseFormat(toStr);
        binTree* root = NULL;

        switch (from) {
            case FORMAT_INFIX: root = buildInfix(expression); break;
            case FORMAT_PREFIX: {
                const char* exprPtr = expression;
                root = buildPrefix(&exprPtr); break;
            }
            case FORMAT_POSTFIX: root = buildPostfix(expression); break;
            default:
                fprintf(stderr, "Error: Invalid input format.\n");
                return 1;
        }

        if (!root) {
            fprintf(stderr, "Error: Failed to build expression tree.\n");
            return 1;
        }

        printf("\n# Output: ");
        switch (to) {
            case FORMAT_INFIX: printInfix(root); break;
            case FORMAT_PREFIX: printPrefix(root); break;
            case FORMAT_POSTFIX: printPostfix(root); break;
            default:
                fprintf(stderr, "Error: Invalid output format.\n");
                return 1;
        }
        printf("\n\n");
        freeTree(root);
        return 0;
    }

    // ------------------ Main Function ------------------
    int main(int argc, char* argv[]) {
        if (argc == 2) {
            Format manual = parseFormat(argv[1]); 
            switch(manual) {
                case FORMAT_HELP: help(); break;
                case FORMAT_GUIDE: guide(); break;
                default:
                    printf("Error: Incorrect arguments. Use --help for usage.\n");
                    return 1; 
            }    
        } else if (argc == 6 && strEquals(argv[1], "--from") && strEquals(argv[3], "--to")) {
            return processConversion(argv[2], argv[4], argv[5]);
        } else {
            printf("Error: Incorrect arguments. Input \"notation-converter --help\" for usage.\n ");
            return 1;
        }
        return 0;
    }
