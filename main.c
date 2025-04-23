#include <stdio.h>
#include <string.h>


typedef struct binTree {
    char data;
    struct binTree* left;
    struct binTree* right;
} binTree;



void help(){
    printf("List of Commands\n");
    printf("jhsfjs\n");
}






int main(int argc, char* argv[]){
    //printf("%s\n", argv[1]);
    //printf("%d\n", argc);

    if(strcmp(argv[1], "--help") == 0){
        help();
    }
    char expression[20];
    strcpy(expression, argv[1]);

    printf("\t%c\n", expression[0]);

    return 0;
}