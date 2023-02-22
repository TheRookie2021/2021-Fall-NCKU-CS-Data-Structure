
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2    /* 每一節點內至多可放資料筆數 */
#define MIN 1    /* 每一節點內至少需放資料筆數 */

typedef struct student {    /* 資料結構 */
		int count;                /* 節點資料數 */
		int key[MAX+1];            /* ID號碼--鍵值 */
		struct student *link[MAX+1];    /* 子鏈結 */
} NodeType;
NodeType *root;

int searchnode(int target, NodeType *p, int *k);
NodeType *removing(int, NodeType *);  /* 將資料從B-Tree中刪除 hw25*/
int deldata(int, NodeType *);    /* 刪除資料函數 */
void move(NodeType *, int);      /* 將節點中的資料逐一往左移 */
void replace(NodeType *, int);   /* 尋找替代節點 */
void restore(NodeType *, int);   /* 資料刪除後的調整工作 */
void getleft(NodeType *, int);   /* 向左兄弟節點借一筆資料 */
void getright(NodeType *, int);  /* 向右兄弟節點借一筆資料 */
void combine(NodeType *, int);   /* 節點合併 */


int searchnode(int target, NodeType *p, int *k)
{
	if(target < p->key[1]){
		*k = 0;
		return 0;
	}
	else{
		*k = p->count;
		while((target < p->key[*k]) && *k > 1)
			(*k)--;
		if(target == p->key[*k])
			return 1;
		else
			return 0;
	}
}
/* 將資料從B-Tree中刪除，若刪除後節點內資料筆數為0，則一併刪除該節點 */
NodeType *removing(int delId, NodeType *node)
{
	NodeType *p;

	if(!deldata(delId, node));
	else
		if(node->count == 0){
			p = node;
			node = node->link[0];
			free(p);
		}
	return node;
}

/* 將第 k 個資料從B-Tree中刪除，若刪除後節點內資料筆數為0，則一併刪除該節點 */
NodeType *removing_kth(int delId, NodeType *node)
{
	NodeType *p;

	if(!deldata(delId, node));
	else
		if(node->count == 0){
			p = node;
			node = node->link[0];
			free(p);
		}
	return node;
}

/* 將資料從B-Tree中移除，若刪除失敗則傳回0，否則傳回資料在節點中所在位置 */
int deldata(int delId, NodeType *p)
{
	int k;
	int found;

	if(p == NULL)
		return 0;
	else{
		if((found = searchnode(delId, p, &k)) != 0){
			if(p->link[k-1]){
			replace(p, k);
			if(!(found = deldata(p->key[k], p->link[k])))
				printf("  Key not found");
			}
			else
			move(p,k);
		}
		else
			found = deldata(delId, p->link[k]);
		if(p->link[k] != NULL){
		      if(p->link[k]->count < MIN)
			restore(p, k);
		}
		return found;
	}
}

/* 將節點中的資料從k的位置逐一左移 */
void move(NodeType *p, int k)
{
	int i;

	for(i = k+1; i <= p->count; i++){
		p->key[i-1] = p->key[i];
		p->link[i-1] = p->link[i];
	}
	p->count--;
}

/* 尋找刪除非樹葉時的替代資料 */
void replace(NodeType *p, int k)
{
	NodeType *q;

	for(q = p->link[k]; q->link[0]; q = q->link[0]);
		p->key[k] = q->key[1]; 
}

/* 資料刪除後，重新調整為B-Tree */
void restore(NodeType *p, int k)
{
	if(k == 0){  /* 刪除資料為節點中的第一筆資料 */
		if(p->link[1]->count > MIN)
			getright(p, 1);
		else
			combine(p, 1);
	}
	else
		if(k == p->count){  /* 刪除資料為節點中的最後一筆資料 */
			if(p->link[k-1]->count > MIN)
					getleft(p, k);
			else
				combine(p, k);
		}
		else  /* 刪除資料為節點中其他位置的資料 */
			if(p->link[k-1]->count > MIN)
				getleft(p, k);
			else
				if(p->link[k+1]->count > MIN)
					getright(p, k+1);
				else
					combine(p, k);
}

/* 向左兄弟節點借資料時，做資料右移的動作 */
void getleft(NodeType *p, int k)
{
	int c;
	NodeType *t;

	t = p->link[k];
	for(c = t->count; c > 0; c--){
		t->key[c+1] = t->key[c];
		t->link[c+1] = t->link[c];
	}
	t->link[1] = t->link[0];
	t->count++;
	t->key[1] = p->key[k];
	t = p->link[k-1];
	p->key[k] = t->key[t->count];
	p->link[k]->link[0] = t->link[t->count];
	t->count--;
}

/* 向右兄弟節點借資料時，做左移的動作 */
void getright(NodeType *p, int k)
{
	int c;
	NodeType *t;

	t = p->link[k-1];
	t->count++;
	t->key[t->count] = p->key[k];
	t->link[t->count] = p->link[k]->link[0];
	t = p->link[k];
	p->key[k] = t->key[1];
	t->link[0] = t->link[1];
	t->count--;
	for(c = 1; c <= t->count; c++){
		t->key[c] = t->key[c+1];
		t->link[c] = t->link[c+1];
	}
}

/* 將三個節點中的資料合併至一個節點中 */
void combine(NodeType *p, int k)
{
	int c;
	NodeType *l, *q;

	q = p->link[k];
	l = p->link[k-1];
	l->count++;
	l->key[l->count] = p->key[k];
	l->link[l->count] = q->link[0];
	for(c = 1; c <= q->count; c++){
		l->count++;
		l->key[l->count] = q->key[c];
		l->link[l->count] = q->link[c];
	}
	for(c = k; c < p->count; c++){
		p->key[c] = p->key[c+1];
		p->link[c] = p->link[c+1];
	}
	p->count--;
	free(q);
}
