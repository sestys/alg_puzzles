#include <bits/stdc++.h>


using namespace std;

int rotation_counter = 0;
int left_counter = 0;

class Node {
public:
	int value;
	Node* right;
	Node* left;
	bool deleted;
	int path;
	int height;

	Node(int _value){
		value = _value;
		right = NULL;
		left = NULL;
		deleted = false;
		path = 0;
		height = 0;
	}
};

Node *r = NULL;


int _getHeight(Node* root){
	if (!root){
		return -1;
	}
	return root->height;
}

int getHeight(Node* root){
	if (!root){
		return -1;
	}
	return 1 + max(_getHeight(root->left), _getHeight(root->right));
}

int _getPath(Node *root){
	if (!root){
		return 0;
	}
	return root->path;
}

int getPath(Node* root){
	if (!root){
		return 0;
	}
	if (root->deleted){
		return 1 + max(_getPath(root->left), _getPath(root->right));
	}
	return max(_getPath(root->left), _getPath(root->right));
}

int getBalance(Node *root){
	return getHeight(root->left) - getHeight(root->right);
}

Node* rotateRight(Node* root){
	rotation_counter++;
	Node *new_root = root->left;
	Node *new_left = new_root->right;

	new_root->right = root;
	root->left = new_left;

	root->height = getHeight(root);
	new_root->height = getHeight(new_root);

	root->path = getPath(root);
	new_root->path = getPath(new_root);
	return new_root;
}

Node* rotateLeft(Node* root){
	rotation_counter++;
	left_counter++;
	Node *new_root = root->right;
	Node *new_right = new_root->left;

	new_root->left = root;
	root->right = new_right;
	
	root->height = getHeight(root);
	new_root->height = getHeight(new_root);

	root->path = getPath(root);
	new_root->path = getPath(new_root);
	return new_root;
}

Node* insert(Node* root, int value){
	if (!root){
		return new Node(value);
	}
	if (value > root->value){
		root->right = insert(root->right, value);
	} else if (value < root->value){
		root->left = insert(root->left, value);
	} else {
		if (root->deleted){
			root->deleted = false;
			root->path--;
		}
		return root;
	}

	root->path = getPath(root);
	root->height = getHeight(root);
	int balance = getBalance(root);

	if ((balance > 1) && (value < root->left->value)){
		return rotateRight(root);
	}
	if ((balance < -1) && (value > root->right->value)){
		return rotateLeft(root);
	}
	if ((balance > 1) && (value >= root->left->value)){
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if ((balance < -1) && (value <= root->right->value)){
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

Node* lazyDelete(Node* root, int value){
	if (!root){
		return root;
	}
	if (value < root->value){
		root->left = lazyDelete(root->left, value);
	} else if (value > root->value){
		root->right = lazyDelete(root->right, value);
	} else {
		if (!root->deleted){
			root->deleted = true;
		}
	}
	root->path = getPath(root);
	return root;
}

int findMax(Node* root){
	if (!root){
		return -1;
	}
	while (root->right){
		root = root->right;
	}
	return root->value;
}

int findMin(Node* root){
	if (!root){
		return -1;
	}
	while (root->left){
		root = root->left;
	}
	return root->value;
}

Node* del(Node* root, int value){
	if (!root){
		return NULL;
	}
	if (value < root->value){
		root->left = del(root->left, value);
	} else if (value > root->value){
		root->right = del(root->right, value);
	} else {
		if (root->left){
			root->value = findMax(root->left);
			root->left = del(root->left, root->value);
		} else if (root->right){
			root->value = findMin(root->right);
			root->right = del(root->right, root->value);
		} else {
			return NULL;
		}
	}
	root->height = getHeight(root);
	root->path = getPath(root);
	int balance = getBalance(root);


	if ((balance > 1) && (getBalance(root->left) >= 0)){
		return rotateRight(root);
	}
	if ((balance < -1) && (getBalance(root->right) <= 0)){
		return rotateLeft(root);
	}
	if ((balance > 1) && (getBalance(root->left) < 0)){
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if ((balance < -1) && (getBalance(root->right) > 0)){
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

bool checkConsolidation(Node* root){
	if ((!root) || (root->path < 1 + root->height / 2)){
		return false;
	} else {
		return true;
	}
}

void consolidation2(Node* root){
	while (getPath(root) > 0){
		if (getPath(root->left) > 0){
			consolidation2(root->left);
		} else if (getPath(root->right) > 0){
			consolidation2(root->right);
		} else if (root->deleted){
			root->deleted = false;
			r = del(r, root->value);
		}
	}


}

void consolidation(Node *root){
	if (!root){
		return;
	}
	consolidation(root->left);
	consolidation(root->right);
	//printf("conso node %i\n", root->value);

	root->path = 0;
	if (root->deleted){
		root->deleted = false;
		r = del(r, root->value);
	}
}

bool consolidationStupid(Node* root){
	if (!root){
		return false;
	}
	if (getPath(root) > 0){
		if (getPath(root->left) > 0){
			consolidationStupid(root->left);
			return true;
		}
		if (getPath(root->right) > 0){
			consolidationStupid(root->right);
			return true;
		}
		if (root->deleted){
			root->deleted = false;
			r = del(r, root->value);
			return true;
		}
	}
	return false;
}


int main(){
	int con_counter = 0;
	int n, command;
	scanf("%i", &n);
	for (int i = 0; i < n; i++){
		scanf("%i", &command);
		if (command > 0){
			r = insert(r, command);
		} else {
			r = lazyDelete(r, abs(command));
		}
		if (checkConsolidation(r)){
			con_counter++;
			while (consolidationStupid(r));
			
		}
	}

	printf("%i %i %i\n", getHeight(r), rotation_counter, con_counter);
	return 0;
}
