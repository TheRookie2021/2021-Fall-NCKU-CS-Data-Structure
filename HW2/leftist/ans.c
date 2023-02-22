#include <stdio.h>

struct node
{
    int data,dist;
    struct node *right,*left,*prnt;

}*root,*temp,*root3,*root4;

int print(struct node *p)
{
    if(p!=NULL)
    {
    print(p->left);
    printf("\t%d",p->data);
    print(p->right);
    }
}

int distance(struct node *m)
{
    if(m==NULL)
    {
    return(-1);
    }
    else
    {
    return(m->dist);
    }   

}

struct node * merg(struct node *a,struct node *b)
{
    if(a==NULL)
        return b;
    if(b==NULL)
        return a;
    
    if(b->data>a->data)
    {
        temp=b;
        b=a;
        a=temp;
    }
    a->right=merg(a->right,b);
    if(distance(a->right)>distance(a->left))
    {
        temp=a->right;
        a->right=a->left;
        a->left=temp;
    }
    if(a->right==NULL)
        a->dist=0;
    else
        a->dist=1+(a->right->dist);
    return(a);
}

struct node * deletion(struct node * root)
{
    printf("deleted element is %d",root->data);
    root=merg(root->right,root->left);
}
struct node * insert(struct node *root1)
{ 
    int val;
    struct node *newnode,*x;
    newnode=(struct node *)malloc(sizeof(struct node));
    newnode->right=NULL;
    newnode->left=NULL;
    newnode->dist=0;
    newnode->prnt=NULL;
    printf("\n enter value");
    scanf("%d",&val);
    newnode->data=val;
    root1=merg(root1,newnode);
    printf("root element is %d\n \n inorder traversal of tree is:",root->data);
    print(root1);
    return(root1);
}
void meld()
{
    int val;
    printf("\n1st tree:");
    root3=(struct node *)malloc(sizeof(struct node));
    root3->right=NULL;
    root3->left=NULL;
    root3->dist=0;
    printf("\nenter 1st data");
    scanf("%d",&val);
    root3->data=val;
    while(1)
    {
    printf("\ndo u waana insert element to 1st tree(0/1)");
    scanf("%d",&val);
    if(val)
    {
    root3=insert(root3);
    }
    else
    break;
    }

    printf("\n2nd tree:");
    root4=(struct node *)malloc(sizeof(struct node));
    root4->right=NULL;
    root4->left=NULL;
    root4->dist=0;
    printf("\nenter 1st data");
    scanf("%d",&val);
    root4->data=val;
    while(1)
    {
    printf("\ndo u waana insert element to 1st tree(0/1)");
    scanf("%d",&val);
    if(val)
    {
    root4=insert(root4);
    }
    else
    break;
    }
    printf("\n 1st tree");
    print(root3);
    printf("\n 2nd tree");
    print(root4);
    root3=merg(root3,root4);
    printf("\nroot element is: %d\n",root3->data);
    print(root3);
}
int main()
{ 
    int fl=0,val;
    printf("\n enter root node");
    scanf("%d",&val);
    root=(struct node *)malloc(sizeof(struct node));
    root->right=NULL;
    root->left=NULL;
    root->dist=0;
    root->data=val;
    root->prnt=NULL;
    while(1)
{
printf("\n enter ur option \n 1.insert 2.print 3.delete 4.meld 5.exit\n");
scanf("%d",&val);
switch(val)
{
    case 1:
    root=insert(root);
    break;
    case 2:
    printf("\n");
    print(root);
    break;
    case 3:
    root=deletion(root);
    break;
    case 4:
    meld();
    break;
    case 5:
    fl=1;
    break;
    default:
    break;

}
if(fl==1)
{
break;
}
}
}

