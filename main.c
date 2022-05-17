/**
 * AUTHOR:FARIS ABUFARHA
 * ID:1200546
 * github:https://github.com/faris771
 * IDE: JETBRAINS CLION
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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

#define null NULL
#define MAX_STRING 100
#define MAX_LINE 4095

typedef char String[MAX_STRING];

//  =================================================LIST FUNCTIONS AND STUFF==================================
typedef struct listNode {


    String topic;
    struct listNode *next;


} listNode;


bool isEmptyList(listNode *head) {
    if (head->next == null) {

        return true;

    }
    else {
        return false;
    }


}

//n is a pointer to our wanted listNode
bool isLastList(listNode *n, listNode *head) {

    return n->next == null;

}


int sizeOfList(listNode *head) {

    int cnt = 0;
    for (listNode *iter = head->next; iter != NULL; iter = iter->next) {
        cnt++;
    }


    return cnt;

}

void deleteList(listNode *head) {
    listNode *tmp = null;
    for (listNode *iter = head->next; iter != NULL;) {

        tmp = iter;
        iter = iter->next;
        tmp->next = null;
        free(tmp);

    }

    head->next = null;

}

listNode *findPrevNodeList(String x, listNode *head) {
    listNode *i = null;

    for (i = head; i != null && strcmp(i->next->topic, x)!=0; i = i->next) {

    }


    return i;


}

void printList(listNode *head) {
    if (isEmptyList(head)) {
        printf("empty List\n");
        return;
    }
    for (listNode *iter = head->next; iter != NULL; iter = iter->next) {
        printf("%s ", iter->topic);

    }
    printf("\n");
}


void insertAtNodeList(String x, listNode *head, listNode *p) {

    listNode *tmp = malloc(sizeof(listNode));

    strcpy(tmp->topic, x);
    tmp->next = p->next;
    p->next = tmp;

//    free(tmp);
}

void insertAtBeginningList(String x, listNode *head) {
    listNode *tmp = malloc(sizeof(listNode));
    strcpy(tmp->topic , x);
    tmp->next = head->next;

    head->next = tmp;

//    free(tmp);

}

void deleteNodeList(String x, listNode *head) {

//    for (listNode *i = head;i!= null && i;  < ; ++) {
//
//    }
    listNode *tmp = null;

    listNode *prev = findPrevNodeList(x, head);
    if (!isLastList(prev, head)) {
        tmp = prev->next;
        prev->next = tmp->next;
        free(tmp);


    }


}


listNode *findNodeList(String x, listNode *head) {

//    listNode *i = null;
//    i = head->next;
//
//    while (i != null && i->topic != x) {
//        i = i->next;
//
//        if (i->topic == x){
//            printf("found!\n");
//            return i;
//        }
//    }
//
//    printf("not found\n");
    for (listNode *iter = head->next; iter != NULL; iter = iter->next) {
        if (strcmp(iter->topic , x) ==0) {
            printf("found\n");
            return iter;

        }

    }


}


// give it a listNode ptr, and let it the head by making it pointing into a listNode
listNode *makeEmptyList(listNode *head) {

    if (head != null) {
        //delete list

    }
    head = malloc(sizeof(listNode));
    head->next = null;


    return head;


}


//  =================================================TREE FUNCTIONS AND STUFF==================================
typedef struct AVLnode *pAvl;

typedef struct AVLnode {

    String courseCode;//key
    String course;
    int creditHours;
    String topics;

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

pAvl find(String courseCode, pAvl T) {
    if (T == NULL) {
        return NULL;
    }
    if (strcmp(courseCode, T->courseCode) < 0) {
        return find(courseCode, T->left);
    }
    else if (strcmp(courseCode, T->courseCode) > 0) {
        return find(courseCode, T->right);
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
/* Perform a rotate between a listNode (K2) and its left child */
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
/* Perform a rotate between a listNode (K1) and its right child */
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
//ADD THE NEW ARGUMENTS
pAvl insert(String courseCode, pAvl T) {
    if (T == NULL) {
        /* Create and return a one-listNode tree */
        T = malloc(sizeof(AVLnode));
        if (T == NULL) {
            printf("Out of space!!!");
        }
        else {
            //HERE WE ASSIGN THE VALUES
            strcpy(T->courseCode, courseCode);
            T->height = 0;
            T->left = T->right = NULL;
        }
    }
    else if (strcmp(courseCode, T->courseCode) < 0) {
        T->left = insert(courseCode, T->left);
        if (height(T->left) - height(T->right) == 2) {
            if (strcmp(courseCode, T->left->courseCode) < 0) {
                T = singleRotateWithLeft(T);
            }
            else {
                T = doubleRotateWithLeft(T);
            }
        }
    }
    else if (strcmp(courseCode, T->courseCode) > 0) {

        T->right = insert(courseCode, T->right);
        if (height(T->right) - height(T->left) == 2) {
            if (strcmp(courseCode, T->right->courseCode) > 0) {
                T = singleRotateWithRight(T);
            }
            else {
                T = doubleRotateWithRight(T);
            }
        }
    }
    /* Else courseCode is in the tree already; we'll do nothing */

    T->height = max(height(T->left), height(T->right)) + 1;
    return T;
}
/* END */

//in-order print to see the elements

//EDIT IF NEEDED MORE DETAILS!!
void printInOrder(pAvl t) {
    if (t != NULL) {
        printInOrder(t->left);
        printf("%s\t", t->courseCode);
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

void cyan() {
    printf("\\033[0;36m\n");
}

void reset() {
    printf("\033[0m");
}

void line() {
    printf("================================================================\n");
}

void welcome() {
    cyan();
    printf("                 _                              \n"
           "                | |                             \n"
           " __      __ ___ | |  ___  ___   _ __ ___    ___ \n"
           " \\ \\ /\\ / // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\\n"
           "  \\ V  V /|  __/| || (__| (_) || | | | | ||  __/\n"
           "   \\_/\\_/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|\n"
           "                                                \n"
           "                                                \n");

    reset();

}


int main() {

    pAvl tree;
    tree = makeEmpty(tree);

    //the same sequence of inderting elements in the example
    tree = insert("1", tree);
    tree = insert("2", tree);
//    tree = insert(3, tree);
//    tree = insert(4, tree);
//    tree = insert(5, tree);
//    tree = insert(6, tree);
//    tree = insert(7, tree);
//    tree = insert(16, tree);
//    tree = insert(15, tree);
//    tree = insert(14, tree);
//    tree = insert(13, tree);
//    tree = insert(12, tree);
//    tree = insert(11, tree);
//    tree = insert(10, tree);

    printf("Test to print the tree (In-Order):\n");
    printInOrder(tree);

    return 0;
}

