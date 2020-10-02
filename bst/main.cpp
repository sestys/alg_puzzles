#include <bits/stdc++.h>

using namespace std;

class Node {
public:
	int k_min;
	int k_max;
	Node* left;
	Node* right;
	Node(int min, int max) {
		k_min = min;
		k_max = max;
		left = NULL;
		right = NULL;
	}
};

Node* rightTrim(Node* root, int k_max);
Node* leftTrim(Node* root, int k_min);
Node* del(Node* root, int k_min, int k_max);
Node* rightMerge(Node* root, int &k_max);
Node* leftMerge(Node* root, int &k_min);
int findMin(Node* root);
int findMax(Node* root);

void printGraph(Node* root){
	if (!root){
		printf("x\n");
	} else {
		printf("[%u...%u]\n", root->k_min, root->k_max);
		printGraph(root->left);
		printGraph(root->right);
	}
}

Node* popMaxKeys(Node* root, int &min, int &max){
	
	if (!root){
		return NULL;
	}
	if (root->right){
		root->right = popMaxKeys(root->right, min, max);
		return root;
	} else {
		min = root->k_min;
		max = root->k_max;
		return root->left;
	}
}

int fastscan()
{
	char c;
    	int number = 0;
    	c = getchar();
	while(c>=58 || c<=47) c=getchar();
    	// Keep on extracting characters if they are integers
    	// i.e ASCII Value lies from '0'(48) to '9' (57)
    	for (; (c>47 && c<58); c=getchar())
        	number = number *10 + c - 48;
	return number;
}

Node* insert(Node* root, int k_min, int k_max){
	if (root == NULL){
		return new Node(k_min, k_max);
	}
	if ((k_min >= root->k_min) && (k_max <= root->k_max)){
		return root;
	}
	if (k_max < root->k_min - 1){
		root->left = insert(root->left, k_min, k_max);
	} 
	else if (k_min > root->k_max + 1){
		root->right = insert(root->right, k_min, k_max);
	}
       	else {
		if (k_min < root->k_min){
			root->left = del(root->left, k_min, root->k_min - 1);
			if (root->left){
				root->left = leftMerge(root->left, k_min);
			}
			root->k_min = k_min;
		}
		if (k_max > root->k_max){
			root->right = del(root->right, root->k_max + 1, k_max);
			if (root->right){
				root->right = rightMerge(root->right, k_max);
			}
			root->k_max = k_max;
		}
	}
	return root;
}

Node* leftMerge(Node* root, int &k_min){
	if ((k_min >= root->k_min) && (k_min <= root->k_max + 1)){
		k_min = root->k_min;
		return root->left;
	}
	if (k_min > root->k_max + 1){
		if (root->right){
			root->right = leftMerge(root->right, k_min);
		}
		return root;
	}
	if (k_min < root->k_min){
		if (root->left){
			return leftMerge(root, k_min);
		}
		return NULL;
	}
	return root;
}

Node* rightMerge(Node* root, int &k_max){
	if ((k_max >= root->k_min - 1) && (k_max <= root->k_max)){
		k_max = root->k_max;
		return root->right;
	}
	if (k_max < root->k_min - 1){
		if (root->left){
			root->left = rightMerge(root->left, k_max);
		}
		return root;
	}
	if (k_max > root->k_max){
		if (root->right){
			return rightMerge(root->right, k_max);
		}
		return NULL;
	}
	return root;
}

