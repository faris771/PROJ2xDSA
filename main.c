/**
 * AUTHOR:FARIS ABUFARHA
 * ID:1200546
 * SEC:3
 * REPO LINK:https://github.com/faris771/PROJ2xDSA
 * IDE: JETBRAINS CLION
 * COMPILER: gcc
 * OS: LINUX UBUNTU
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
#define MAX_STRING 250
#define MAX_LINE 1000


typedef char String[MAX_STRING];

//  =================================================LIST FUNCTIONS AND STUFF==================================
typedef struct listNode {

    String topic;
    struct listNode *next;


} listNode;

typedef listNode *pNode;


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

    for (i = head; i != null && strcmp(i->next->topic, x) != 0; i = i->next) {

    }

    printf("prev\n");
    return i;

}

void printList(listNode *head) {
    if (isEmptyList(head)) {
        printf("empty List\n");
        return;
    }
    for (listNode *iter = head->next; iter != NULL; iter = iter->next) {
        printf("%s   ", iter->topic);

    }
    printf("\n");
}

void insertAtNodeList(String x, listNode *head, listNode *p) {

    listNode *tmp = malloc(sizeof(listNode));

    strcpy(tmp->topic, x);
    tmp->next = p->next;
    p->next = tmp;

}

void insertAtEndList(String x, listNode *head) {
    listNode *newNode = malloc(sizeof(listNode));
    if (newNode == null) {
        printf("out of memory!\n");
        exit(1);
    }

    strcpy(newNode->topic, x);
    newNode->next = null;

    pNode tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = newNode;
}

void deleteNodeList(String x, listNode *head) {

    bool isLast;

    for (pNode i = head; i->next != null; i = i->next) {

        if (strcmp(i->next->topic, x) == 0) {
            pNode newTmp = null;
            newTmp = i->next;

            i->next = newTmp->next;
            free(newTmp);
            printf("\033[0;32m");
            printf("DELETED\n");
            printf("\033[0m");

            return;

        }

    }
    printf("\033[1;31m"); //GREEN

    printf("TOPIC NOT FOUND !\n");

    printf("\033[0m");


}


listNode *findNodeList(String x, listNode *head) {
    for (listNode *iter = head; iter != NULL; iter = iter->next) {

        if (strcmp(iter->topic, x) == 0) {
            printf("found\n");
            return iter;

        }

    }

    return null;

}

listNode *makeEmptyList(listNode *head) {

    if (head != null) {
        deleteList(head);
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
    String department;
    pNode topicsList;

    pAvl left;
    pAvl right;
    int height; //Balance information


} AVLnode;

void findCharNode(pAvl t, char x, pNode idList) {
    if (t == NULL) {
        return;
    }

    findCharNode(t->left, x, idList);
    if (t->course[0] == x) {


        pNode tmp = malloc(sizeof(listNode));
        strcpy(tmp->topic, t->courseCode);
        tmp->next = idList->next;
        idList->next = tmp;
//        printf("2\n");//1 WORKDS FINE

//            deleteTreeNode(t, t->courseCode);
    }

    findCharNode(t->right, x, idList);


}

void printDep();

pAvl makeEmptyTree(pAvl T) {
    if (T != NULL) {
        makeEmptyTree(T->left);
        makeEmptyTree(T->right);
        free(T);
    }
    return NULL;
}

pAvl findTreeNode(String courseCode, pAvl T) {
    if (T == NULL) {
        return NULL;
    }
    if (strcmp(courseCode, T->courseCode) < 0) {
        return findTreeNode(courseCode, T->left);
    }
    else if (strcmp(courseCode, T->courseCode) > 0) {
        return findTreeNode(courseCode, T->right);
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

int height(pAvl P) {
    if (P == NULL) {
        return -1;
    }
    else {
        return P->height;
    }
}


int max(int Lhs, int Rhs) {
    return Lhs > Rhs ? Lhs : Rhs;
}

pAvl singleRotateWithLeft(pAvl K2) {
    pAvl K1;

    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    K2->height = max(height(K2->left), height(K2->right)) + 1;
    K1->height = max(height(K1->left), K2->height) + 1;

    return K1;  /* New root */
}

