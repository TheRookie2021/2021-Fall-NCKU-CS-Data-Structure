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
    int n;
    scanf("%d",&n);
    Input input[n];
    TreeNode* ouput[n];
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
//read input



//print output 
    
    for(int i=0;i<n;i++){
        if(strcmp(input[i].string,"preorder-inorder")==0){
            ouput[i]=pre_buildTree(&input[i].pre_or_post[0],input[i].num,
                                   &input[i].inorder[0],input[i].num);
            PrintPost(ouput[i]);
        }else if(strcmp(input[i].string,"postorder-inorder")==0){
            ouput[i]=post_buildTree(&input[i].pre_or_post[0],input[i].num,
                                    &input[i].inorder[0],input[i].num);
            PrintPre(ouput[i]);

        }
        printf("\n");
    }

    return 0;
}
