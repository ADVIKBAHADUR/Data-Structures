#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Tree_Node* newNode(char val)
{
    Tree_Node* new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    new_node->data = val;
    new_node->leftnode = new_node->rightnode = NULL;
    return new_node;
}

void tree_insert(Tree_Node** root, char data) {
    // Check to see if root is empty
    if (*root == NULL) {
        *root = newNode(data);
    } else {
        if (data < (*root)->data) {
            tree_insert(&((*root)->leftnode), data);
        } else {
            tree_insert(&((*root)->rightnode), data);
        }
    }
}

Tree_Node* create_bst(char data[]) {
    Tree_Node* root = NULL;
    int sentinel = 0;
    int len = 0;
    while (sentinel == 0) {
        tree_insert(&root, data[len]);
        len++;
        if (data[len] == '\0') {
            sentinel = 1;
        }
    }
    return root;
}

Tree_Node* tree_search(Tree_Node* root, char data) {
    if (root == NULL) {
        return NULL; // If the root is NULL, the element is not present
    }

    if (data < root->data) {
        return tree_search(root->leftnode, data);
    } else if (data > root->data) {
        return tree_search(root->rightnode, data);
    } else {
        return root;
    }
}

void tree_print_sorted(Tree_Node* root) {
    if (root != NULL) {
        // GO ALL THE WAY DOWN LEFT MOST OF THE ROOT
        tree_print_sorted(root->leftnode);
        printf("%c", root->data);
        // THEN GO ALL THE WAY DOWN THE RIGHT OF THAT NODE
        tree_print_sorted(root->rightnode);
    }
}

void tree_delete(Tree_Node* root) {
    if (root != NULL) {
        // GO ALL THE WAY DOWN LEFT MOST OF THE ROOT
        tree_delete(root->leftnode);
        // THEN GO ALL THE WAY DOWN THE RIGHT OF THAT NODE
        tree_delete(root->rightnode);
        free(root);
    }
}