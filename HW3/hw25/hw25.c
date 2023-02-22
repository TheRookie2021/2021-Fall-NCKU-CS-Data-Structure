/* File name: Btree.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2    /* 每一節點內至多可放資料筆數 */
#define MIN 1    /* 每一節點內至少需放資料筆數 */

typedef struct student {    /* 資料結構 */
		int count;                /* 節點資料數 */
		int id[MAX+1];            /* ID號碼--鍵值 */
		char name[MAX+1][11];     /* 姓名 */
		int score[MAX+1];         /* 分數 */
		struct student *link[MAX+1];    /* 子鏈結 */
} NodeType;

NodeType *root;
void insertFunction(void);  /* 新增函數 */
NodeType *access(int, char *, int, NodeType *);  /* 將新增資料加入B-Tree中 hw25*/
/* 從根節點往下逐一尋找插入點，將資料新增的函數 */
int topdown(int, char *, int, NodeType *, int *, char *, int *, NodeType **); 
/* 將資料置於某特定節點中 */
void putdata(int, char *, int, NodeType *, NodeType *, int);
void broken(int, char *, int, NodeType *, NodeType *, int, 
		   int *, char *,int *, NodeType **);  /* 將一節點劃分為二 */
void updateFunction(void);              /* 修改函數 */
void deleteFunction(void);              /* 刪除函數 */
NodeType *removing(int, NodeType *);  /* 將資料從B-Tree中刪除 hw25*/
int deldata(int, NodeType *);    /* 刪除資料函數 */
void move(NodeType *, int);      /* 將節點中的資料逐一往左移 */
void replace(NodeType *, int);   /* 尋找替代節點 */
void restore(NodeType *, int);   /* 資料刪除後的調整工作 */
void getleft(NodeType *, int);   /* 向左兄弟節點借一筆資料 */
void getright(NodeType *, int);  /* 向右兄弟節點借一筆資料 */
void combine(NodeType *, int);   /* 節點合併 */
void listFunction(void);                /* 輸出函數 */
void queryFunction(void);                /* 查詢函數 */
NodeType * search(int, NodeType *, int *); /* 依鍵值搜尋某特定節點函數 hw25*/
int searchnode(int, NodeType *, int *);     /* 依鍵值搜尋節點中某特定資料函數 hw25*/
void show(NodeType *);            /* 以遞迴方式依序將資料輸出 */
void quit(void);                   /* 結束函數 */


/* 結束本系統 */
void quit(void)
{
	printf("\n  Thanks for using, bye bye!!");
	getchar();
	exit(0);
}

int main()
{
	int flag=0,times=1;/* times是判斷是否為第一次進入需要載入輸入檔案*/
	char choice, ans;

	while(1){
		do{
			printf("\n");
			puts("  *********************");
			puts("        1.insert");
			puts("        2.update");
			puts("        3.delete");
			puts("        4.list");
			puts("        5.query");
			puts("        6.quit");
			puts("  *********************");
			printf("  Please enter your choice(1..6): ");
			choice = getchar();
			while (getchar()!='\n') continue;
			printf("\n");
			switch(choice)	{
				case '1':
					insertFunction();
					break;
				case '2':
					updateFunction();
					break;
				case '3':
					deleteFunction();
					break;
				case '4':
					listFunction();
					break;
				case '5':
					queryFunction();
					break;
				case '6':printf("  Are you sure? (Y/N): ");
					ans = getchar();
					while (getchar()!='\n') continue;
					ans = toupper(ans);
					if(ans == 'Y'){
						quit();
					}
					break;
				default: puts("  Choice error!!");
			}
		}  while(choice != '6');
	}
	return 0;
}