Node* del(Node* root, int k_min, int k_max){
	if (!root){
		return NULL;
	} // 1L
	if (k_max < root->k_min){
		root->left = del(root->left, k_min, k_max);
	} 
	else if (k_min > root->k_max){ //1R
		root->right = del(root->right, k_min, k_max);
	} 
	else if((k_max < root->k_max) && ((k_min == root->k_min) || (k_min == root->k_min - 1))){//2L
		root->k_min = k_max + 1;
	}
       	else if ((k_min > root->k_min) && ((k_max == root->k_max) || (k_max == root->k_max + 1))){
		root->k_max = k_min - 1;
	}
       	else if ((k_min < root->k_min - 1) && (k_max < root->k_max)){ //3L
		root->left = del(root->left, k_min, root->k_min - 2);
		root->k_min = k_max + 1;
	}
       	else if ((root->k_min < k_min) && (root->k_max + 1 < k_max)){ //3R
		root->right = del(root->right, root->k_max + 2, k_max);
		root->k_max = k_min - 1;
	}
       	else if ((root->k_min < k_min) && (k_max < root->k_max)){ //4
		if (k_min - root->k_min <= root->k_max - k_max){
			root->left = insert(root->left, root->k_min, k_min - 1);
			root->k_min = k_max + 1;
		} else {
			root->right = insert(root->right, k_max + 1, root->k_max);
			root-> k_max = k_min - 1;
		}
	} else { //5-7
		int tree_min = findMin(root);
		int tree_max = findMax(root);
		if ((k_min <= tree_min) && (k_max >tree_max)){
			return NULL;
		}
		if ((k_min <= tree_min) && (tree_max > k_max)){
			return del(root->right, root->k_max + 2, k_max);
		}
		if ((tree_min < k_max) && (tree_max <= k_max)){
			return del(root->left, k_min, root->k_min - 2);
		}
		if ((tree_min < k_min) && (tree_max > k_max)){
			root->left = leftTrim(root->left, k_min);
			root->right = rightTrim(root->right, k_max);
			int min, max;
			min = 0;
			max = 0;			
			root->left = popMaxKeys(root->left, min, max);
			root->k_min = min;
			root->k_max = max;
		}
	}
	return root;
}

Node* leftTrim(Node* root, int k_min){
	if (!root){
		return NULL;
	}
	if ((root->k_min == k_min) || (root->k_min - 1 == k_min)){
		return root->left;
	}
	if (root->k_min > k_min){
		return leftTrim(root->left, k_min);
	}
	if (root->k_max + 1 == k_min){
		root->right = NULL;
		return root;
	}
	if (root->k_max < k_min){
		root->right = leftTrim(root->right, k_min);
		return root;
	} else {
		root->k_max = k_min - 1;
		root->right = NULL;
		return root;
	}
}

Node* rightTrim(Node* root, int k_max){
	if (!root){
		return NULL;
	}
	if ((k_max == root->k_max) || (k_max == root->k_max + 1)){
		return root->right;
	}
	if (root->k_max <k_max){
		return rightTrim(root->right, k_max);
	}
	if (root->k_min - 1 == k_max){
		root->left = NULL;
		return root;
	}
	if (root->k_min > k_max){
		root->left = rightTrim(root->left, k_max);
		return root;
	} else {
		root->k_min = k_max + 1;
		root->left = NULL;
		return root;
	}
}

int findMax(Node* root){
	if (!root){
		return 0;
	}
	while (root->right){
		root = root->right;
	}
	return root->k_max;
}

int findMin(Node* root){
	if (!root){
		return 0;
	}
	while (root->left){
		root = root->left;
	}
	return root->k_min;
}

void inorder(Node* root, int level, int &keys, int &max_depth, vector<int> &freq){
	if (!root){
		return;
	}
	keys += root->k_max - root->k_min + 1;
	if (level > max_depth){
		max_depth = level;
		freq.push_back(root->k_max - root->k_min + 1);
	} else {
		freq[level] += root->k_max - root->k_min + 1;
	}
	inorder(root->left, level + 1, keys, max_depth, freq);
	inorder(root->right, level + 1, keys, max_depth, freq);
}
		

void getOutput(Node* root){
	int keys = 0;
	int max_depth = -1;
	vector<int> freq;
	inorder(root, 0, keys, max_depth, freq);
	printf("%u %i\n", keys, max_depth);
	for(int i = 0; i < max_depth; i++){
		printf("%i ", freq[i]);
	}
	printf("%i\n", freq[max_depth]);
}

int main(void){
	Node* root = NULL;
	int k_min, k_max, n;
	char c;
	n = fastscan();
	for(int i = 0; i < n; i++){
		scanf(" %c %u %u", &c, &k_min, &k_max);
		if (c == 'I'){
			root = insert(root, k_min, k_max);
		} else {
			root = del(root, k_min, k_max);
		}
	}
	getOutput(root);
}
	
