#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct{
    char string[25];
    int num;
    int pre_or_post[MAX_SIZE];
    int inorder[MAX_SIZE];
}Input;

typedef struct{
    int arr[MAX_SIZE];
}Ouput;

typedef struct{
    int key;
    struct Treenode* left;
    struct Treenode* right;

}TreeNode;

TreeNode* prt_buildTree_r   (   int* preorder, int* inorder, 
                            int preStart, int preEnd,
					        int inStart, int inEnd     ) {

   	if(preStart > preEnd || inStart > inEnd)
		return NULL;

	TreeNode* root = malloc(sizeof(TreeNode));
	root->key = *(preorder+preStart);
	
	int in_rootidx; // Find root in inorder
	for(int i = inStart; i <= inEnd; i++) {
		if(inorder[i] == root->key) {
			in_rootidx = i;
			break;
		}
	}
	
	root->left  = prt_buildTree_r(preorder, inorder, preStart + 1, preEnd, inStart,
                                in_rootidx - 1);
	root->right = prt_buildTree_r(preorder, inorder, preStart+in_rootidx-inStart + 1,
						        preEnd, in_rootidx + 1, inEnd);
	return root;
}

TreeNode* pre_buildTree(int* preorder, int preorderSize,int* inorder, int inorderSize) { 
	if(inorder == NULL || preorder == NULL)
		return NULL;

	return prt_buildTree_r(preorder, inorder, 0, preorderSize - 1, 0, inorderSize - 1);
}

//---------------------------------------------------------------------------------

TreeNode* post_buildTree_r   (  int* postorder, int* inorder, 
                                int postStart, int postEnd,
                                int inStart, int inEnd     ) {

   	if(postEnd > postStart || inStart > inEnd)
		return NULL;

	TreeNode* root = malloc(sizeof(TreeNode));
	root->key = *(postorder+postStart);
	
	int in_rootidx; // Find root in inorder
	for(int i = inStart; i <= inEnd; i++) {
		if(inorder[i] == root->key) {
			in_rootidx = i;
			break;
		}
	}
	

	root->right = post_buildTree_r(postorder, inorder, 
                                    postStart-1,postEnd, 
                                    in_rootidx + 1, inEnd);
	root->left  = post_buildTree_r( postorder, inorder, 
                                    postStart-(inEnd-in_rootidx) - 1, postEnd, 
                                    inStart,in_rootidx - 1);
	return root;
}

TreeNode* post_buildTree(int* postorder, int postorderSize,int* inorder, int inorderSize) { 
	if(inorder == NULL || postorder == NULL)
		return NULL;

	return post_buildTree_r(postorder, inorder, postorderSize - 1 , 0 , 0 , inorderSize - 1);
}

void PrintPost(TreeNode* root){
    if(root==NULL)return;
    else{
        PrintPost(root->left);
        PrintPost(root->right);
        printf("%d ",root->key);
    }
}

void PrintPre(TreeNode* root){
    if(root==NULL)return;
    else{
        printf("%d ",root->key);
        PrintPre(root->left);
        PrintPre(root->right);
    }

}

int main(){
    int n;/*
    scanf("%d",&n);
    Input input[n];
    Ouput output[n];
    for(int i=0;i<n;i++){
        scanf("%s",&input[i].string);
        scanf("%d",&input[i].num);
        for(int j=0;j<input[i].num;j++){
            scanf("%d",&input[i].pre_or_post[j]);
        }
        for(int j=0;j<input[i].num;j++){
            scanf("%d",&input[i].inorder[j]);
        }
    }
    */
//read input
    int arr_pre[7]={1, 2 ,3, 4, 5, 6, 7};
    int arr_in[7] ={ 3 ,2 ,4 ,1 ,6 ,5 ,7};
    TreeNode* treehead1;
    treehead1=pre_buildTree(&arr_pre[0],7,&arr_in[0],7);
    PrintPost(treehead1);
    printf("\n");
    //PrintPre(treehead1);
    printf("\n");
//print output 
    int arr_post[10]={5, 6, 4, 7, 3, 8, 2, 10, 9, 1};
    int arr_pin[10] ={ 5, 4, 6, 3, 7, 2, 8, 1, 9, 10};
    TreeNode* treehead2;
    treehead2=post_buildTree(&arr_post[0],10,&arr_pin[0],10);
    PrintPre(treehead2);
    printf("\n");
    //PrintPost(treehead2);
    return 0;
}

