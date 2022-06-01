#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define true 1==1
#define false 1!=1
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
typedef int bool;

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
} TreeNode;

TreeNode* addNode(TreeNode *t, int data) {
	TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
	newNode->key = data;
	newNode->left = NULL;
	newNode->right = NULL;
	TreeNode *pCurrent = t;
	TreeNode *pParent = t;
	if(t == NULL){
		t = newNode;
	} else {
		while(pCurrent->key != data){
			pParent = pCurrent;
			if(pCurrent->key > data){
				pCurrent = pCurrent->left;
				if(pCurrent == NULL){
					pParent->left = newNode;
					return t;
				}
			} else{
				pCurrent = pCurrent->right;
				if(pCurrent == NULL){
					pParent->right = newNode;
					return t;
				}
			}
		}
	}
	return t;
}

int checkTreeDeep(TreeNode *tree) {
	if(tree== NULL)
		return 0;
	int deepLeft = checkTreeDeep(tree->left);
	if(deepLeft == -1)
		return -1;
	int deepRight = checkTreeDeep(tree->right);
	if(deepRight == -1)
		return -1;
	int deepDif = abs(deepLeft - deepRight);
	if(deepDif > 1)
		return -1;
	else
		return __max(deepLeft, deepRight) + 1;
		
}

bool checkBalanceTree(TreeNode *tree) {
	if(checkTreeDeep(tree) <= 0)
		return false;
	else
		return true;
}

bool binSearch(TreeNode *root, int value) {
	if(root == NULL)
		return false;
	if(root->key == value)
		return true;
	if(root->key < value)
        return binSearch(root->left, value);
    else return binSearch(root->right, value);
}


int main() {
    
    const int CT = 50;
    
	TreeNode *tree[CT];
    
    srand(time(NULL));
    
    for(int i = 0; i < CT; ++i){
    	tree[i] = NULL;
    	tree[i] = addNode(tree[i], rand()%100);
    	for(int node = 1; node < 10000; ++node){
    		addNode(tree[i], rand()%100);
		}
	}
    
	double prcnt = 0.0;
	for(int i = 0; i < CT; ++i){
		if(checkBalanceTree(tree[i])){
			prcnt = prcnt + 1.0;
		}
	}
	prcnt = (prcnt/CT)*100.0;
	printf("Out of %d trees %d%% are balanced \n", CT, (int)prcnt);
	
	
	for(int i = 0; i < CT; ++i){
		printf("50 in tree%d = %s \n", i+1, binSearch(tree[i], 50)? "true" : "false");
	}
	
	
    return 0;
}