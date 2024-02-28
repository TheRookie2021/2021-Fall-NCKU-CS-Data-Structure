#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 1001
typedef struct node
{
    char key[MAX];
    int value;

} Node;

typedef struct PatriciaTree *patricia;
typedef struct PatriciaTree
{
    int bitNUM;
    Node data;
    patricia left, right;

} PatriciaTree;

Node creatNode(char* key, int value)
{
    Node newnode;
    strcpy(newnode.key , key);
    newnode.value = value;
    return newnode;
}
patricia creatPatricia(char* key, int value, int bitnum)
{
    patricia new = malloc(sizeof(PatriciaTree));
    new->data = creatNode(key, value);
    new->bitNUM = bitnum;
    new->left = NULL;
    new->right = NULL;
    return new;
}
bool bit(char* key, int index)
{
    return key[index];
}

patricia search(patricia t, char* key)
{
    if (!t)
        return NULL;
    patricia cur, next;
    next=t->left;
    cur = t;
    while (next->bitNUM > cur->bitNUM)
    {
        cur = next;
        next = (bit(key, next->bitNUM)) ? next->right : next->left;
    }
    return next;
}
void insert(patricia *tree, char* key, int value)
{
    patricia cur, parent, last, new;
    int i;
    if ((*tree) == NULL)
    {
        (*tree) = creatPatricia(key, value, 0);
        (*tree)->left = (*tree);
        printf("insert -> %d\n",value);
        return;
    }
    last = search((*tree), key);
    if (strcmp(key , last->data.key)==0)
    {
        printf("insert -> conflict\n");
        return;
    }

    for (i = 1; bit(key, i) == bit(last->data.key, i); i++);

    cur = (*tree)->left;
    parent = *tree;
    while (cur->bitNUM > parent->bitNUM && cur->bitNUM < i)
    {
        parent = cur;
        cur = (bit(key, cur->bitNUM)) ? cur->right : cur->left;
    }

    new = creatPatricia(key, value, i);
    new->left = (bit(key, i)) ? cur : new;
    new->right = (bit(key, i)) ? new : cur;
    if (cur == parent->left)
        parent->left = new;
    else
        parent->right = new;

     printf("insert -> %d\n",new->data.value);
}
void delete (patricia *tree, char* key)
{
    patricia target=NULL;
    target = search(*tree,key);
    if(strcmp(target->data.key,key)!=0) 
    {
        printf("delete -> not found\n");
        return;
    }
    patricia parent;
    
    parent = *tree;
    while (parent->left!=target && parent->right!=target)
    {
        parent  = (bit(key, parent->bitNUM)) ? parent->right : parent->left;
     
    }
    // Case 1: p has one self pointer.
    if (target->left == target || target->right == target)
    {
       
       if (strcmp(target->data.key, (*tree)->data.key) == 0)
       {
           (*tree) = NULL;
       }
        else
        {
            if (parent->left == target)
                parent->left = (target->left == target) ? target->right : target->left;
            else parent->right = (target->left == target) ? target->right : target->left;
        }
    }
    // Case 2: p has no self pointer.
    else if (target->left != target && target->right != target)
    {
        patricia q=target;
        while(q->left!=target &&q->right!=target)
        {
            q=(bit(key,q->bitNUM))? q->right:q->left;
        }
        if (q->left == target)
        {
            q->left=target;
            strcmp(target->data.key,q->data.key);
            target->data.value = q->data.value;
            patricia r = q;
            while (r->left != q && r->right != q)
            {
                r = (bit(key, r->bitNUM)) ? r->right : r->left;
            }
            if (r->left == q)
            {
                r->left = target;
            }
            else
            {
                r->right = target;
            }
        }
        else
        {
            q->right=target;
            strcmp(target->data.key,q->data.key);
            target->data.value = q->data.value;
            patricia r = q;
            while (r->left != q && r->right != q)
            {
                r = (bit(key, r->bitNUM)) ? r->right : r->left;
            }
            if (r->left == q)
            {
                r->left = target;
            }
            else
            {
                r->right = target;
            }
        }
    }
    printf("delete -> %s\n",key);
}
void quit()
{
    exit(0);
}
int main()
{
    int num;
    char key[MAX];
    int value;
    char str[20];
    patricia tree=NULL;
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%s", str);
        if (strcmp(str, "insert") == 0)
        {
            scanf("%s%d", key, &value);
            insert(&tree, key, value);
        }
        else if (strcmp(str, "search") == 0)
        {
            scanf("%s", key);
            patricia new=NULL;
            new = search(tree, key);
            if (strcmp(new->data.key,key)==0)
            {
                printf("search -> %d\n",new->data.value);
            }
            else
            {
                printf("search -> not found\n");
            }
        }
        else if (strcmp(str, "delete") == 0)
        {
            scanf("%s", key);
            delete(&tree,key);
        }
        else if (strcmp(str, "quit") == 0)
        {
            quit();
        }
    }

    return 0;
}