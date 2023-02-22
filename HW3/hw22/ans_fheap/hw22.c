#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 200
typedef struct _Node {
  int key;
  int value;
  int degree;
  struct _Node *left_sibling;
  struct _Node *right_sibling;
  struct _Node *parent;
  struct _Node *child;
  bool mark;
  bool visited;
} Node;

typedef struct fibanocci_heap {
  int n;
  Node *min;
} Fheap;

Fheap *make_Fheap();
void insertion(Fheap *H, Node *new, int key, int val);
Node *extract_min(Fheap *H);
void consolidate(Fheap *H);
void Fheap_link(Fheap *H, Node *y, Node *x);
void decrease_key(Fheap *H, Node *Node, int key);
void cut(Fheap *H, Node *Node_to_be_decrease, Node *parent_Node);
void cascading_cut(Fheap *H, Node *parent_Node);
void Delete_Node(Fheap *H, int dec_key,int val);

Fheap *make_Fheap() {
  Fheap *H;
  H = (Fheap *)malloc(sizeof(Fheap));
  H->n = 0;
  H->min = NULL;
  return H;
}


// Inserting Nodes
void insertion(Fheap *H, Node *new,int key, int val) {
  new = (Node *)malloc(sizeof(Node));
  new->key = key;
  new->value=val;
  new->degree = 0;
  new->mark = false;
  new->parent = NULL;
  new->child = NULL;
  new->visited = false;
  new->left_sibling = new;
  new->right_sibling = new;
  if (H->min == NULL) {
    H->min = new;
  } else {
    H->min->left_sibling->right_sibling = new;
    new->right_sibling = H->min;
    new->left_sibling = H->min->left_sibling;
    H->min->left_sibling = new;
    if (new->key < H->min->key) {
      H->min = new;
    }
  }
  (H->n)++;
}

// Consolidate function
void consolidate(Fheap *H) {
  int i=0, d=0;
  
  Node *A[MAX], *x, *y;
  for (i = 0; i <= MAX; i++) {
    A[i] = NULL;
  }
  x = H->min;
  do {
    d = x->degree;
    while (A[d] != NULL) {
      y = A[d];
      if (x->key > y->key) {
        Node *exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min)
        H->min = x;
      Fheap_link(H, y, x);
      if (y->right_sibling == x)
        H->min = x;
      A[d] = NULL;
      d++;
    }
    // printf("x key: %d, x deg: %d, d:%d\n",x->key,x->degree,d);
      A[d] = x;
    /*
      for (int j = 0; j <= MAX; j++) {
      if(A[j]!=NULL)
        printf("A[j] %d, j: %d\n",A[j]->key,j);
  }
    */
      x = x->right_sibling;
  } while (x != H->min);

  H->min = NULL;
  for (i = 0; i < MAX; i++) {
    if (A[i] != NULL) 
    {
      A[i]->left_sibling = A[i];
      A[i]->right_sibling = A[i];
      if (H->min == NULL) {
        H->min = A[i];
        
    //printf("H->min = A[i], min:%d\n",A[i]->key);
      } 
      else 
      {
        H->min->left_sibling->right_sibling = A[i];
        A[i]->right_sibling = H->min;
        A[i]->left_sibling = H->min->left_sibling;
        H->min->left_sibling = A[i];
        if (A[i]->key < H->min->key) {
          H->min = A[i];
        }

    //printf("H->min = A[i], min:%d\n",A[i]->key);
      }
    }//if(A[i] != NULL)
    else{
      
    }
  }
  if(H->min==H->min->child)H->min->child=NULL;//biggist bugggggg!
}

// Linking
void Fheap_link(Fheap *H, Node *y, Node *x) {
  y->right_sibling->left_sibling = y->left_sibling;
  y->left_sibling->right_sibling = y->right_sibling;

  if (x->right_sibling == x)
    H->min = x;

  y->left_sibling = y;
  y->right_sibling = y;
  y->parent = x;

  if (x->child == NULL) {
    x->child = y;
  }
  y->right_sibling = x->child;
  y->left_sibling = x->child->left_sibling;
  x->child->left_sibling->right_sibling = y;
  x->child->left_sibling = y;
  if ((y->key) < (x->child->key))
    x->child = y;

  (x->degree)++;
}

// Extract min
Node *extract_min(Fheap *H) {
  if (H->min == NULL){

    return NULL;
  }
  else {
    
    Node *temp = H->min;
    Node *pntr;
    pntr = temp;
    Node *x = NULL;
    if (temp->child != NULL) {
      x = temp->child;
      do {
        pntr = x->right_sibling;
        (H->min->left_sibling)->right_sibling = x;
        x->right_sibling = H->min;
        x->left_sibling = H->min->left_sibling;
        H->min->left_sibling = x;
        if (x->key < H->min->key)
          H->min = x;
        x->parent = NULL;
        x = pntr;
      } while (pntr != temp->child);
    }

    (temp->left_sibling)->right_sibling = temp->right_sibling;
    (temp->right_sibling)->left_sibling = temp->left_sibling;
    H->min = temp->right_sibling;

    if (temp == temp->right_sibling && temp->child == NULL){

      H->min = NULL;
    }
    else {
      H->min = temp->right_sibling;
      consolidate(H);
    //printf("after consolidate, min:%d\n",H->min->key);
    }
    H->n = H->n - 1;
    return temp;
  }
  return H->min;
}

