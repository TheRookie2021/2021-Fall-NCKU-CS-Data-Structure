#include <iostream>
#include <list>
using namespace std;

struct node
{
    int key;
    int height; // root is the highist, leaves height are 0
    int BF;
    struct node *left, *right;
};
node *creat_node(int n)
{
    node *newnode = new node;
    newnode->key = n;
    newnode->height = 1;
    newnode->BF = 0;

    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
int max(node *a, node *b)
{
    if (a == NULL && b == NULL)
        return 0;
    if (a == NULL)
        return b->height;
    if (b == NULL)
        return a->height;

    return (a->height > b->height) ? a->height : b->height;
}
class avl
{
private:
    node *root;

public:
    // void LeftRotate(node **target)
    // {
    //     /******************
    //      *            target
    //      *
    //                  x (bf<-1)             z
    //                   \                 /   \
    //                    z (bf=-1)  ->   x     y
    //                      \
    //                       y
    //   *****************/
    //     node *x = (*target)->right;
    //     node *z = (*target)->right->right;
    //     // node *y = (*target)->right->right->right;
    //     // node *temp = (*target)->left;
    //     (*target)->right = z;
    //     z->left = x;
    // }
    // void RightRotate(node **target)
    // {
    // }
    node *search(node *root, int n)
    {
        if (root == NULL)
            return;
        if (n > root->key)
            search(root->right, n);
        else if (n < root->key)
            search(root->left, n);
        else
            return root;
    }

    void insert(node *root, int n)
    {
        if (root == NULL)
        {
            root = creat_node(n);
            return;
        }

        if (n > root->key)
        {
            if (root->right != NULL)
                insert(root->right, n);
            else
            {
                root->right = creat_node(n);
            }
        }
        else if (n < root->key)
        {
            if (root->left != NULL)
                insert(root->left, n);
            else
            {
                root->left = creat_node(n);
            }
        }
        else
            return;

        // update height then check balanced factor
        root->height = max(root->left, root->right) + 1;

        if (root->left == NULL && root->right == NULL)
        {
            root->BF = 0;
        }
        else if (root->left == NULL)
        {
            root->BF = -root->right->height;
        }
        else if (root->right == NULL)
        {
            root->BF = root->left->height;
        }
        else
        {
            root->BF = root->left->height - root->right->height;
        }

        // check the BF of children of present node
        node *BF_inbalance = NULL;
        if (root->left != NULL)
        {
            if (root->left->BF > 1 || root->left->BF < -1)
            {
                BF_inbalance = root->left;
            }
        }
        if (root->right != NULL)
        {
            if (root->right->BF > 1 || root->right->BF < -1)
            {
                BF_inbalance = root->right;
            }
        }
        if (BF_inbalance == NULL)
            return;

        // let's rorororororooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooorotate!
        if (BF_inbalance->BF > 1 || BF_inbalance->BF < -1)
        {
            node *child_inbalance; // the child of BF inbalance needed to be rotate

            if (BF_inbalance->left == NULL)
            {
                child_inbalance = BF_inbalance->right;
            }
            else if (BF_inbalance->right == NULL)
            {
                child_inbalance = BF_inbalance->left;
            }
            else
            {
                child_inbalance = (BF_inbalance->left->height > BF_inbalance->right->height) ? BF_inbalance->left : BF_inbalance->right;
                // warning! what happens when either of childe is null-> segmentation fault will occure!!!!!!!!!!!! (9/30
                // solved! (10/3
            }

            // case bf>1
            if (BF_inbalance->BF > 1)
            {

                // ll -> need right rotate
                /****************
                      x (bf>1)          z
                     /                 / \
                   z (bf=1)   ->     y    x
                  /
                 y
                ****************/
                if (child_inbalance->BF == 1)
                {
                    if (root->left == BF_inbalance)
                    {
                        root->left = child_inbalance;
                        BF_inbalance->right = child_inbalance->right;
                        child_inbalance->right = BF_inbalance;
                    }
                    else
                    {
                        root->right = child_inbalance;
                        BF_inbalance->right = child_inbalance->right;
                        child_inbalance->right = BF_inbalance;
                    }
                }

                // lr ->first, need left rotate on z, then right rotate on x
                /****************
                      x (bf>1)             x            y
                     /                    /           /   \
                   z (bf=-1)     ->     y       ->   z     x
                    \                  /
                     y               z
                ****************/
                else if (child_inbalance->BF == -1)
                {
                    if (root->left == BF_inbalance)
                    {
                        BF_inbalance->left = child_inbalance->right;
                        BF_inbalance->left->left = child_inbalance;
                        child_inbalance->right = NULL;

                        root->left = BF_inbalance->left;
                        BF_inbalance->left->right = BF_inbalance;
                        BF_inbalance->right = NULL;
                    }
                    else
                    {
                        BF_inbalance->left = child_inbalance->right;
                        BF_inbalance->left->left = child_inbalance;
                        child_inbalance->right = NULL;

                        root->right = BF_inbalance->left;
                        BF_inbalance->left->right = BF_inbalance;
                        BF_inbalance->right = NULL;
                    }
                }
            }

            // case bf<-1
            else if (BF_inbalance->BF < -1)
            {

                // rr ->need left rotate
                /*****************
                      x (bf<-1)             z
                        \                 /   \
                         z (bf=-1)  ->   x     y
                           \
                            y
                 *****************/
                if (child_inbalance->BF == -1)
                {
                    if (root->left == BF_inbalance)
                    {
                        root->left = child_inbalance;
                        BF_inbalance->right = child_inbalance->left;
                        child_inbalance->left = BF_inbalance;
                    }
                    else
                    {
                        root->right = child_inbalance;
                        BF_inbalance->right = child_inbalance->left;
                        child_inbalance->left = BF_inbalance;
                    }
                }
            }
            // rl: first right rotate on z, then left rotate on x
            /*****************
                  x (bf<-1)             x                    y
                    \                    \                 /   \
                     z (bf=1)   ->        y         ->   x      z
                    /                      \
                   y                        z
             *****************/
            else if (child_inbalance->BF == 1)
            {
                if (root->left == BF_inbalance)
                {
                    BF_inbalance->right = child_inbalance->left;
                    BF_inbalance->right->right = child_inbalance;
                    child_inbalance->left = NULL;

                    root->left = BF_inbalance->right;
                    BF_inbalance->right->left = BF_inbalance;
                    BF_inbalance->right = NULL;
                }
                else
                {
                    BF_inbalance->right = child_inbalance->left;
                    BF_inbalance->right->right = child_inbalance;
                    child_inbalance->left = NULL;

                    root->right = BF_inbalance->right;
                    BF_inbalance->right->left = BF_inbalance;
                    BF_inbalance->right = NULL;
                }
            }
        }
        return;
    }

    void preorder(node *root)
    {
        if (root != NULL)
        {
            cout << root->key;
            preorder(root->left);
            preorder(root->right);
        }
    }
    void inorder(node *root)
    {
        if (root != NULL)
        {
            inorder(root->left);
            cout << root->key;
            inorder(root->right);
        }
    }
};

int main()
{

    return 0;
}