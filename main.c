#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define N 15

typedef struct nodeItem {
    int info;
    struct nodeItem *left, *right, *father;
} node;

node *makeTree(int value);
int info(node *n);
node *left(node *n);
node *right(node *n);
node *father(node *n);
int isLeft(node *n);
int isRight(node *n);
node *brother(node *n);

node *addLeft(node *tree, int value);
node *setNodeLeft(node *tree, node *n);
node *addRight(node *tree, int value);
node *setNodeRight(node *tree, node *n);
void freeTree(node *tree);
void verifyParent(node *tree);
void freePosOrdem(node *tree);

void preOrdem(node *tree);
void emOrdem(node *tree);
void posOrdem(node *tree);

node *insert(node *tree, int value);
node *searchForValue(node *tree, int value);
void resultOfSearch(node *find);
node *deleteNode(node *tree, int value);
node *deleteRoot(node *tree);

int max(int a, int b);
int larger(node *tree);
int min(int a, int b);
int smaller(node *tree);
int length(node *tree);
int largestNumberSubtree(node *tree);
void showLargerSmaller(node *tree);
void showAmountOfNodes(node *tree);
int numberOfNodesVisited(node *tree, int value);

int main() {
    setlocale(LC_ALL, "");
    node *tree = NULL;
    int array[N] = {
            50, 30, 70, 20,40, 60, 80, 15,
            25,35, 45, 36 , 65, 58, 72
    };

    for(int i=0; i < N; i++) {
        tree = insert(tree, array[i]);
    }

    printf("Valores Ordenados (percurso emOrdem): \n");
    emOrdem(tree);
    printf("\n\n");
    showAmountOfNodes(tree);
    showLargerSmaller(tree);
    printf("Number of nodes visited in the search: %d\n", numberOfNodesVisited(tree, 36));

    return 0;
}

node *makeTree(int value) {
    node *tree = (node *) malloc(sizeof (node));
    tree->info = value;
    tree->left = tree->right = tree->father = NULL;

    return tree;
}

int info(node *n) {
    return n == NULL ? printf("Unable to access information from a null node\n") : n->info;
}

node *left(node *n) {
    return n == NULL ? NULL : n->left;
}

node *right(node *n) {
    return n == NULL ? NULL : n->right;
}

node *father(node *n) {
    return n == NULL ? NULL : n->father;
}

int isLeft(node *n) {
    return n == NULL || father(n) == NULL ? 0 : left(father(n)) == n ? 1 : 0;
}

int isRight(node *n) {
    return n == NULL || father(n) == NULL ? 0 : right(father(n)) == n ? 1 : 0;
}

node *brother(node *n) {
    return n == NULL || father(n) == NULL ? NULL : isLeft(n) ? right(father(n)) : left(father(n));
}

node *addLeft(node *tree, int value) {
    return setNodeLeft(tree, makeTree(value));
}

node *setNodeLeft(node *tree, node *n) {
    tree->left = n;
    if(n != NULL) n->father = tree;

    return n;
}

node *addRight(node *tree, int value) {
    return setNodeRight(tree, makeTree(value));
}

node *setNodeRight(node *tree, node *n) {
    tree->right = n;
    if(n != NULL) n->father = tree;

    return n;
}

void freeTree(node *tree) {
    if(tree != NULL) {
        verifyParent(tree);
        freePosOrdem(tree);
    } else return;
}

void verifyParent(node *tree) {
    node *parent = father(tree);

    if(parent != NULL) {
        if(isLeft(tree)) parent->left = NULL;
        if(isRight(tree)) parent->right = NULL;
    } else return;
}

void freePosOrdem(node *tree) {
    freeTree(left(tree));
    freeTree(right(tree));
    free(tree);
}

void preOrdem(node *tree) {
    if(tree != NULL) {
        printf("[%d]", info(tree));
        preOrdem(left(tree));
        preOrdem(right(tree));
    } else return;
}

void emOrdem(node *tree) {
    if(tree != NULL) {
        emOrdem(left(tree));
        printf("[%d]", info(tree));
        emOrdem(right(tree));
    } else return;
}

void posOrdem(node *tree) {
    if(tree != NULL) {
        posOrdem(left(tree));
        posOrdem(right(tree));
        printf("[%d]", info(tree));
    } else return;
}

node *insert(node *tree, int value) {
    if(tree == NULL) return makeTree(value);

    if(value < info(tree)) {
        left(tree) == NULL ? setNodeLeft(tree, insert(left(tree), value))
        : insert(left(tree), value);
    } else {
        right(tree) == NULL ? setNodeRight(tree, insert(right(tree), value))
        : insert(right(tree), value);
    }

    return tree;
}

node *searchForValue(node *tree, int value) {
    if(tree == NULL || info(tree) == value) return tree;

    return value < info(tree) ? searchForValue(left(tree), value)
    : searchForValue(right(tree), value);
}

void resultOfSearch(node *find) {
    if(find != NULL) {
        printf("Value %d found in binary tree!\n", info(find));
    } else {
        printf("Value found in binary tree!\n");
    }
}

node *deleteNode(node *tree, int value) {
    node *findNode = searchForValue(tree, value);
    node *parent = father(findNode);

    if(parent == NULL) return deleteRoot(findNode);
    else {
        isLeft(findNode) ? setNodeLeft(parent, deleteRoot(findNode))
        : setNodeRight(parent, deleteRoot(findNode));
    }

    return tree;
}

node *deleteRoot(node *tree) {
    node *node, *parent;

    if(left(tree) == NULL) {
        node = right(tree);
    } else {
        node = left(tree);
        while (right(node) != NULL) {
            node = right(node);
        }

        if(father(node) != tree) {
            parent = father(node);
            setNodeRight(parent, left(node));
            setNodeLeft(node, left(tree));
        }
        setNodeRight(node, right(tree));
    }

    if(node != NULL) node->father = NULL;
    free(tree);
    return node;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int larger(node *tree) {
    if(tree == NULL) return 0;
    else {
        int current = max(larger(left(tree)), larger(right(tree)));
        return max(info(tree), current);
    }
}

int min(int a, int b) {
    return a > b ? b : a;
}

int smaller(node *tree) {
    if(tree == NULL) return 999;
    else {
        int current = min(smaller(left(tree)), smaller(right(tree)));
        return min(info(tree), current);
    }
}

int length(node *tree) {
    if(tree == NULL) return 0;
    else return length(left(tree)) + length(right(tree)) + 1;
}

int largestNumberSubtree(node *tree) {
    return tree == NULL ? 0 : max(length(left(tree)), length(right(tree)));
}

void showLargerSmaller(node *tree) {
    if(tree == NULL) {
        printf("Cannot find largest and smallest in a null tree!\n");
    } else {
        printf("Larger: %d, Smaller: %d\n", larger(tree), smaller(tree));
    }
}

void showAmountOfNodes(node *tree) {
    if(tree != NULL) {
        printf("Number of tree nodes is: %d\n", length(tree));
        printf("Number of left tree nodes is: %d\n", length(left(tree)));
        printf("Number of right tree nodes is: %d\n", length(right(tree)));
    } else printf("Unable to inform the number of nodes in a null tree!\n");
}

int numberOfNodesVisited(node *tree, int value) {
    if(tree == NULL ) return 0;
    if(info(tree) == value) return 1;

    return value < info(tree) ? numberOfNodesVisited(left(tree), value) + 1
    : numberOfNodesVisited(right(tree), value) + 1;
}
