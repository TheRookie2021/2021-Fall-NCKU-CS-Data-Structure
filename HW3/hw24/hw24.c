#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct RBTNode
{
    int color, key;
    struct RBTNode *left, *right, *parent;
} RBTNode;

typedef struct Node
{
    int data, bf;
    struct Node *left, *right;
} Node;

RBTNode *root = NULL, *another;
bool balanced;

RBTNode *RBTInitNode(int key)
{
    RBTNode *node = (RBTNode *)malloc(sizeof(RBTNode));
    node->key = key;
    node->color = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void RBTInitTree()
{
    another = (RBTNode *)malloc(sizeof(RBTNode));
    another->color = 1;
    another->left = another->right = another->parent = NULL;
    root = another, root->parent = another;
}

void RBTRightRotate(RBTNode *node)
{
    RBTNode *left = node->left;
    node->left = left->right;
    if (left->right != another)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == another)
        root = left;
    else if (node == node->parent->left)
        node->parent->left = left;
    else
        node->parent->right = left;
    left->right = node;
    node->parent = left;
}

void RBTLeftRotate(RBTNode *node)
{
    RBTNode *right = node->right;
    node->right = right->left;
    if (right->left != another)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == another)
        root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

void RBTInsertFixup(RBTNode *currentNode)
{

    while (currentNode->parent->color == 0)
    {
        if (currentNode->parent == currentNode->parent->parent->left)
        {
            RBTNode *uncle = currentNode->parent->parent->right;
            if (uncle->color == 0)
            {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            else
            {
                if (currentNode == currentNode->parent->right)
                {
                    currentNode = currentNode->parent;
                    RBTLeftRotate(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                RBTRightRotate(currentNode->parent->parent);
            }
        }
        else
        {
            RBTNode *uncle = currentNode->parent->parent->left;
            if (uncle->color == 0)
            {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            else
            {
                if (currentNode == currentNode->parent->left)
                {
                    currentNode = currentNode->parent;
                    RBTRightRotate(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                RBTLeftRotate(currentNode->parent->parent);
            }
        }
    }
    root->color = 1;
}

void RBTInsert(int key)
{
    RBTNode *x = root;
    RBTNode *y = another;
    RBTNode *node = RBTInitNode(key);
    while (x != another)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else if (node->key > x->key)
            x = x->right;
        else
            return;
    }
    node->parent = y;
    if (y == another)
        root = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;
    node->left = another;
    node->right = another;
    RBTInsertFixup(node);
    another->parent = root;
}

RBTNode *RBTSearch(int key)
{
    RBTNode *current = root;
    while (current != another && current->key != key)
    {
        if (current->key > key)
            current = current->left;
        else
            current = current->right;
    }
    if (current == another)
        return NULL;
    else
        return current;
}

RBTNode *RBTLeftmost(RBTNode *current)
{
    while (current->left != another)
        current = current->left;
    return current;
}

RBTNode *RBTSuccessor(RBTNode *current)
{
    if (current->right != another)
        return RBTLeftmost(current->right);
    RBTNode *current_pt = current->parent;
    while (current_pt != another && current == current_pt->right)
    {
        current = current_pt;
        current_pt = current_pt->parent;
    }
    return current_pt;
}

void RBTDeleteFixup(RBTNode *current)
{
    while (current != root && current->color == 1)
    {
        if (current == current->parent->left)
        {
            RBTNode *sibling = current->parent->right;
            if (sibling->color == 0)
            {
                sibling->color = 1;
                current->parent->color = 0;
                RBTLeftRotate(current->parent);
                sibling = current->parent->right;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1)
            {
                sibling->color = 0;
                current = current->parent;
            }
            else
            {
                if (sibling->right->color == 1)
                {
                    sibling->left->color = 1;
                    sibling->color = 0;
                    RBTRightRotate(sibling);
                    sibling = current->parent->right;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->right->color = 1;
                RBTLeftRotate(current->parent);
                current = root;
            }
        }
        else
        {
            RBTNode *sibling = current->parent->left;
            if (sibling->color == 0)
            {
                sibling->color = 1;
                current->parent->color = 0;
                RBTRightRotate(current->parent);
                sibling = current->parent->left;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1)
            {
                sibling->color = 0;
                current = current->parent;
            }
            else
            {
                if (sibling->left->color == 1)
                {
                    sibling->right->color = 1;
                    sibling->color = 0;
                    RBTLeftRotate(sibling);
                    sibling = current->parent->left;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->left->color = 1;
                RBTRightRotate(current->parent);
                current = root;
            }
        }
    }
    current->color = 1;
}

void RBTDelete(int key)
{
    RBTNode *toDelete = RBTSearch(key);
    if (toDelete == NULL)
        return;
    RBTNode *x, *y;
    if (toDelete->left == another || toDelete->right == another)
        y = toDelete;
    else
        y = RBTSuccessor(toDelete);
    if (y->left != another)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if (y->parent == another)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != toDelete)
        toDelete->key = y->key;

    if (y->color == 1)
        RBTDeleteFixup(x);
    another->parent = root;
}

void RBTExist( int targ)
{
    for (Node *now = root; now; now = (targ > now->data) ? now->right : now->left)
        if (targ == now->data)
        {
            printf("exist\n");
            return;
        }
    printf("Not exist\n");
}

//-----------------------------------------------------
void AVLLeftRotate(Node **root, bool isInsert)
{
    Node *node = *root, *child = node->left;
    if (isInsert)
        balanced = true;

    if (child->bf == 1 || child->bf == 0)
    {
        node->left = child->right;
        child->right = node;
        if (child->bf == 0)
        {
            child->bf = -1;
            node->bf = 1;
            balanced = true;
        }
        else
            child->bf = node->bf = 0;
        (*root) = child;
    }
    else
    {
        Node *grand = child->right;
        child->right = grand->left;
        grand->left = child;
        node->left = grand->right;
        grand->right = node;
        switch (grand->bf)
        {
        case 1:
            node->bf = -1;
            child->bf = 0;
            break;
        case 0:
            node->bf = child->bf = 0;
            break;
        case -1:
            node->bf = 0;
            child->bf = 1;
            break;
        }
        *root = grand;
        (*root)->bf = 0;
    }
}

void AVLRightRotate(Node **root, bool isInsert)
{
    Node *node = *root, *child = node->right;
    if (isInsert)
        balanced = true;

    if (child->bf == -1 || child->bf == 0)
    {
        node->right = child->left;
        child->left = node;
        if (child->bf == 0)
        {
            child->bf = 1;
            node->bf = -1;
            balanced = true;
        }
        else
            child->bf = node->bf = 0;
        (*root) = child;
    }
    else
    {
        Node *grand = child->left;
        child->left = grand->right;
        grand->right = child;
        node->right = grand->left;
        grand->left = node;
        switch (grand->bf)
        {
        case 1:
            node->bf = 0;
            child->bf = -1;
            break;
        case 0:
            node->bf = child->bf = 0;
            break;
        case -1:
            node->bf = 1;
            child->bf = 0;
            break;
        }
        *root = grand;
        (*root)->bf = 0;
    }
}

void AVLInsert(Node **root, int data)
{
    if (!*root)
    {
        *root = (Node *)malloc(sizeof(Node));
        (*root)->left = (*root)->right = NULL;
        (*root)->bf = 0;
        (*root)->data = data;
        balanced = false;
    }
    else if (data < (*root)->data)
    {
        Node *node = *root;
        AVLInsert(&(node->left), data);
        if (!balanced)
            switch (node->bf)
            {
            case -1:
                node->bf = 0;
                balanced = true;
                break;
            case 0:
                node->bf = 1;
                break;
            case 1:
                AVLLeftRotate(root, true);
                break;
            }
    }
    else if (data > (*root)->data)
    {
        Node *node = *root;
        AVLInsert(&(node->right), data);
        if (!balanced)
            switch (node->bf)
            {
            case 1:
                node->bf = 0;
                balanced = true;
                break;
            case 0:
                node->bf = -1;
                break;
            case -1:
                AVLRightRotate(root, true);
                break;
            }
    }
}

void AVLExist(Node *root, int targ)
{
    for (Node *now = root; now; now = (targ > now->data) ? now->right : now->left)
        if (targ == now->data)
        {
            printf("exist\n");
            return;
        }
    printf("Not exist\n");
}
int AVLFindReplace(Node *n)
{
    Node *ans = n->left;
    while (ans->right)
        ans = ans->right;
    return ans->data;
}

void AVLDelete(Node **root, int targ)
{
    Node *node = *root;
    if (!node)
        return;
    if (node->data == targ)
    {
        if (!node->left || !node->right)
        {
            (*root) = (node->left) ? (node->left) : (node->right);
            balanced = false;
        }
        else
        {
            int new_targ = AVLFindReplace(node);
            AVLDelete(root, new_targ);
            node->data = new_targ;
        }
    }
    else if (targ < node->data)
    {
        AVLDelete(&(node->left), targ);
        if (!balanced)
            switch (node->bf)
            {
            case -1:
                AVLRightRotate(root, false);
                break;
            case 0:
                node->bf = -1;
                balanced = true;
                break;
            case 1:
                node->bf = 0;
                break;
            }
    }
    else if (targ > node->data)
    {
        AVLDelete(&(node->right), targ);
        if (!balanced)
            switch (node->bf)
            {
            case 1:
                AVLLeftRotate(root, false);
                break;
            case 0:
                node->bf = 1;
                balanced = true;
                break;
            case -1:
                node->bf = 0;
                break;
            }
    }
}

void AVLSearch(Node *root, int targ)
{
    for (Node *now = root; now; now = (targ > now->data) ? now->right : now->left)
        if (targ == now->data)
        {
            printf("%d\n", now->bf);
            return;
        }
    printf("Not found\n");
}
int main()
{
    char DS[20];
    char op[20];
    int var;
    
    scanf("%s", DS);
    if (strcmp(DS, "AVL") == 0)
    {
        Node* root=NULL;
        for (;;)
        {
            scanf("%s", op);
            scanf("%d", &var);

            if (strcmp(op, "insert") == 0)
            {
                AVLInsert(&root,var);
            }
            else if (strcmp(op, "delete") == 0)
            {
                AVLDelete(&root,var);
            }
            else if (strcmp(op, "search") == 0)
            {
                AVLSearch(root,var);
            }
            else if (strcmp(op, "exist") == 0)
            {
                AVLExist(root,var);
            }
            else if (strcmp(op, "quit") == 0)
            {
                exit(0);
            }
        }
    }
    else
    {//RBTree

        for (;;)
        {
            scanf("%s", op);
            scanf("%d", &var);
    
            if (strcmp(op, "insert") == 0)
            {
                RBTInsert(var);
            }
            else if (strcmp(op, "delete") == 0)
            {
                RBTDelete(var);
            }
            else if (strcmp(op, "search") == 0)
            {
                RBTSearch(var);
            }
            else if (strcmp(op, "exist") == 0)
            {
                RBTExist(var);
            }
            else if (strcmp(op, "quit") == 0)
            {
                exit(0);
            }
        }
    }
    return 0;
}