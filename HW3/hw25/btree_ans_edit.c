#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX 3
#define MIN 2

struct BTreeNode {
  int val[MAX + 1];
  int count;// for counting internal value stored 
  struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root;

// Create a node
struct BTreeNode *createNode(int val, struct BTreeNode *child) {
  struct BTreeNode *newNode;
  newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  newNode->val[1] = val;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert node
void insertNode(int val, int pos, struct BTreeNode *node,
        struct BTreeNode *child) {
  int j = node->count;
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(int val, int *pval, int pos, struct BTreeNode *node,
         struct BTreeNode *child, struct BTreeNode **newNode) {
  int median, j;
  *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));

  median = MIN;
  j = median + 1;

  while (j <= MAX) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(val, pos, node, child);
  } else {
    insertNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value
int setValue(int val, int *pval,
           struct BTreeNode *node, struct BTreeNode **child) {
  int pos;
  
printf("step1\n");
  if (!node) {
    *pval = val;
    *child = NULL;
    return 1;//null tree
  }
printf("step2\n");
  if (val < node->val[1]) { //<= ? <
    pos = 0;
  } 
  else 
  {
    for (pos = node->count; (val <= node->val[pos] && pos > 1); pos--);
    
    if (val == node->val[pos]) {//here, duplicated num is not allow!!
      
      return 0;//do nothing after that
    }
  }

printf("step3\n");
  if (setValue(val, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      insertNode(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;//do nothing after that
}

// Insert the value
void insert(int val) {
  int flag, i;//flag: for "NULL" checking , i: for recursion
  struct BTreeNode *child;

  flag = setValue(val, &i, root, &child);
  if (flag)//flag==1: root is null
    root = createNode(i, child);
}

// Copy the successor
void copySuccessor(struct BTreeNode *myNode, int pos) {
  struct BTreeNode *dummy;
  dummy = myNode->link[pos];

  for (; dummy->link[0] != NULL;)
    dummy = dummy->link[0];
  myNode->val[pos] = dummy->val[1];
}

// Remove the value
void removeVal(struct BTreeNode *myNode, int pos) {
  int i = pos + 1;
  while (i <= myNode->count) {
    myNode->val[i - 1] = myNode->val[i];
    myNode->link[i - 1] = myNode->link[i];

    i++;
  }
  myNode->count--;
}

// Do right shift
void rightShift(struct BTreeNode *myNode, int pos) {
  struct BTreeNode *x = myNode->link[pos];
  int j = x->count;

  while (j > 0) {
    x->val[j + 1] = x->val[j];
    x->link[j + 1] = x->link[j];
  }
  x->val[1] = myNode->val[pos];
  x->link[1] = x->link[0];
  x->count++;

  x = myNode->link[pos - 1];
  myNode->val[pos] = x->val[x->count];
  myNode->link[pos] = x->link[x->count];
  x->count--;
  return;
}

// Do left shift
void leftShift(struct BTreeNode *myNode, int pos) {
  int j = 1;
  struct BTreeNode *x = myNode->link[pos - 1];

  x->count++;
  x->val[x->count] = myNode->val[pos];
  x->link[x->count] = myNode->link[pos]->link[0];

  x = myNode->link[pos];
  myNode->val[pos] = x->val[1];
  x->link[0] = x->link[1];
  x->count--;

  while (j <= x->count) {
    x->val[j] = x->val[j + 1];
    x->link[j] = x->link[j + 1];
    j++;
  }
  return;
}

// Merge the nodes
void mergeNodes(struct BTreeNode *myNode, int pos) {
  int j = 1;
  struct BTreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

  x2->count++;
  x2->val[x2->count] = myNode->val[pos];
  x2->link[x2->count] = myNode->link[0];

  while (j <= x1->count) {
    x2->count++;
    x2->val[x2->count] = x1->val[j];
    x2->link[x2->count] = x1->link[j];
    j++;
  }

  j = pos;
  while (j <= myNode->count) {
    myNode->val[j] = myNode->val[j + 1];
    myNode->link[j] = myNode->link[j + 1];
    j++;
  }
  myNode->count--;
  free(x1);
}

// Adjust the node
void adjustNode(struct BTreeNode *myNode, int pos) {
  if (!pos) {
    if (myNode->link[1]->count > MIN) {
      leftShift(myNode, 1);
    } else {
      mergeNodes(myNode, 1);
    }
  } else {
    if (myNode->count != pos) {
      if (myNode->link[pos - 1]->count > MIN) {
        rightShift(myNode, pos);
      } else {
        if (myNode->link[pos + 1]->count > MIN) {
          leftShift(myNode, pos + 1);
        } else {
          mergeNodes(myNode, pos);
        }
      }
    } else {
      if (myNode->link[pos - 1]->count > MIN)
        rightShift(myNode, pos);
      else
        mergeNodes(myNode, pos);
    }
  }
}

// Delete a value from the node
int delValFromNode(int val, struct BTreeNode *myNode) {
  int pos, flag = 0;
  if (myNode) {
    if (val < myNode->val[1]) {
      pos = 0;
      flag = 0;
    } else {
      for (pos = myNode->count; (val < myNode->val[pos] && pos > 1); pos--);
      if (val == myNode->val[pos]) {
        flag = 1;
      } else {
        flag = 0;//not found
      }
    }
    if (flag) {
      if (myNode->link[pos - 1]) {
        copySuccessor(myNode, pos);
        flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
        if (flag == 0) {//not found
          printf("non\n");
        }
      } else {
        removeVal(myNode, pos);
      }
    } else {
      flag = delValFromNode(val, myNode->link[pos]);
    }
    if (myNode->link[pos]) {
      if (myNode->link[pos]->count < MIN)
        adjustNode(myNode, pos);
    }
  }
  return flag;
}

// Delete operaiton
void delete (int val, struct BTreeNode *myNode) { 
  struct BTreeNode *tmp;
  if (!delValFromNode(val, myNode)) {
    printf("remove(%d) = not found\n",val);
    return;
  } else {
    if (myNode->count == 0) {
      tmp = myNode;
      myNode = myNode->link[0];
      free(tmp);
    }
  }
  root = myNode;
  printf("remove(%d) = %d\n",val,val);
}

// Search node
int search(int val, int *pos, struct BTreeNode *myNode,int *found,int* num) {
  if (!myNode) {
    return;
  }

  if (val < myNode->val[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->count;
       (val < myNode->val[*pos] && *pos > 1); (*pos)--)
      ;
    if (val == myNode->val[*pos]) {
      *found=1;
      *num=val;
      return val;
    }
  }
  search(val, pos, myNode->link[*pos],found,num);

  return -1;//not found
}
// Traverse the nodes
void get_k(struct BTreeNode *myNode,int target,int *k,int *val) { 
  int i;
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
      get_k(myNode->link[i],target,k,val);
      if((*k)==target){
        *val=myNode->val[i + 1]; 
      }
      (*k)++;
    }
    get_k(myNode->link[i],target,k,val);
  }
}

int delete_k (int kth, struct BTreeNode *myNode) {
  struct BTreeNode *tmp;
  int k=0;
  int val=-1;
  get_k(root,kth-1,&k,&val);
  
  if(val==-1){
    printf("removek(%d) = not found\n",kth);
    return;
  }
  if (!delValFromNode(val, myNode)) { 
    return;
  } else {
    if (myNode->count == 0) {
      tmp = myNode;
      myNode = myNode->link[0];
      free(tmp);
    }
  }
  root = myNode;
  printf("removek(%d) = %d\n",kth,val);
  
  return val;
}


// Traverse then nodes
void traversal(struct BTreeNode *myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
      traversal(myNode->link[i]);
      printf("%d ", myNode->val[i + 1]);

    }
    traversal(myNode->link[i]);
  }
}

int main() {
  int val, ch;
  int k=0;//for get_k
  int found=0;int num=0;//for search
  char op[20];
  int op_n;
  int variable;
  scanf("%d",&op_n);
  //insert
  //get
  //getk
  //remove
  //removek
for(int i=0;i<op_n;i++){
  scanf("%s",op);
  scanf("%d",&variable);
  
  if(strcmp(op,"add")==0){
    insert(variable);
    printf("add(%d) = ok\n",variable);
    traversal(root);printf("\n");

  }else if(strcmp(op,"get")==0){
    found=0; ch=0; num=0;
    search(variable, &ch, root,&found,&num);
    if(found==0)
      printf("get(%d) = not found\n",variable);
    else 
      printf("get(%d) = %d\n",variable,num);
  }else if(strcmp(op,"getk")==0){
    k=0;  val=-1; 
    get_k(root,variable-1,&k,&val);
    if(val==-1)
      printf("getk(%d) = not found\n",variable);
    else
      printf("getk(%d) = %d\n",variable,val);
    
  }else if(strcmp(op,"remove")==0){
    delete(variable,root);
    
  }else if(strcmp(op,"removek")==0){
    delete_k(variable,root);
    
    traversal(root);printf("\n");

  }

}//for 
/*
  insert(8);
  insert(9);
  insert(10);
  insert(11);
  insert(15);
  insert(16);
  insert(17);
  insert(18);
  insert(20);
  insert(23);
  
  get_k(root,0,&k,&val);
  printf("%d\n",val);
  search(11, &ch, root,&found,&num);

  if(found==0)
      printf("not found\n");
  else 
      printf("%d\n",num);


      printf("delete k %d",delete_k(1,root));
  printf("\n");
*/
}