pAvl singleRotateWithRight(pAvl K1) {
    pAvl K2;

    K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;

    K1->height = max(height(K1->left), height(K1->right)) + 1;
    K2->height = max(height(K2->right), K1->height) + 1;

    return K2;  /* New root */
}

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

pAvl insert(AVLnode treeNode, pAvl T) {
    if (T == NULL) {
        /* Create and return a one-listNode tree */
        T = malloc(sizeof(AVLnode));

        if (T == NULL) {
            printf("Out of space!!!");
        }

        else {
            //HERE WE ASSIGN THE VALUES
            // TRY W/OUT *

            *T = treeNode;
//            strcpy(T->courseCode, courseCode);
            T->height = 0;
            T->left = T->right = NULL;
        }
    }
    else if (strcmp(treeNode.courseCode, T->courseCode) < 0) {
        T->left = insert(treeNode, T->left);
        if (height(T->left) - height(T->right) == 2) {
            if (strcmp(treeNode.courseCode, T->left->courseCode) < 0) {
                T = singleRotateWithLeft(T);
            }
            else {
                T = doubleRotateWithLeft(T);
            }
        }
    }
    else if (strcmp(treeNode.courseCode, T->courseCode) > 0) {

        T->right = insert(treeNode, T->right);
        if (height(T->right) - height(T->left) == 2) {
            if (strcmp(treeNode.courseCode, T->right->courseCode) > 0) {
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
        fprintf(stdout, "courseCode: %s     course name: %s      creditHours: %d      department: %s       topics: ",
                t->courseCode, t->course, t->creditHours, t->department);
        printList(t->topicsList);
        printInOrder(t->right);
    }
//    printf("\n");
}

int getBalance(pAvl N) {
    if (N == NULL) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

pAvl deleteTreeNode(pAvl root, String courseCode) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL) { // no more nodes

        return root;
    }
    if (strcmp(courseCode, root->courseCode) <
        0) {// if the key we want to save is smaller than current root go to left subtree

        root->left = deleteTreeNode(root->left, courseCode);
    }

    else if (strcmp(courseCode, root->courseCode) >
             0) { //else if the key we want to save is greater than current root go to right subtree
        root->right = deleteTreeNode(root->right, courseCode);

    }
        //else if we find the node we do the deletion

    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {        // node with only one child or no child (NOT A MID NODE)

            pAvl temp = root->left ? root->left : root->right;

            //TMP WILL BE THE NOT NULL NODE THE CHILD OF ROOT

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else { // One child case
                *root = *temp;                          //(NODE) OR THE OPPOSITE
                //                                      /
            } // Copy the contents of               (NODE)
            // the non-empty child
            free(temp);
        }
        else {
            //CASE OF 2 CHILDREN
            // successor (smallest in the right subtree)
            pAvl temp = findMin(root->right);



            // Copy the inorder successor's data to this node
            strcpy(root->courseCode, temp->courseCode);
            strcpy(root->course, temp->course);
            root->creditHours = temp->creditHours;
            strcpy(root->department, temp->department);
            root->topicsList = temp->topicsList;


            // Delete the inorder successor
            root->right = deleteTreeNode(root->right, temp->courseCode);
        }
    }

    // If the tree had only one node then return
    if (root == NULL) {
        return root;
    }

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return singleRotateWithLeft(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = singleRotateWithRight(root->left);
        return singleRotateWithLeft(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return singleRotateWithRight(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = singleRotateWithLeft(root->right);
        return singleRotateWithRight(root);
    }

    return root;
}


// styling
// \033 is the escape sequence  [1;31m is the color

void red() {
    printf("\033[1;31m");
}

void blue() {
    printf("\033[0;34m");

}

void yellow() {
    printf("\033[1;33m");
}

void cyan() {
    printf("\033[0;36m");
}

void green() {
    printf("\033[0;32m");

}

void bold() {
    printf("\033[1;3?m");
}

void reset() {
    printf("\033[0m");
}

void line() {
    bold();
    printf("================================================================\n");
    reset();
}

void welcome() {
    yellow();
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

void memoryMsg() {
    red();
    printf("OUT OF MEMORY!\n");
    reset();
}

char *trimString(char *str) {  //FREE
    size_t len = strlen(str);

    while (isspace(str[len - 1])) --len;
    while (*str && isspace(*str)) ++str, --len;

    return strndup(str, len);
}


pAvl readFile(pAvl root) {
    FILE *in = fopen("courses.txt", "r");
    if (in == null) {
        red();
        printf("CAN'T READ FILE! \n");
        reset();
        return null;
    }
    String leftStr;
    String rightStr;
    String strCourse, strHours, strCourseCode, strDep;
    String HCD;

    pAvl tmpAvlNode = null;

    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, in)) {
        tmpAvlNode = malloc(sizeof(AVLnode));

        if (tmpAvlNode == null) {
            memoryMsg();
            exit(1);
        }
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';

        }
        strcpy(leftStr, strtok(buffer, "/"));//left of '/'
        strcpy(rightStr, strtok(null, "/"));//right

        //left stuff
        strcpy(tmpAvlNode->course, trimString(strtok(leftStr, ":")));
        strcpy(HCD, trimString(strtok(null, ":")));//WORKING

        tmpAvlNode->creditHours = atoi(strtok(HCD, "#"));
        strcpy(tmpAvlNode->courseCode, trimString(strtok(null, "#")));
        strcpy(tmpAvlNode->department, trimString(strtok(null, "#")));
        // loop through the string to extract all other tokens
        tmpAvlNode->topicsList = makeEmptyList(tmpAvlNode->topicsList);
        char *token = strtok(rightStr, ",");
//        printf("topics\n");
        while (token != NULL) {

            //fixes new line in the last segment

            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }

            insertAtEndList(trimString(token), tmpAvlNode->topicsList);
            token = strtok(NULL, ",");
        }
        root = insert(*tmpAvlNode, root);

    }
    fclose(in);
    return root;
}