/* 新增一筆資料，並調整為B-Tree */
void insertFunction(void)
{     
/* position記錄資料在節點中新增的位置 */
	int position, insertId, insertScore; 
	NodeType *node;
	char ans, insertName[11];

	puts("\n  ---- INSERT ----");
	puts("  Please enter detail data");
	printf("  ID number: ");
	scanf("%d", &insertId);
	while (getchar()!='\n') continue;
	/* 找尋新增資料是否已存在，若存在，則顯示錯誤 */
	node = search(insertId, root, &position);
	if(node != NULL)
		puts(" ID number has existed!!");
	else{
		printf("  Name: ");  /* 要求輸入其他詳細資料 */
		scanf("%s'", insertName);
		while (getchar()!='\n') continue;
		printf("  Score: ");
		scanf("%d", &insertScore);
		while (getchar()!='\n') continue;
		printf("  Are you sure? (Y/N): ");
		ans = getchar();
		while (getchar()!='\n') continue;
		printf("\n");
		ans = toupper(ans);
		if(ans == 'Y')
			root = access(insertId, insertName, insertScore,root);
	}
}

/* 將新增資料加入B-TREE，node指加入節點，傳回值為root所在 */
NodeType *access(int appId, char *appName, int appScore, NodeType *node)
{
	int xId, xScore, pushup;  /* pushup判斷節點是否需劃分而往上新增一節點 */
	char xName[11];
	NodeType *xr, *p;

	pushup = topdown(appId,appName,appScore,node,&xId,xName,&xScore, &xr);
	if(pushup){  /* 若pushup為1，則配置一個新節點，將資料放入 */
		p = (NodeType *) malloc(sizeof(NodeType));
		p->link[0] = NULL;
		p->link[1] = NULL;
		p->link[2] = NULL;
		p->count = 1;
		p->id[1] = xId;
		strcpy(p->name[1], xName);
		p->score[1] = xScore;
		p->link[0] = root;
		p->link[1] = xr;
		return p;
	}
	return node;
}

/* 從樹根往下尋找資料加入節點，將資料新增於B-Tree中，參數p為目前所在節點，
xr記錄資料所對應的子鏈結 */
int topdown(int newId, char *newName, int newScore, NodeType *p,
			int *xId, char *xName, int *xScore, NodeType **xr)
{
	int k;

	if(p == NULL){  /* p為NULL表示新增第一筆資料 */
		*xId = newId;
		strcpy(xName, newName);
		*xScore = newScore;
		*xr = NULL;
		return 1;
	}
	else{
		if(searchnode(newId, p, &k)){
		/* 找尋新增資料鍵值是否重覆，若重覆則顯示錯誤 */
			puts("  Data error, ID number has existed!!");
			quit();
			return 0;
		}
		/* 繼續往下找尋新增節點 */
		if(topdown(newId, newName, newScore, p->link[k], xId, xName,
				 xScore, xr))
		{
			if(p->count < MAX){
			/* 若新增節點有足夠的空間存放資料，則將資料直接加入該節點 */
				putdata(*xId, xName, *xScore, *xr, p, k);
				return 0;
			}
			else{
			      /* 若無足夠空間，則須劃分節點 */
				broken(*xId, xName, *xScore, *xr, p, k, xId, xName,
						xScore, xr);
				return 1;
			}
		}
		else
			return 0;
	}
}

/* 將新增資料直接加入於節點中，xr為新增資料對應的子鏈結所在，p為資料加入的節點 */
void putdata(int xId, char *xName, int xScore, NodeType *xr,
		    NodeType *p, int k)
{
	int i;

	/* 將節點中的資料逐一右移，以空出新增資料加入的位置 */
	for(i = p->count; i > k; i--){
		p->id[i+1] = p->id[i];
		strcpy(p->name[i+1], p->name[i]);
		p->score[i+1] = p->score[i];
		p->link[i+1] = p->link[i];
	}
	p->id[k+1] = xId;
	strcpy(p->name[k+1], xName);
	p->score[k+1] = xScore;
	p->link[k+1] = xr;
	p->count++;
}

