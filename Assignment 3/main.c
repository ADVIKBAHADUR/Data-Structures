#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char name[5] = {'A', 'd', 'v', 'i', 'k'};

    Tree_Node* test;
    test = create_bst(name);

    tree_print_sorted(test);
}