pAvl secondChoice(pAvl root) {
    String dummyStr;
    int dummyInt;

    pAvl tmpNode = null;
    tmpNode = malloc(sizeof(AVLnode));
    tmpNode->topicsList = makeEmptyList(tmpNode->topicsList);
    if (tmpNode == null) {
        memoryMsg();
    }
    printf("1.PLEASE ENTER THE COURSE CODE YOU WISH TO ADD!\n");
    scanf("%s", dummyStr);
    pAvl testNode = findTreeNode(dummyStr, root);
    if (testNode != null) {
        red();
        printf("COURSE ALREADY EXIST!!\n");
        reset();
        return root;

    }
    strcpy(tmpNode->courseCode, dummyStr);
    printf("2. COURSE NAME:\n");
    fgetc(stdin);
    fgets(dummyStr, MAX_STRING, stdin);
    if (dummyStr[strlen(dummyStr) - 1] == '\n') {
        dummyStr[strlen(dummyStr) - 1] = '\0';

    }


    strcpy(tmpNode->course, dummyStr);
//    fgetc(stdin);
    printf("3. CREDIT HOURS:\n");
    scanf("%d", &dummyInt);
    tmpNode->creditHours = dummyInt;
    fgetc(stdin);

    printf("4. DEPARTMENT:\n");
    fgets(dummyStr, MAX_STRING, stdin);
    if (dummyStr[strlen(dummyStr) - 1] == '\n') {
        dummyStr[strlen(dummyStr) - 1] = '\0';

    }
    strcpy(tmpNode->department, dummyStr);

    String topicsStr;
    while (true) {
        printf("5.PLEASE INPUT TOPICS ONE BY ONE, OR PRESS -1 WHEN YOU ARE DONE\n");
        fflush(stdin);
        fgets(topicsStr, MAX_STRING, stdin);
        if (topicsStr[strlen(topicsStr) - 1] == '\n') {
            topicsStr[strlen(topicsStr) - 1] = '\0';

        }
        if (strcmp(topicsStr, "-1") == 0) {
            break;
        }
        insertAtEndList(topicsStr, tmpNode->topicsList);

    }
    root = insert(*tmpNode, root);
    green();
    printf("COURSE ADDED SUCCESSFULLY!\n");
    reset();

    return root;
}

