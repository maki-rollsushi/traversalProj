#include <stdio.h>
#include <string.h>


typedef struct binTree {
    char data;
    struct binTree* left;
    struct binTree* right;
} binTree;



void help(){
    printf("List of Commands\n");
    printf("\n");
}



void preOrder(binTree** tree){
    //make the arithmetic into preOrder
}

void inOrder(binTree** tree){
    //make the arithmetic into inOrder
}

void postOrder(binTree** tree){
    //make the arithmetic into postOrder
}

void printTree(binTree** tree){
    //prints the binary tree
}

void printOrder(binTree** tree){
    //prints the arithmetic based on the users input.
}






//takes an input from the user.
int main(int argc, char* argv[]){

    if(strcmp(argv[1], "--help") == 0){
        help();
    }


    return 0;
}