void cut(Fheap *H, Node *Node_to_be_decrease, Node *parent_Node) {
  Node *temp_parent_check;

  if (Node_to_be_decrease == Node_to_be_decrease->right_sibling)
    parent_Node->child = NULL;

  Node_to_be_decrease->left_sibling->right_sibling = Node_to_be_decrease->right_sibling;
  Node_to_be_decrease->right_sibling->left_sibling = Node_to_be_decrease->left_sibling;
  if (Node_to_be_decrease == parent_Node->child)
    parent_Node->child = Node_to_be_decrease->right_sibling;
  (parent_Node->degree)--;

  Node_to_be_decrease->left_sibling = Node_to_be_decrease;
  Node_to_be_decrease->right_sibling = Node_to_be_decrease;
  H->min->left_sibling->right_sibling = Node_to_be_decrease;
  Node_to_be_decrease->right_sibling = H->min;
  Node_to_be_decrease->left_sibling = H->min->left_sibling;
  H->min->left_sibling = Node_to_be_decrease;

  Node_to_be_decrease->parent = NULL;
  Node_to_be_decrease->mark = false;
}

void cascading_cut(Fheap *H, Node *parent_Node) {
  Node *aux;
  aux = parent_Node->parent;
  if (aux != NULL) {
    if (parent_Node->mark == false) {
      parent_Node->mark = true;
    } else {
      cut(H, parent_Node, aux);
      cascading_cut(H, aux);
    }
  }
}

void decrease_key(Fheap *H, Node *Node_to_be_decrease, int new_key) {
  Node *parent_Node;
  if (H == NULL) {
    return;
  }
  if (Node_to_be_decrease == NULL) {
    return;
  }
  else {
    if (Node_to_be_decrease->key < new_key) {
      return;
    } 
    else 
    {
      Node_to_be_decrease->key = new_key;
      parent_Node = Node_to_be_decrease->parent;
      if ((parent_Node != NULL) && (Node_to_be_decrease->key < parent_Node->key)) {
        cut(H, Node_to_be_decrease, parent_Node);
        cascading_cut(H, parent_Node);
        
       // printf("after cut, min:%d\n",H->min->key);
      }
      if (Node_to_be_decrease->key < H->min->key) {
        H->min = Node_to_be_decrease;
        
        //printf("after cut, min:%d\n",H->min->key);
      }
    }
  }
}

void *find_Node(Fheap *H, Node *n, int key,int val, int new_key) {
  Node *find_use = n;
  Node *f = NULL;
  find_use->visited = true;
  if (find_use->key == key && find_use->value==val) {
    find_use->visited = false;
    f = find_use;
    decrease_key(H, f, new_key);
  }
  if (find_use->child != NULL) {
    find_Node(H, find_use->child, key,val, new_key);
  }
  if ((find_use->right_sibling->visited != true)) {
    find_Node(H, find_use->right_sibling, key,val, new_key);
  }

  find_use->visited = false;
}

void Delete_Node(Fheap *H, int dec_key,int val) {
 // printf("min:%d\n",H->min->key);
  Node *p = NULL;
  find_Node(H, H->min, dec_key, val, -1000);
  p = extract_min(H);
  //printf("deletkey %d, p.value%d\n",dec_key, p->value);
  
 // printf("after extract, min:%d\n",H->min->key);
}

// Printing the heap
void print_heap(Node *n) {
  Node *x;
  for (x = n;; x = x->right_sibling) {
    if (x->child == NULL) {
      printf("node with no child (%d) \n", x->key);
    } else {
      printf("NODE(%d) with child (%d)\n", x->key, x->child->key);
      print_heap(x->child);
    }
    if (x->right_sibling == n) {

      break;
    }
  }
}

int main() {
  Node *new_Node, *extracted_min, *Node_to_be_decrease, *find_use;//temp use
  Fheap *heap;
  int new_key,new_val, 
      dec_key,dec_val,
      delete_key,delete_val, 
      dec_amount;
  
  char operation[20];
  int operation_no;
  heap = make_Fheap();
  while(1)
  {
    scanf("%s", operation);
    operation_no=0;
    if(strcmp(operation,"insert")==0){
      operation_no=1;
    }else if(strcmp(operation,"extract")==0){
      operation_no=2;
    }else if(strcmp(operation,"decrease")==0){
      operation_no=3;
    }else if(strcmp(operation,"delete")==0){
      operation_no=4;
    }else if(strcmp(operation,"quit")==0){
      operation_no=5;
    }
    switch (operation_no) {
      case 1://insert
        scanf("%d", &new_key);
        scanf("%d", &new_val);
        insertion(heap, new_Node,new_key, new_val);
        break;

      case 2://extract
      if(heap->min!=NULL)
      {
        extracted_min = extract_min(heap);
        printf("(%d)%d\n", extracted_min->key,extracted_min->value);
      }
        break;

      case 3://decrease
        scanf("%d", &dec_key);
        scanf("%d", &dec_val);
        scanf("%d", &dec_amount);
        find_use = heap->min;
        new_key=dec_key-dec_amount;
        find_Node(heap, find_use, dec_key,dec_val,new_key);//replace with new_key
        break;

      case 4://delete Node
          scanf("%d", &delete_key);
          scanf("%d", &delete_val);
          Delete_Node(heap, delete_key,delete_val);
          break;

      case 5:
        exit(0);
        
      default: break;
    }
  }
  return 0;
}