pAvl thirdChoice(pAvl root) {
    String dummyStr;
    int dummyInt;

    printf("INPUT COURSE CODE YOU'RE LOOKING FOR\n");
    scanf("%s", dummyStr);
    pAvl tmp = null;
    tmp = findTreeNode(dummyStr, root);
    if (tmp == null) {
        red();
        printf("COURSE NOT FOUND!\n");
        reset();
        return root;
    }
    while (true) {

        printf("ENTER 1 TO CHANGE COURSE CODE\n2 TO CHANGE COURSE NAME\n3.CREDIT HOURS\n4.DEPARTMENT\n5.TOPICS LIST \n-1 TO QUIT\n");
        scanf("%d", &dummyInt);
        if (dummyInt == 1) {
            root = deleteTreeNode(root, dummyStr);

            printf("INPUT NEW COURSE CODE\n");
            scanf("%s", dummyStr);
            pAvl newNode = null;
            newNode = malloc(sizeof(AVLnode));
            *newNode = *tmp;
            strcpy(newNode->courseCode, dummyStr);
            root = insert(*newNode, root);


        }

        else if (dummyInt == 2) {
            printf("PLEASE INPUT NEW COURSE NAME\n");
            fgetc(stdin);
            fgets(dummyStr, MAX_STRING, stdin);
            if (dummyStr[strlen(dummyStr) - 1] == '\n') {
                dummyStr[strlen(dummyStr) - 1] = '\0';

            }
            strcpy(tmp->course, dummyStr);

        }
        else if (dummyInt == 3) {
            printf("PLEASE INPUT NEW COURSE CREDIT HOURS\n");
            scanf("%d", &dummyInt);
            tmp->creditHours = dummyInt;

        }
        else if (dummyInt == 4) {
            printf("PLEASE INPUT NEW DEPARTMENT NAME\n");
            fgetc(stdin);
            fgets(dummyStr, MAX_STRING, stdin);
            if (dummyStr[strlen(dummyStr) - 1] == '\n') {
                dummyStr[strlen(dummyStr) - 1] = '\0';

            }
            strcpy(tmp->department, dummyStr);

        }
        else if (dummyInt == 5) {
            int innerInt;
            String innerStr;
            while (true) {
                printf("INPUT\n1. TO ADD NEW TOPIC\n2.DELETE A TOPIC\n3.DELETE ALL TOPICS\n4.EDIT TOPIC\n-2. TO QUIT EDITING TOPICS\n");
                scanf("%d", &innerInt);
                if (innerInt == 1) {
                    printf("INPUT NEW TOPIC\n");
                    fgetc(stdin);
                    fgets(innerStr, MAX_STRING, stdin);
                    if (innerStr[strlen(innerStr) - 1] == '\n') {
                        innerStr[strlen(innerStr) - 1] = '\0';

                    }

                    insertAtEndList(innerStr, tmp->topicsList);


                }
                else if (innerInt == 2) {
                    printf("TOPIC YOU WISH TO DELETE\n");
                    fgetc(stdin);
                    fgets(innerStr, MAX_STRING, stdin);
                    if (innerStr[strlen(innerStr) - 1] == '\n') {
                        innerStr[strlen(innerStr) - 1] = '\0';

                    }
                    deleteNodeList(innerStr, tmp->topicsList);
                }
                else if (innerInt == 3) {
                    deleteList(tmp->topicsList);
                }
                else if (innerInt == 4) {
                    printf("PLEASE INPUT TOPIC YOU WISH TO UPDATE\n");
                    fgetc(stdin);
                    fgets(innerStr, MAX_STRING, stdin);
                    if (innerStr[strlen(innerStr) - 1] == '\n') {
                        innerStr[strlen(innerStr) - 1] = '\0';

                    }
                    pNode tmpTopic = findNodeList(innerStr, tmp->topicsList);
                    if (tmpTopic == null) {
                        red();
                        printf("TOPIC NOT FOUND!\n");
                        reset();
                    }
                    else {
                        String strTmp;
                        printf("ENTER UPDATED TOPIC PLEASE\n");
//                        fgetc(stdin);
                        fgets(strTmp, MAX_STRING, stdin);
                        strcpy(tmpTopic->topic, strTmp);

                    }

                }
                else if (innerInt == -2) {

                    break;

                }
                else {
                    red();
                    printf("INVALID INPUT\n");
                    reset();
                }
            }

            green();
            printf("TOPICS EDITED SUCCESSFULLY\n");
            reset();

        }
        else if (dummyInt == -1) {
            blue();
            printf("CHANGE PHASE ENDED\n");
            reset();
            line();
            break;
        }
        else {
            red();
            printf("INVALID INPUT\n");
            reset();
        }
    }
    return root;
}

