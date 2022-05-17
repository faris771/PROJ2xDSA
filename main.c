#include <stdlib.h>
#include <stdio.h>




/*
 *
 *        Color Codes
Black: \033[0;30m
Red: \033[0;31m
Green: \033[0;32m
Yellow: \033[0;33m
Blue: \033[0;34m
Magenta: \033[0;35m
Cyan: \033[0;36m
White: \033[0;37m
        Style
Normal: \033[0;3?m
Bold:   \033[1;3?m
Reset: \033[0m
*/

typedef char String[100];


#define null NULL




//Radi version, but edited


typedef struct AVLnode *pAvl;

typedef struct AVLnode {
    //key
    String courseCode;
    String course;
    int creditHours;




    pAvl left;
    pAvl right;
    int height; //Balance information




} AVLnode;

pAvl makeEmpty(pAvl T) {
    if (T != NULL) {
        makeEmpty(T->left);
        makeEmpty(T->right);
        free(T);
    }
    return NULL;
}

pAvl find(int X, pAvl T) {
    if (T == NULL) {
        return NULL;
    }
    if (X < T->courseCode) {
        return find(X, T->left);
    }
    else if (X > T->courseCode) {
        return find(X, T->right);
    }
    else {
        return T;
    }
}

pAvl findMin(pAvl T) {
    if (T == NULL) {
        return NULL;
    }
    else if (T->left == NULL) {
        return T;
    }
    else {
        return findMin(T->left);
    }
}

pAvl findMax(pAvl T) {
    if (T != NULL) {
        while (T->right != NULL) { // iterative faster than recursive
            T = T->right;
        }
    }

    return T; // if it's null will return null
}

/* START: fig4_36.txt */


int height(pAvl P) {
    if (P == NULL) {
        return -1;
    }
    else {
        return P->height;
    }
}

/* END */

int max(int Lhs, int Rhs) {
    return Lhs > Rhs ? Lhs : Rhs;
}

/* START: fig4_39.txt */
/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

pAvl singleRotateWithLeft(pAvl K2) {
    pAvl K1;

    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    K2->height = max(height(K2->left), height(K2->right)) + 1;
    K1->height = max(height(K1->left), K2->height) + 1;

    return K1;  /* New root */
}


/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

pAvl singleRotateWithRight(pAvl K1) {
    pAvl K2;

    K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;

    K1->height = max(height(K1->left), height(K1->right)) + 1;
    K2->height = max(height(K2->right), K1->height) + 1;

    return K2;  /* New root */
}

/* START: fig4_41.txt */
/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

pAvl doubleRotateWithLeft(pAvl K3) {
    /* Rotate between K1 and K2 */
    K3->left = singleRotateWithRight(K3->left);

    /* Rotate between K3 and K2 */
    return singleRotateWithLeft(K3);
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

pAvl doubleRotateWithRight(pAvl K1) {
    /* Rotate between K3 and K2 */
    K1->right = singleRotateWithLeft(K1->right);

    /* Rotate between K1 and K2 */
    return singleRotateWithRight(K1);
}


/* START: fig4_37.txt */
pAvl insert(int X, pAvl T) {
    if (T == NULL) {
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct AVLnode));
        if (T == NULL) {
            printf("Out of space!!!");
        }
        else {
//            T->courseCode = X;
            T->height = 0;
            T->left = T->right = NULL;
        }
    }
    else if (X < T->courseCode) {
        T->left = insert(X, T->left);
        if (height(T->left) - height(T->right) == 2) {
            if (X < T->left->courseCode) {
                T = singleRotateWithLeft(T);
            }
            else {
                T = doubleRotateWithLeft(T);
            }
        }
    }
    else if (X > T->courseCode) {

        T->right = insert(X, T->right);
        if (height(T->right) - height(T->left) == 2) {
            if (X > T->right->courseCode) {
                T = singleRotateWithRight(T);
            }
            else {
                T = doubleRotateWithRight(T);
            }
        }
    }
    /* Else X is in the tree already; we'll do nothing */

    T->height = max(height(T->left), height(T->right)) + 1;
    return T;
}
/* END */

//in-order print to see the elements
void printInOrder(pAvl t) {
    if (t != NULL) {
        printInOrder(t->left);
        printf("%d\t", t->courseCode);
        printInOrder(t->right);
    }
}

// styling
// \033 is the escape sequence  [1;31m is the color

void red() {
    printf("\033[1;31m");
}

void yellow() {
    printf("\033[1;33m");
}

void reset() {
    printf("\033[0m");
}


int main() {

    pAvl tree;
    tree = makeEmpty(tree);

    //the same sequence of inderting elements in the example
    tree = insert(1, tree);
    tree = insert(2, tree);
    tree = insert(3, tree);
    tree = insert(4, tree);
    tree = insert(5, tree);
    tree = insert(6, tree);
    tree = insert(7, tree);
    tree = insert(16, tree);
    tree = insert(15, tree);
    tree = insert(14, tree);
    tree = insert(13, tree);
    tree = insert(12, tree);
    tree = insert(11, tree);
    tree = insert(10, tree);

    printf("Test to print the tree (In-Order):\n");
    printInOrder(tree);

    return 0;
}