/* 將節點一分為二，yr為劃分後新增加的節點 */
void broken(int xId, char *xName, int xScore, NodeType *xr, NodeType *p,
			int k, int *yId, char *yName, int *yScore, NodeType **yr)
{
	int i;
	int median;  /* median記錄從何處劃分節點 */

	if(k <= MIN)
		median = MIN;
	else
		median = MIN + 1;
	*yr = (NodeType *) malloc(sizeof(NodeType));
	/* 將資料從劃分處開始搬移至新節點中 */
	for(i = median + 1; i <= MAX; i++){
		(*yr)->id[i-median] = p->id[i];
		strcpy((*yr)->name[i-median], p->name[i]);
		(*yr)->score[i-median] = p->score[i];
		(*yr)->link[i-median] = p->link[i];
	}
	(*yr)->count = MAX - median;
	p->count = median;
	if(k <= MIN)
		putdata(xId, xName, xScore, xr, p, k);
	else
		putdata(xId, xName, xScore, xr, *yr, k - median);
	*yId = p->id[p->count];
	strcpy(yName, p->name[p->count]);
	*yScore = p->score[p->count];
	(*yr)->link[0] = p->link[p->count];
	p->count--;
}

/* 修改資料函數 */
void updateFunction(void)
{
	int updateId, updateScore, position;
	char ans, updateName[11];
	NodeType *node;

	puts("\n  ---- UPDATE ----");
	printf("  Please enter ID number: ");
	scanf("%d", &updateId);
	while (getchar()!='\n') continue;
	node = search(updateId, root, &position);  /* 找尋欲修改資料所在節點位置 */
	if(node != NULL){
		printf("  Original name: %s\n", node->name[position]);
		printf("  Please enter new name: ");
		scanf("%10s", updateName);
		while (getchar()!='\n') continue;
		printf("  Original score: %d\n", node->score[position]);
		printf("  Please enter new score: ");
		scanf("%d", &updateScore);
		while (getchar()!='\n') continue;
		printf("  Are you sure? (Y/N): ");
		ans = getchar();
		while (getchar()!='\n') continue;
		printf("\n");
		ans = toupper(ans);
		if(ans == 'Y'){
			node->score[position] = updateScore;
			strcpy(node->name[position], updateName);
		}
	}
	else
		puts("  ID number not found!!");
}

/* 刪除資料函數 */
void deleteFunction(void)
{
	int delId, position;  /* position記錄刪除資料在節點中的位置 */
	char ans;
	NodeType *node;

	puts("\n  ---- DELETE ----");
	printf("  Please enter ID number: ");
	scanf("%d", &delId);
	while (getchar()!='\n') continue;
	node = search(delId, root, &position);
	if(node != NULL){
		printf("  Are you sure? (Y/N): ");
		ans = getchar();
		while (getchar()!='\n') continue;
		printf("\n");
		ans = toupper(ans);
		if(ans == 'Y')
			root = removing(delId, root);
	}
	else
		puts("  ID number not found!!");
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
			if(!(found = deldata(p->id[k], p->link[k])))
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
		p->id[i-1] = p->id[i];
		strcpy(p->name[i-1], p->name[i]);
		p->score[i-1] = p->score[i];
		p->link[i-1] = p->link[i];
	}
	p->count--;
}