void fifhtChoice(pAvl root) {

    String dummyString;
    printf("INPUT COURSE CODE YOU WANT TO SEE ITS LIST\n");
    scanf("%s", dummyString);
    pAvl tmp = null;
    tmp = findTreeNode(dummyString, root);
    if (tmp == null) {
        red();
        printf("course not found\n");
        reset();

        return;

    }
    printList(tmp->topicsList);

}

void printDep(pAvl t, String str) {

    if (t != NULL) {
        printDep(t->left, str);

        if (strcmp(t->department, str) == 0) {
            fprintf(stdout, "courseCode: %s     course name: %s      creditHours: %d      department: %s       topics: ",
                    t->courseCode, t->course, t->creditHours, t->department);
            printList(t->topicsList);

        }
        printDep(t->right, str);

    }
    printf("\n");

}

void sixthChoice(pAvl root) {
    fgetc(stdin);//GETS RID OF NEWLINE

    String tmpDep;
    printf("INPUT DEPARTMENT\n");
    fgets(tmpDep, MAX_STRING, stdin);

    strcpy(tmpDep, trimString(tmpDep));
    if (tmpDep[strlen(tmpDep) - 1] == '\n') {
        tmpDep[strlen(tmpDep) - 1] = '\0';
    }

    printDep(root, tmpDep);

}

pAvl seventhChoice(pAvl root) {

    String dummyStr;
    printf("INPUT CODE YOU WANT TO DELETE \n");
    scanf("%s", dummyStr);

    return deleteTreeNode(root, dummyStr);
    root->topicsList = makeEmptyList(root->topicsList);
    free(root->topicsList);



}


pAvl eightChoice(pAvl root) {
    printf("INPUT THE LETTER PLEASE \n");
    char letter;
    scanf(" %c", &letter);
    pNode tmpID = makeEmptyList(tmpID);

    if (tmpID == null) {
        memoryMsg();
    }
    findCharNode(root, letter, tmpID);


    for (pNode iter = tmpID; iter != null; iter = iter->next) {
        root = deleteTreeNode(root, iter->topic);

    }
    tmpID = makeEmptyList(tmpID);
    free(tmpID);

    return root;
}


void findDepNode(pAvl t, String x, pNode idList) {
    if (t == NULL) {
        return;
    }

    findDepNode(t->left, x, idList);
    if (strcmp(t->department, x) == 0) {
        pNode tmp = malloc(sizeof(listNode));
        strcpy(tmp->topic, t->courseCode);
        tmp->next = idList->next;
        idList->next = tmp;
//        printf("2\n");//1 WORKDS FINE

    }

    findDepNode(t->right, x, idList);


}


pAvl ninthChoice(pAvl root) {

    pNode tmpID = NULL;
    tmpID = makeEmptyList(tmpID);

    fgetc(stdin);
    printf("PLEASE INPUT DEPARTMENT\n");
    String str;
    fgets(str, MAX_STRING, stdin);
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    findDepNode(root, str, tmpID);
    for (pNode iter = tmpID; iter != null; iter = iter->next) {
//        printf("%s\n", iter->topic);
        root = deleteTreeNode(root, iter->topic);

    }
    tmpID = makeEmptyList(tmpID);
    free(tmpID);

    return root;

}

