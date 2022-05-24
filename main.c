/**
 * AUTHOR:FARIS ABUFARHA
 * ID:1200546
 * github:https://github.com/faris771
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

//    for (listNode *i = head;i!= null && i;  < ; ++) {
//
//    }
    listNode *tmp = null;

    listNode *prevNode = findPrevNodeList(x, head);
    if (!isLastList(prevNode, head)) {
        tmp = prevNode->next;
        prevNode->next = tmp->next;
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
        if (strcmp(iter->topic, x) == 0) {
            printf("found\n");
            return iter;

        }

    }

    return null;

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

        printf("%s\n", t->courseCode);
//            insertAtEndList(t->courseCode, idList);
        pNode tmp = malloc(sizeof(listNode));
        strcpy(tmp->topic, t->courseCode);
//            printf("1\n");
        tmp->next = idList->next;
        idList->next = tmp;
        printf("2\n");//1 WORKDS FINE

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
        printf("%s:%s %d %s ", t->courseCode, t->course, t->creditHours, t->department);
        printList(t->topicsList);
        printInOrder(t->right);
    }
    printf("\n");
}

int getBalance(pAvl N) {
    if (N == NULL) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

pAvl deleteTreeNode(pAvl root, String courseCode) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL) {
        return root;
    }

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (strcmp(courseCode, root->courseCode) < 0) {

        root->left = deleteTreeNode(root->left, courseCode);
    }

        // If the key to be deleted is greater than the
        // root's key, then it lies in right subtree
    else if (strcmp(courseCode, root->courseCode) > 0) {
        root->right = deleteTreeNode(root->right, courseCode);

        // if key is same as root's key, then This is
        // the node to be deleted
    }
    else {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            pAvl temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else { // One child case
                *root = *temp;
            } // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            pAvl temp = findMin(root->right);

            // Copy the inorder successor's data to this node
            strcpy(root->courseCode, temp->courseCode);

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
        printf("FILE NOT FOUND!\n");
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


            insertAtEndList(token, tmpAvlNode->topicsList);
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
    strcpy(tmpNode->courseCode, dummyStr);
    printf("2. COURSE NAME:\n");
    scanf("%s", dummyStr);
    strcpy(tmpNode->course, dummyStr);
    printf("3. CREDIT HOURS:\n");
    scanf("%d", &dummyInt);
    tmpNode->creditHours = dummyInt;
    printf("4. DEPARTMENT:\n");
    scanf("%s", dummyStr);
    strcpy(tmpNode->department, dummyStr);

    while (true) {
        printf("5.PLEASE INPUT TOPICS ONE BY ONE, OR PRESS -1 WHEN YOU ARE DONE\n");
        scanf("%s", dummyStr);
        if (strcmp(dummyStr, "-1") == 0) {
            break;
        }
        insertAtEndList(dummyStr, tmpNode->topicsList);

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

    printf("INPUT COURSE CODED YOU'RE LOOKING FOR\n");
    scanf("%s", dummyStr);
    pAvl tmp = null;
    tmp = findTreeNode(dummyStr, root);
    if (tmp == null) {
        red();
        printf("COURSE NOT FOUND!\n");
        reset();
        return null;
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
//            newNode->topicsList = tmp->topicsList;
//            strcpy(newNode->department, tmp->department);
//            newNode->creditHours = tmp->creditHours;
//            strcpy(newNode->course, tmp->course);

            root = insert(*newNode, root);


        }

        else if (dummyInt == 2) {
            printf("PLEASE INPUT NEW COURSE NAME\n");
            scanf("%s", dummyStr);
            strcpy(tmp->course, dummyStr);

        }
        else if (dummyInt == 3) {
            printf("PLEASE INPUT NEW COURSE CREDIT HOURS\n");
            scanf("%d", &dummyInt);
            tmp->creditHours = dummyInt;

        }
        else if (dummyInt == 4) {
            printf("PLEASE INPUT NEW DEPARTMENT NAME\n");
            scanf("%s", dummyStr);
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
                    scanf("%s", innerStr);
                    insertAtEndList(innerStr, tmp->topicsList);


                }
                else if (innerInt == 2) {
                    printf("TOPIC YOU WISH TO DELETE\n");
                    scanf("%s", innerStr);
                    deleteNodeList(innerStr, tmp->topicsList);
                }
                else if (innerInt == 3) {
                    deleteList(tmp->topicsList);
                }
                else if (innerInt == 4) {
                    pNode tmpTopic = findNodeList(dummyStr, tmp->topicsList);
                    if (tmpTopic == null) {
                        red();
                        printf("TOPIC NOT FOUND!\n");
                        reset();
                    }
                    else {
                        String strTmp;
                        printf("ENTER UPDATED TOPIC PLEASE\n");
                        scanf("%s", strTmp);
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
    printList(tmp->topicsList);

}

void printDep(pAvl t, String str) {

    if (t != NULL) {
        printDep(t->left, str);

        if (strcmp(t->department, str) == 0) {
            printf("%s\n", t->courseCode);
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
    for (int i = 0; i < strlen(tmpDep); ++i) {
        if (tmpDep[i] == '\n') {
            tmpDep[i] = '\0';
        }
    }
    printDep(root, tmpDep);

}

pAvl seventhChoice(pAvl root) {

    String dummyStr;
    printf("INPUT CODE YOU WANT TO DELETE \n");
    scanf("%s", dummyStr);

    return deleteTreeNode(root, dummyStr);


}


/*
void FindByIllness(AVLNode t, string ill) {
    if (t != NULL) {
        FindByIllness(t->Left, ill);
        if (strcasecmp(ill, t->data.Illness) == 0) {
            printf("   %-15s", t->data.PatientName);
            printf("   %c", t->data.Gender);
            printf("\t\t");
            stringToDate(t->data.admissionDate);
            printf("   \t");
            stringToDate(t->data.birthDate);
            printf("\t%s", t->data.Illness);
            printf("\t\t%s", t->data.Address);
            printf("      \t%s", t->data.BloodType);
            printf("\n");
        }
        FindByIllness(t->Right, ill);
    }

}


*/