/* 尋找刪除非樹葉時的替代資料 */
void replace(NodeType *p, int k)
{
	NodeType *q;

	for(q = p->link[k]; q->link[0]; q = q->link[0]);
		p->id[k] = q->id[1]; strcpy(p->name[k], q->name[1]);
		p->score[k] = q->score[1];
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
		t->id[c+1] = t->id[c];
		strcpy(t->name[c+1], t->name[c]);
		t->score[c+1] = t->score[c];
		t->link[c+1] = t->link[c];
	}
	t->link[1] = t->link[0];
	t->count++;
	t->id[1] = p->id[k];
	strcpy(t->name[1], p->name[k]);
	t->score[1] = p->score[k];
	t = p->link[k-1];
	p->id[k] = t->id[t->count];
	strcpy(p->name[k], t->name[t->count]);
	p->score[k] = t->score[t->count];
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
	t->id[t->count] = p->id[k];
	strcpy(t->name[t->count], p->name[k]);
	t->score[t->count] = p->score[k];
	t->link[t->count] = p->link[k]->link[0];
	t = p->link[k];
	p->id[k] = t->id[1];
	strcpy(p->name[k], t->name[1]);
	p->score[k] = t->score[1];
	t->link[0] = t->link[1];
	t->count--;
	for(c = 1; c <= t->count; c++){
		t->id[c] = t->id[c+1];
		strcpy(t->name[c], t->name[c+1]);
		t->score[c] = t->score[c+1];
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
	l->id[l->count] = p->id[k];
	strcpy(l->name[l->count], p->name[k]);
	l->score[l->count] = p->score[k];
	l->link[l->count] = q->link[0];
	for(c = 1; c <= q->count; c++){
		l->count++;
		l->id[l->count] = q->id[c];
		strcpy(l->name[l->count], q->name[c]);
		l->score[l->count] = q->score[c];
		l->link[l->count] = q->link[c];
	}
	for(c = k; c < p->count; c++){
		p->id[c] = p->id[c+1];
		strcpy(p->name[c], p->name[c+1]);
		p->score[c] = p->score[c+1];
		p->link[c] = p->link[c+1];
	}
	p->count--;
	free(q);
}

/* 資料輸出函數 */
void listFunction(void)
{
	puts("\n  ---- LIST ----");
	puts("  *******************************");
	puts("      ID     NAME       SCORE");
	puts("   =============================");
	show(root);
	puts("  *******************************");
}

/* 以遞迴方式輸出節點資料，輸出資料採中序法，nd為欲輸出資料的節點 */
void show(NodeType *nd)
{
	if(nd != NULL){
		if(nd->count > 0){
			if(nd->count == 1){
				show(nd->link[0]);
				printf("      %-6d %-10s %4d\n",
					nd->id[1], nd->name[1], nd->score[1]);
				show(nd->link[1]);
			}
			else
			if(nd->count == 2){
				show(nd->link[0]);
				printf("      %-6d %-10s %4d\n",
						nd->id[1], nd->name[1], nd->score[1]);
				show(nd->link[1]);
				printf("      %-6d %-10s %4d\n",
						nd->id[2], nd->name[2], nd->score[2]);
				show(nd->link[2]);
			}
		}
	}
}

/* 查詢某一特定資料 */
void queryFunction(void)
{
	int queryId, position;
	NodeType *quenode;

	puts("\n  ---- QUERY ----");
	printf("  Please enter ID number: ");
	scanf("%d", &queryId);
	while (getchar()!='\n') continue;
	quenode = search(queryId, root, &position);
	if(quenode != NULL){
		printf("  ID number: %d\n", quenode->id[position]);
		printf("  Name: %s\n", quenode->name[position]);
		printf("  Score: %d\n", quenode->score[position]);
	}
	else
		puts("  ID number not found!!");
}

/* 搜尋某一鍵值所在節點，target為搜尋鍵值，傳回值為target所在節點指標，
若沒有找到則傳回NULL */
NodeType *search(int target, NodeType *node, int *targetpos)
{
	if(node == NULL)
		return NULL;
	else
		if(searchnode(target, node, targetpos))
			return node;
		else
			return search(target, node->link[*targetpos], targetpos);
}

/* 搜尋某一鍵值在節點中的位置，target為搜尋鍵值，k記錄鍵值所在位置，
傳回0表示搜尋失敗，傳回1表示搜尋成功 */
int searchnode(int target, NodeType *p, int *k)
{
	if(target < p->id[1]){
		*k = 0;
		return 0;
	}
	else{
		*k = p->count;
		while((target < p->id[*k]) && *k > 1)
			(*k)--;
		if(target == p->id[*k])
			return 1;
		else
			return 0;
	}
}