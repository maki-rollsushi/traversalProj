#include <stdio.h>
#include <string.h>

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

void printHelp();
void printGuide();



//takes an input from the user.
int main(int argc, char* argv[]) {
    if (argc == 2) { // Only 2 arguments, might be --help or --guide
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            help();
            return 0;
        }
        else if (strcmp(argv[1], "--guide") == 0) {
            guide();
            return 0;
        }
        else {
            printf("Error: Unknown option. Use -h or --help.\n");
            return 1;
        }
    }
    else if (argc == 6) { 
        // Expected input: ./program "expression" --from X --to Y
        char* expression = argv[1];
        char* fromFormat = NULL;
        char* toFormat = NULL;

        // Read the --from and --to arguments
        if (strcmp(argv[2], "--from") == 0) {
            fromFormat = argv[3];
        }
        else {
            printf("Error: Missing or incorrect --from argument.\n");
            return 1;
        }

        if (strcmp(argv[4], "--to") == 0) {
            toFormat = argv[5];
        }
        else {
            printf("Error: Missing or incorrect --to argument.\n");
            return 1;
        }

        // Build the expression tree
        binTree* root = NULL;

        if (strcmp(fromFormat, "postfix") == 0) {
            root = buildFromPostfix(expression);
        }
        else if (strcmp(fromFormat, "prefix") == 0) {
            root = buildFromPrefix(expression);
        }
        else if (strcmp(fromFormat, "infix") == 0) {
            root = buildFromInfix(expression);
        }
        else {
            printf("Error: Invalid format for --from. Must be infix, prefix, or postfix.\n");
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
            printf("Error: Invalid format for --to. Must be infix, prefix, or postfix.\n");
            return 1;
        }
    }
    else {
        printf("Error: Incorrect number of arguments. Use -h or --help for usage.\n");
        return 1;
    }

    return 0;
}

//return value is the root node
binTree* buildPostfix(const char* expression){
    //insert code here
}
binTree* buildPrefix(const char* expression){
    //code here
}
binTree* buildInfix(const char* expression){
    //code
}


//prints the output based on the input --to
void printPostfix(binTree* root){
    //here
}
void printPrefix(binTree* root){
    //here
}
void printInfix(binTree* root){
    //here
}  