pAvl eightChoice(pAvl root) {
    printf("INPUT THE LETTER PLEASE \n");
    char letter;
    scanf(" %c", &letter);

//    pAvl tmp = null;
//    tmp = findTreeNode("^%c.*", letter);
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
    if (strcmp(t->course,x) == 0) {

        printf("%s\n", t->courseCode);
//            insertAtEndList(t->courseCode, idList);
        pNode tmp = malloc(sizeof(listNode));
        strcpy(tmp->topic, t->courseCode);
//            printf("1\n");
        tmp->next = idList->next;
        idList->next = tmp;
        printf("2\n");//1 WORKDS FINE

//            deleteTreeNode(t, t->courseCode);
    }

    findDepNode(t->right, x, idList);


}





pAvl ninthChoice(pAvl root) {

    pNode tmpID = makeEmptyList(tmpID);

    fgetc(stdin);
    printf("PLEASE INPUT DEPARTMENT\n");
    String str;
    fgets(str, MAX_STRING, stdin);
    findDepNode(root, str, tmpID);
    for (pNode iter = tmpID; iter != null; iter = iter->next) {
        root = deleteTreeNode(root, iter->topic);

    }
    tmpID = makeEmptyList(tmpID);
    free(tmpID);

    return root;

}

void filePrintInOrder(pAvl t, FILE *out) {

    if (t != NULL) {
        filePrintInOrder(t->left, out);

        fprintf(out, "courseCode: %s     course name: %s      creditHours: %d      department: %s       topics: ",
                t->courseCode, t->course, t->creditHours, t->department);

//
//        if (isEmptyList(t->topicsList)) {
//            fprintf(out, "\n");
////            return;
//        }
//        else {
        for (listNode *iter = t->topicsList->next; iter != NULL; iter = iter->next) {
            fprintf(out, "%s ", iter->topic);

        }
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


int main() {
    pAvl root = NULL;
    bool isRead = false;


    line();
    welcome();
    line();


    int selection;
    while (true) {
        printf("1. Read the file courses.txt file and create the tree.\n"
               "2. Insert a new course from the user with all its associated data.\n"
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
                root = secondChoice(root);
                line();
                break;

            case 3:
                root = thirdChoice(root);
                break;

            case 4:

                printInOrder(root);
                line();
                break;

            case 5:
                fifhtChoice(root);
                line();
                break;

            case 6:
                sixthChoice(root);
                line();
                break;

            case 7:
                root = seventhChoice(root);
                line();


                break;


            case 8:
                root = eightChoice(root);
                line();
                break;


            case 9:
                root = ninthChoice(root);
                line();
                break;


            case 10 :
                save(root);
                break;

            case 11:
                yellow();
                printf("THANK YOU COME AGAIN!!\n");
                reset();
                return 0;
                line();
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