void filePrintInOrder(pAvl t, FILE *out) {

    if (t != NULL) {
        filePrintInOrder(t->left, out);

        fprintf(out,"%s:%d#%s#%s/",
                t->course, t->creditHours,t->courseCode,  t->department);

        listNode *iter= null;
        for (iter = t->topicsList->next; iter->next != NULL; iter = iter->next) {
            fprintf(out, "%s, ", iter->topic);

        }
        fprintf(out, "%s ", iter->topic);

        fprintf(out, "\n");

//        }

        filePrintInOrder(t->right, out);
    }

}

void save(pAvl root) {
    FILE *out = fopen("offered_courses.txt", "w");
    out = freopen(NULL, "w", out); // MAKES THE FILE EMPTY


//    system(":> offered_courses.txt"); FOR LINUX
    if (out == null) {
        red();
        printf("COULDN'T OPEN FILE\n");
        reset();
        return;
    }
    filePrintInOrder(root, out);

    fclose(out);
}

void art() {
    printf("??????????????????????????????????????????????????????????????????????????????????????????\n"
           "???????????????THANK YOU COME AGAIN???????????? ?????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "???\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "??????????????????????????????????????????????????????????????????????????????????????????\n"
           "???????????????????????????????????????????????????????????????????????????????????????\n");

}

void deleteWholeTree(pAvl root) {
    if (root == NULL) {
        return;
    }

    deleteWholeTree(root->left);
    deleteWholeTree(root->right);


    free(root);
    root->topicsList = makeEmptyList(root->topicsList);
    free(root->topicsList);

}


int main() {
    pAvl root = NULL;
    bool isRead = false;


    line();
    welcome();
    line();


    int selection;
    while (true) {
        printf("1. Read the file courses.txt file and create the tree.\n"
               "2. Insert a new course.\n"
               "3. Find a course and support updating of its information.\n"
               "4. List courses in lexicographic order with their associated\n"
               "information (credit hours, IDs, and topics).\n"
               "5. List all topics associated with a given course.\n"
               "6. List all courses in lexicographic order that belong to the same\n"
               "department.\n"
               "7. Delete a course.\n"
               "8. Delete all courses that start with a specific letter.\n"
               "9. Delete all courses belong to a given department.\n"
               "10. Save all words in file offered_courses.txt\n"
               "11. EXIT\n");
        line();

        scanf("%d", &selection);
        switch (selection) {

            case 1:
                if (isRead) {
                    red();
                    printf("FILE ALREADY HAS BEEN READ!\n");
                    reset();
                    line();
                    break;
                }
                makeEmptyTree(root);
                root = readFile(root);
                isRead = true;
                green();
                printf("FILE READ SUCCESSFULLY\n");
                reset();
                line();
                break;
            case 2:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }
                root = secondChoice(root);
                line();
                break;

            case 3:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }
                root = thirdChoice(root);
                break;

            case 4:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }
                printInOrder(root);
                line();
                break;

            case 5:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }

                fifhtChoice(root);
                line();
                break;

            case 6:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }
                sixthChoice(root);
                line();
                break;

            case 7:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }

                root = seventhChoice(root);
                line();


                break;


            case 8:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }

                root = eightChoice(root);
                green();
//                printf("COURSES DELETED SUCCESSFULLY\n");
                reset();
                line();
                break;


            case 9:
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }

                root = ninthChoice(root);
//                green();
//                printf("COURSES DELETED SUCCESSFULLY\n");
//                reset();
                line();
                break;


            case 10 :
                if (!isRead) {
                    red();
                    printf("PLEASE  PRESS 1 FIRST TO READ THE FILE AND MAKE THE TREE :)\n");
                    reset();
                    line();
                    break;
                }

                save(root);
                green();
                printf("FILE SAVED SUCCESSFULLY!\n");
                reset();
                line();
                break;

            case 11:


                bold();
                art();
                reset();
                deleteWholeTree(root); // frees everything
                line();
                return 0;
                break;

            default:
                red();
                printf("INVALID INPUT!\n");
                line();
                reset();


        }

    }


    return 0;
}

